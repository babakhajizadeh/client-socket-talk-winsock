// Server side demo Socket programming
#include <stdio.h>
#include <stdlib.h>
#include <winsock.h>
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>

int main(int argc, char* argv[])
{
    int recv_size;
    WSADATA wsa;
    SOCKET client_soc;
    struct sockaddr_in client, server;
    char message[100];
    char server_reply[2048];

    printf(" [i] client side Initialising of Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf(" [!] winsock initialisation failed. Error Code : %d\n", WSAGetLastError());
        return 1;
    }
    printf(" [i] Winsock initialized.\n");

    //Create socket
    client_soc = socket(AF_INET, SOCK_STREAM, 0);
    if (client_soc == -1)
    {
        printf(" [!] client socket failed to creat!\n");
    }
    
    server.sin_addr.s_addr = inet_addr("172.19.7.196"); // => local , (Google: 142.251.46.174)
    server.sin_family = AF_INET;
    server.sin_port = htons(8888); // => google http , (local server: 8888)

    //Connect to remote server
    while (connect(client_soc, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("\r [i] Waiting for server...");
        
    }
    printf("[errno]%d",errno);
    printf("\n [i] server has connected.\n");

    for (int i = 0;i < 10;i++) {
        //Send some data
        strcpy(message, "hello from client\0");
        if (send(client_soc, message, strlen(message), 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
        puts(" [i] Data Send\n");

        //Receive a reply from the server

        if ((recv_size = recv(client_soc, server_reply, 2048, 0)) > 0)
        {
            printf("[i] recievined\n");
        }
        if (recv_size == SOCKET_ERROR)
        {
            puts("recv failed");
        }
        else { puts(" [i] Reply received\n"); }

        printf(" [debug] recv_size: %d", recv_size);

        //Add a NULL terminating character to make it a proper string before printing

        server_reply[recv_size - 1] = '\0';
        puts(server_reply);
    }
    getchar();
    closesocket(client_soc);
    return 0;
}