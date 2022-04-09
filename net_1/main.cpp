#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>

#include <cstdlib>
#include <iostream>
#include <cstring>



int main(int argc, char const *argv[])
{

    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <port>" << std::endl;
        return EXIT_FAILURE;
    }


    const int port { std::stoi(argv[1]) };

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //Создаём сокет
    
        if(sock == -1) {
            std::cerr << "FAILED TO CREATE SOCKET!" << std::endl;
            return EXIT_FAILURE;
        }
        else {
            std::cout << "Starting echo server on the port " << port << "...\n";
        }


    sockaddr_in addr =
            {
                    .sin_family = PF_INET,
                    .sin_port = htons(port),
                    .sin_addr = {.s_addr = INADDR_ANY}
            };


    if (bind(sock, reinterpret_cast<const sockaddr*>(&addr), sizeof(addr)) != 0)
    {
        std::cerr << "BIND ERROR!" << std::endl;
        // Socket will be closed in the Socket destructor.
            close(sock);
        return EXIT_FAILURE;
    }

    char buffer[256];

    // socket address used to store client address
    struct sockaddr_in *client_address = {0};
    socklen_t client_address_len = sizeof(sockaddr_in);
    ssize_t recv_len = 0;

    std::cout << "Running echo server...\n" << std::endl;

    while (true)
    {
        // Read content into buffer from an incoming client.
        recv_len = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                            reinterpret_cast<sockaddr *>(&client_address),
                            &client_address_len);

        if (recv_len > 0)
        {
            buffer[recv_len] = '\0';

            std::cout
                    << "Client with address "
                    << inet_ntoa(client_address->sin_addr)
                    << ":" << client_address->sin_port
                    << " sent datagram "
                    << "[length = "
                    << recv_len
                    << "]:\n'''\n"
                    << buffer
                    << "\n'''"
                    << std::endl;

            // Send same content back to the client ("echo").
            sendto(sock, buffer, recv_len, 0, reinterpret_cast<const sockaddr *>(&client_address),
                   client_address_len);
        }

        if (getnameinfo(reinterpret_cast<const sockaddr*>(&client_address), sizeof(client_address), buffer, NI_MAXHOST, nullptr, 0, NI_NAMEREQD))
            std::cerr << "could not resolve hostname" << std::endl;
        else
            std::cout << "host: " << buffer << std::endl;

        if (SIGABRT)
            return EXIT_SUCCESS;

        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}
