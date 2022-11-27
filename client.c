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
    
    server.sin_addr.s_addr = inet_addr("172.19.7.29"); // => Google , (local server: 142.251.46.174)
    server.sin_family = AF_INET;
    server.sin_port = htons(8888); // => google http , (local server: 8888)

    //Connect to remote server
    while (connect(client_soc, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("\r [i] Waiting for server...");
        
    }
    printf("[errno]%d",errno);
    printf("\n [i] server has connected.\n");

    //Send some data
    strcpy(message, "test");
    if (send(client_soc, message, strlen(message), 0) < 0)
    {
        puts("Send failed");
        return 1;
    }
    puts(" [i] Data Send\n");
    
    //Receive a reply from the server
    if ((recv_size = recv(client_soc, server_reply, 2048, 0)) == SOCKET_ERROR)
    {
        puts("recv failed");
    }
    else puts(" [i] Reply received\n");

    printf(" [debug] recv_size: %d", recv_size);
    //Add a NULL terminating character to make it a proper string before printing
    server_reply[recv_size-1] = '\0';
    puts(server_reply);

    return 0;




    //while ((server_reply_size = recv(client_soc, server_reply, strlen(server_reply), 0)) > 0)
    //{
    //    printf("%.*s\n", (int)strlen(server_reply), server_reply);
    //    printf("\n[debug] server_reply strlen(): %zd", strlen(server_reply));
    //    printf("\n[debug] recve return zie : %d", server_reply_size);
    //    printf("\n[debug]%.*s\n", (int)strlen(server_reply), server_reply);
    //}

    //printf(" [i] Type a message to send:\n");
    //strcpy(message, "t"); //single character test message
    //if (send(client_soc, message, strlen(message), 0) < 0)
    //{
    //    puts("Send failed");
    //}
    //printf("\n [!] message has sent!\n");

    //while (fgets(message, sizeof message, stdin))
    //{
    //    if (send(client_soc, message, strlen(message), 0) < 0)
    //    {
    //        puts("Send failed");
    //        return 1;
    //    }
    //    printf(" [!] message has sent!\n");
    //    printf(" [i] Type a message to send:\n");

    //}

    return 0;
}