// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <stdio.h>
#include <winsock2.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000


void devolucionClienteSocket (SOCKET s) {

	char sendBuff[512], recvBuff[512];

	printf("Receiving message... \n");
	recv(s, recvBuff, sizeof(recvBuff), 0);
	printf("Mensaje recibido: %s \n", recvBuff);

    char str[1000];
	int id;
	fflush(stdout);
	fgets(str, 1000, stdin);
	sscanf(str, "%i", &id);

	printf("Sending message... \n");
	strcpy(sendBuff, id);
	send(s, sendBuff, sizeof(sendBuff), 0);
	printf("Mensaje enviado: %s \n", sendBuff);

	char mensaje[512];
	strcpy(mensaje, "¡No existe dicha compra, mentiroso!");

    if (strcmp(recvBuff, mensaje) != 0) {

		char razon[1000];
		fflush(stdout);
		fgets(str, 1000, stdin);
		sscanf(str, "%s", &razon);

		printf("Sending message... \n");
		strcpy(sendBuff, razon);
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("Mensaje enviado: %s \n", sendBuff);	

		printf("Receiving message... \n");
		recv(s, recvBuff, sizeof(recvBuff), 0);
		printf("Mensaje recibido: %s \n", recvBuff);

	}

}

void problemaClienteSocket (SOCKET s) {

	char sendBuff[512];

	printf("Sending reply... \n");
	strcpy(sendBuff, "¡Gracias!");
	send(s, sendBuff, sizeof(sendBuff), 0);
	printf("Mensaje enviado: %s \n", sendBuff);
}

void dudaClienteSocket (SOCKET s) {

	char sendBuff[512], recvBuff[512];

	printf("Receiving message... \n");
	recv(s, recvBuff, sizeof(recvBuff), 0);
	printf("Mensaje recibido: %s \n", recvBuff);

	printf("Receiving message... \n");
	recv(s, recvBuff, sizeof(recvBuff), 0);
	printf("Mensaje recibido: %s \n", recvBuff);


	char str[1000];
	int nombre;
	fflush(stdout);
	fgets(str, 1000, stdin);
	sscanf(str, "%s", &nombre);

	printf("Sending reply... \n");
	strcpy(sendBuff, nombre);
	send(s, sendBuff, sizeof(sendBuff), 0);
	printf("Mensaje enviado: %s \n", sendBuff);


	printf("Receiving message... \n");
	recv(s, recvBuff, sizeof(recvBuff), 0);
	printf("Mensaje recibido: %s \n", recvBuff);

	printf("Sending reply... \n");
	strcpy(sendBuff, "¡Gracias!");
	send(s, sendBuff, sizeof(sendBuff), 0);
	printf("Mensaje enviado: %s \n", sendBuff);

	printf("Receiving message... \n");
	recv(s, recvBuff, sizeof(recvBuff), 0);
	printf("Mensaje recibido: %s \n", recvBuff);

}


int main(int argc, char *argv[]) {

	WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in server;
	char sendBuff[512], recvBuff[512];

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		printf("Connection error: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr), ntohs(server.sin_port));


    // ********************************************************************************************************************************
    // ********************************************************************************************************************************


	// SEND and RECEIVE data
	printf("Sending message 1... \n");
	strcpy(sendBuff, "Hello, server.");
	send(s, sendBuff, sizeof(sendBuff), 0);

	printf("Receiving message 1... \n");
	recv(s, recvBuff, sizeof(recvBuff), 0);
	printf("Data received: %s \n", recvBuff);

	printf("Sending message 2... \n");
	strcpy(sendBuff, "Hello again.");
	send(s, sendBuff, sizeof(sendBuff), 0);
	printf("Data sent: %s \n", sendBuff);

	printf("Receiving message 2... \n");
	recv(s, recvBuff, sizeof(recvBuff), 0);
	printf("Data received: %s \n", recvBuff);

	printf("Sending last message... \n");
	strcpy(sendBuff, "Bye");
	send(s, sendBuff, sizeof(sendBuff), 0);
	printf("Data sent: %s \n", sendBuff);


    // ********************************************************************************************************************************
    // ********************************************************************************************************************************


	// SEND and RECEIVE data
	printf("Sending message \n");
	strcpy(sendBuff, "Hola. ¿Podrias ayudarme?");
	send(s, sendBuff, sizeof(sendBuff), 0);

	do {

		int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);

		if (bytes > 0) {
			printf("Receiving message... \n");
			printf("Data received: %s \n", recvBuff);

            char primerMensaje[512];
            primerMensaje = "¡Claro! ¿En que puedo ayudarte? \n Devolución, problema tecnico, duda de stock";

            if (strcmp(recvBuff, primerMensaje) == 0) {

				char str[20];
				char opcion[20];
				fflush(stdout);
				fgets(str, MAX_LINE, stdin);
				sscanf(str, "%i", &opcion);

				for (int indice = 0; opcion[indice] != '\0'; ++indice){
					opcion[indice] = toupper(opcion[indice]);
				}

                printf("Sending reply... \n");
                strcpy(sendBuff, opcion);
                send(s, sendBuff, sizeof(sendBuff), 0);
                printf("Mensaje enviado: %s \n", sendBuff);

				if (strcmp(opcion, "DEVOLUCION") == 0) {

					devolucionClienteSocket (SOCKET s);
					break;

				} else if (strcmp(opcion, "PROBLEMA TECNICO") == 0) {

					problemaClienteSocket (SOCKET s);
					break;

				} else if (strcmp(opcion, "DUDA DE STOCK") == 0) {

					dudaClienteSocket (SOCKET s);
					break;

				}


            } 
		}

	} while (1);

	// CLOSING the socket and cleaning Winsock...
	closesocket(s);
	WSACleanup();

	return 0;
}

