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
    char server_ip[15];
    int server_port;

    message[0] = '\0';


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
    printf(" [?] Enter IPV4 address of the running server: ");
    fgets(server_ip, 15, stdin);

    printf(" [?] Enter Port number for TCP communication: ");
    scanf("%d", &server_port);

    server.sin_addr.s_addr = inet_addr(server_ip); // => local , (Google: 142.251.46.174)
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);
    fflush(stdin);
    fflush(stdout);

    //Connect to remote server
    while (connect(client_soc, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("\r [i] Waiting for server...");
        
    }
    //printf("[DEBUG] errno: %d",errno);
    printf("\n [i] server has connected.\n");

    while ((recv_size = recv(client_soc, server_reply, 2048, 0)) > 3 )
    {
        //printf(" [debug] recv size each: %d\n", recv_size);
        printf(server_reply);

    }
    while ((recv_size = recv(client_soc, server_reply, 2048, 0)) > 0) {
        printf(server_reply);
        scanf("%s", message);

        ////Send some data
        //printf("[Debug]:");
        //for (int i = 0; i < strlen(message) + 1; i++)
        //{
        //    printf(" %02x", message[i]);
        //}
        if (send(client_soc, message, strlen(message) + 1, 0) < 0)
        {
            puts(" [!] Send failed");
            return 1;
        }
    }
    closesocket(client_soc);
    return 0;
}