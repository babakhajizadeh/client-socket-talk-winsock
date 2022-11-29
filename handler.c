// to handle connection for each client
#include "handler.h"
#include <stdio.h>
#include <errno.h>

void* connection_handler(void* socket_desc)
{
    //Get the socket descriptor
    int sock = (int)socket_desc;
    char socket_id;
    int read_size;

    char message[100];
    char client_message[100];

    strcpy(message, " [Server] Type a message to get back:(MAX 67) \n");
    send(sock, message, strlen(message)+1, 0);
    Sleep(200);
    while ((read_size = recv(sock, client_message, 100, 0)) > 0)
    {
        printf(" [DEBUG] client message recv() returned size is:%d ", read_size); //for debuging
        printf("strlen(): %d [%s] \n",(int)strlen(client_message),client_message); //for debuging
        //Send the message back to client
       //client_message[read_size] = '\0';
        strcpy(message," [server] server thread reply:");
        sprintf(message, "%s%s\n", message, client_message);
        //printf(" [debug] strlen() message size: %d\n", ((int)(strlen(message))));

        send(sock, message, strlen(message) + 1, 0);

    }
    printf("\n [errorno] %d", errno);

    if (read_size == 0)
    {
        printf("\n [i] Client id %d disconnected.\n", sock);
        fflush(stdout);
        closesocket(sock);
    }
    else if (read_size == -1)
    {
        printf("wsa get last error: %d",WSAGetLastError());
        perror(" [!] Recv() system call failed! \n\r");
        printf(" [DEBUG] the recv() method returned value:%d\n\r", read_size);
        closesocket(sock);
    }


    return 0;
}