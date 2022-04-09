#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>

using namespace std;

int main() {
    // Create a socket
    constexpr int CLEAR = 0;
    constexpr int ER = -1;
    char buffer[255];

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (sock == ER)
        return 1;

    // Create a hint structure for the server we're connecting with
    constexpr int port = 2202;
    //string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = PF_INET;
    hint.sin_port = htons(port);
    hint.sin_addr = {.s_addr = INADDR_ANY};
    //inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    // Connect to the server on the socket
    //int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    std::cout << "ENTER MESSAGE:" << std::endl;
    std::cin >> buffer;

    sendto(sock, buffer, sizeof(buffer), MSG_CONFIRM,
           reinterpret_cast<const sockaddr*>(&hint), sizeof(hint));

    socklen_t server_addr_len = sizeof(sockaddr_in);
    int recv_len = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
                            reinterpret_cast<sockaddr*>(&hint), &server_addr_len);

    if(recv_len > 0){
        buffer[recv_len] = '\0';
        std::cout << "SERVER MESSAGE: " << buffer << std::endl;
    }
    /*if (connectRes == ER)
        return 1;*/

    // do {} while() loop:
    /*constexpr size_t BUF_SZ = 4096;
    char buf[BUF_SZ];
    string userInput;

    do {
        //  Enter lines of text
        cout << "> ";
        getline(cin, userInput);
        //  Send to server
        constexpr int TO_LAST = 1;
        int sendRes = send(sock, userInput.c_str(), userInput.size() + TO_LAST, CLEAR);
        // TODO: Check if that failed!
        if (sendRes == ER) {
            cout << "Could not send to the server! Whoops!\r\n";
            continue;
        }

        //  Wait for response
        memset(buf, CLEAR, BUF_SZ);
        int bytesReceived = recv(sock, buf, BUF_SZ, CLEAR);

        if (bytesReceived == ER) {
            cout << "There was an error getting response from the server!\r\n";
            continue;
        }
        //  Display response
        else {
            cout << "SERVER> " << string(buf, bytesReceived) << "\r\n";
        }
    } while (true);*/
    // Close the socket
    close(sock);

    return 0;
}
