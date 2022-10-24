
#include "../../include/ddevlib/dnet/dnet.hpp"
#include <winsock2.h>

sockaddr_in dnet::net::server;
int dnet::net::client_socket = NULL;

dnet::net::net() {

}

int dnet::net::init() {

    WSADATA ws;
    printf("DNET: Initialising Winsock... ");
    if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
    {
        printf("Failed. Error Code: %d", WSAGetLastError());
        return 1;
    }
    printf("Initialised.\n");

    // create socket
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) // <<< UDP socket
    {
        printf("DNET: socket() failed with error code: %d\n", WSAGetLastError());
        return 2;
    }

    // setup address structure
    memset((char*)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.S_un.S_addr = inet_addr(SERVER);

    return 0;
}

int dnet::net::send(std::string message) {
    if (sendto(client_socket, message.c_str(), strlen(message.c_str()), 0, (sockaddr*)&server, sizeof(sockaddr_in)) == SOCKET_ERROR)
    {
        printf("DNET: sendto() failed with error code: %d\n", WSAGetLastError());
        return 3;
    }

    return 0;
}

int dnet::net::end() {
    printf("DNET: Closing socket... ");
    
    closesocket(client_socket);
    WSACleanup();
    
    printf("Done.\n");

    return 0;
}

std::string dnet::net::err(int err) {
    if (err == 1)       return "Failed to init Winsock";
    else if (err == 2)  return "Failed to create socket";
    else if (err == 3)  return "Failed to send message";
    else return "";
}
