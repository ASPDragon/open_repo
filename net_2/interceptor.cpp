// Включает поддержку всех Стандартов в библиотеке (C89, C99, POSIX, BSD, SVID
// LFS, X/Open) и расширения GNU.
// Он влияет на stdio и stdlib.
// Здесь нужен для того, чтобы был доступен макрос RTLD_NEXT.
#define _GNU_SOURCE
//
// System calls interceptor for the networking spoiling...

extern "C" {
#include <dlfcn.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
};

#include <cstdio>
#include <cstdlib>
#include <ctime>

static void init (void) __attribute__ ((constructor));

typedef ssize_t (*write_t) (int fd, const void* buf, size_t count);
typedef int (*socket_t) (int domain, int type, int protocol);
typedef int (*close_t) (int fd);
typedef int (*connect_t) (int sockfd, const struct sockaddr* addr, socklen_t addren);

static close_t old_close;
static socket_t old_socket;
static write_t old_write;
static connect_t old_connect;

// В учебных целях будет перехвачено единственное открытие сокета.
static int socket_fd = -1;

void init(void) {
    srand(time(nullptr));
    // Использую printf(), т.к. ниже я не могу использовать классы и код STL.
    // А смешивать две системы вывода - нежелательно.

    printf("Interceptor library loaded.\n");
    // Сохраняю указатели на предыдущие вызовы
    old_close = reinterpret_cast<close_t>(dlsym(RTLD_NEXT, "close"));
    old_write = reinterpret_cast<write_t>(dlsym(RTLD_NEXT, "write"));
    old_socket = reinterpret_cast<socket_t>(dlsym(RTLD_NEXT, "socket"));
    old_connect = reinterpret_cast<connect_t>(dlsym(RTLD_NEXT, "connect"));
}

int connect(int sockfd, const struct sockaddr *addr,
            socklen_t addrlen) {
    sockaddr_in* addr_in = (sockaddr_in*)addr;
    char ip_str[32];
    inet_ntop(addr_in->sin_family, &addr_in->sin_addr, ip_str, 32);

    printf("> connect() on the socket was called for %s:%d!\n", ip_str, addr_in->sin_port);
    if (sockfd == socket_fd) {
        int res = old_connect(sockfd, addr, addrlen);
        if (res == -1) return -1;
        char address_data[1024];
        sprintf(address_data, "Address: %s; port: %d", ip_str, addr_in->sin_port);
        write(sockfd, address_data, strlen(address_data));

        return 0;
    }
    return old_connect(sockfd, addr, addrlen);
}

// Перехват вызовов производится из C-библиотеки, поэтому нужно выключить
// манглинг C++.
// Если манглинг не будет выключен, придётся реализовывать перехватчик на
// чистом C.

extern "C" {

    ssize_t write(int fd, const void* buf, size_t count) {
        auto char_buf = reinterpret_cast<const char*>(buf);

        if (char_buf && (count > 1) && (fd == socket_fd)) {
            FILE* file = fopen("log.dump", "w");
            fprintf(file, "> write() on the socket was called with a string '%s', '%d'\n", char_buf,
                    strcmp(char_buf, "close"));
            if (strcmp(char_buf, "close") == 10) {
                close(fd);
                return 0;
            }
            fprintf(file, "New buffer = [");
            fprintf(file, "%s",char_buf);
            fprintf(file, "]\n");
            fclose(file);
        }

        return old_write(fd, buf, count);
    }

int close(int fd) {
    if (fd == socket_fd) {
        printf("> close() on the socket was called!\n");
        char buf[8];
        strcpy(buf, "closed!");
        printf("%s\n", buf);
        if (old_write(fd, buf, 7) == -1) {
            perror("Error writing closed event");
        }
        socket_fd = -1;
        sleep(3);
    }
    return old_close(fd);
}

int socket(int domain, int type, int protocol) {
    int cur_socket_fd = old_socket(domain, type, protocol);
    if (-1 == socket_fd) {
        printf("> socket() was called, fd = %d!\n", cur_socket_fd);
// Первый вызов функции socket(), надо сохранить дескриптор.
        socket_fd = cur_socket_fd;
    } else {
        printf("> socket() was called, but socket was opened already...\n");
    }
    return cur_socket_fd;
}
}