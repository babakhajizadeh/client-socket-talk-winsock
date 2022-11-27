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

    strcpy(message, " [?] Type a message to get back:\n\r\0");
    send(sock, message, strlen(message)+1, 0);
    while ((read_size = recv(sock, client_message, 100, 0)) > 0)
    {
    //    printf(" [debug] client message recv() returned size is:%d\n", read_size);

        //Send the message back to client
        strcpy(message,"\n [i] server thread reply: \n\r\0");
        send(sock, message, strlen(message) + 1, 0);
        send(sock, client_message, read_size, 0);


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
        perror(" [!] Recv() system call failed! \n\r");
        printf(" [debug] the recv() method returned value:%d\n\r", read_size);
        closesocket(sock);
    }


    return 0;
}