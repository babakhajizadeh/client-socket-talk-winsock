// Server side demo Socket programming
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "handler.h"
int main(int argc, char const* argv[])
{
	WSADATA wsa;
	SOCKET server_soc, new_socket;
	struct sockaddr_in server ,client;
	int c;
	char message[100];
	char socket_to_string[8];
	pthread_t sniffer_thread;
	char signal[3] = { "ok" };
	int server_port;


	printf(" [i] server side Initialising of Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf(" [!] winsock initialisation failed. Error Code : %d\n", WSAGetLastError());
		return 1;
	}
	printf(" [i] Winsock initialized.\n");


	// Creating unbound socket file descriptor
	if ((server_soc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror(" [!] Server socket failed to creat.\n"); // serrver return above 0 means success
		exit(EXIT_FAILURE);
	}
	printf(" [i] Server socket created.\n");


	printf(" [?] Enter Port number for TCP communication: ");
	scanf("%d",&server_port);

	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(server_port);

	//Bind
	if (bind(server_soc, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf(" [i] Bind failed with error code : %d\n", WSAGetLastError());
	}

	printf(" [i] Bind done.\n");

	//Listen to incoming connections
	listen(server_soc, 3);

	//Accept and incoming connection
	printf(" [i] Waiting for incoming connections...\n");

	if (listen(server_soc, 3) < 0) {
		perror(" [!] listen failed.");
		exit(EXIT_FAILURE);
	}
	c = sizeof(struct sockaddr_in);

	while ((new_socket = accept(server_soc, (struct sockaddr*)&client, &c)) != INVALID_SOCKET) {
		printf(" [i] Connection accepted for socket: %d\n\r",(int)new_socket);
		strcpy(message, "\r [server] Connection has accepted.\n");
		send(new_socket, message, strlen(message) + 1, 0);
		strcpy(message, "\r [server] creating connection handler for socket id: ");
		//strcpy(socket_to_string, "\0");
		sprintf(socket_to_string, "%d\n", (int)new_socket);
		sprintf(message, "%s%s", message, socket_to_string);
		Sleep(200);
		send(new_socket, message, strlen(message) + 1, 0);
		Sleep(200);
		send(new_socket, signal, strlen(signal) + 1, 0);

		if (pthread_create(&sniffer_thread, NULL, connection_handler, (void*)new_socket) < 0)
		{
			perror(" [!] could not create thread\n\r");
		}
		//pthread_join(sniffer_thread, NULL);

	} 

	if (new_socket == INVALID_SOCKET) printf(" [!] Accept failed with error code %d\n", WSAGetLastError());

	closesocket(server_soc);
	WSACleanup();
	return 0;

}
