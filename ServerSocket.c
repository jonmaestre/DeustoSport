// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <stdio.h>
#include <winsock2.h>
#include <ctype.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000


void devolucionServerSocket (SOCKET comm_socket) {

	char sendBuff[512], recvBuff[512];

	printf("Contactando con el departamento de devoluciones... \n");


	strcpy(sendBuff, "¿Que producto desea devolver? Por favor introduzca el identificativo de compra");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
	printf("Mensaje enviado: %s \n", sendBuff);

	
	printf("Receiving id \n");
	recv(s, recvBuff, sizeof(recvBuff), 0);
	printf("Data received: %s \n", recvBuff);

	// ********************* FUNCIÓN BUSCA IDCOMPRA EN BD ***********

	bool existe;

	if (existe == FALSE) {

		printf("Sending message... \n");
		strcpy(sendBuff, "¡No existe dicha compra, mentiroso!");
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: %s \n", sendBuff);

	} else {

		printf("Sending message... \n");
		strcpy(sendBuff, "¿Podrias explicarnos la razon de tu devolucion?");
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: %s \n", sendBuff);


		printf("Receiving id \n");
		recv(s, recvBuff, sizeof(recvBuff), 0);
		printf("Data received: %s \n", recvBuff);

		// ***************** FUNCION CREAR DEVOLUCION **************

		printf("Sending message... \n");
		strcpy(sendBuff, "¡Muchas gracias! Será de gran ayuda tu aportacion. \n Por favor, manda de vuelta tu paquete a la direccion 'calle Ejemplo 1A'");
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: %s \n", sendBuff);

	}

}

void problemaServerSocket (SOCKET comm_socket) {
	
	char sendBuff[512]

	printf("Sending reply... \n");
	strcpy(sendBuff, "¡Sentimos las molestias! \n Puede contactar con el servicio tecnico de DeustoSportKit llamando al 600 000 000");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
	printf("Mensaje enviado: %s \n", sendBuff);

	printf("Receiving message... \n");
	printf("Data received: %s \n", recvBuff);

}

void dudaServerSocket (SOCKET comm_socket, char recvBuff[512], char sendBuff[512]) {

	char sendBuff[512], recvBuff[512];

	strcpy(sendBuff, "¡Buenos dias! Cuentanos tu duda del stock.");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
	printf("Mensaje enviado: %s \n", sendBuff);

	strcpy(sendBuff, "¿En qué producto estas interesadx? Escriba su nombre por favor");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
	printf("Mensaje enviado: %s \n", sendBuff);

	printf("Receiving message... \n");
	recv(s, recvBuff, sizeof(recvBuff), 0);
	printf("Mensaje recibido: %s \n", recvBuff);

	// ************************************* FUNCION BUSCAR POR NOMBRE *****************

	bool existe;

	if (existe == FALSE) {

		printf("Sending message... \n");
		strcpy(sendBuff, "¡No existe dicho producto, mentiroso!");
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: %s \n", sendBuff);

	} else {

		// ******************************* CALLCULAR CUANTOS ********************

		int cuantos;

		printf("Sending message... \n");
		strcpy(sendBuff, ("Ahora mismo hay un total de %i productos en stock.", cuantos));
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: %s \n", sendBuff);

		printf("Receiving message... \n");
		recv(s, recvBuff, sizeof(recvBuff), 0);
		printf("Mensaje recibido: %s \n", recvBuff);

		printf("Sending message... \n");
		strcpy(sendBuff, "¡Que pase un buen dia!");
		send(s, sendBuff, sizeof(sendBuff), 0);
		printf("Data sent: %s \n", sendBuff);

	}

}



int main(int argc, char *argv[]) {

	WSADATA wsaData;
	SOCKET conn_socket;
	SOCKET comm_socket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512];

	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("Bind done.\n");

	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		printf("Listen failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//ACCEPT incoming connections (server keeps waiting for them)
	printf("Waiting for incoming connections...\n");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		printf("accept failed with error code : %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
			ntohs(client.sin_port));

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);


    // ********************************************************************************************************************************
    // ********************************************************************************************************************************


	//SEND and RECEIVE data
	printf("Waiting for incoming messages from client... \n");
	do {
		int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		if (bytes > 0) {
			printf("Receiving message... \n");
			printf("Data received: %s \n", recvBuff);

			printf("Sending reply... \n");
			strcpy(sendBuff, "ACK -> ");
			strcat(sendBuff, recvBuff);
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			printf("Mensaje enviado: %s \n", sendBuff);

			if (strcmp(recvBuff, "Bye") == 0)
				break;
		}
	} while (1);


    // ********************************************************************************************************************************
    // ********************************************************************************************************************************

    //SEND and RECEIVE data
    // No pongo acentos por si acaso
	
	printf("Waiting for incoming messages from client... \n");
	do {

		int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		if (bytes > 0) {
			printf("Receiving message... \n");
			printf("Data received: %s \n", recvBuff);

            if (strcmp(recvBuff, "Hola. ¿Podrias ayudarme?") == 0) {

                printf("Sending reply... \n");
                strcpy(sendBuff, "¡Claro! ¿En que puedo ayudarte? \n Devolución, problema tecnico, duda de stock");
                send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                printf("Mensaje enviado: %s \n", sendBuff);

                if (strcmp(recvBuff, "Bye") == 0) {
                    break;
                }

            } else{

               	char devolucion[11] = "DEVOLUCION";
				strcpy(devolucion, "DEVOLUCION");
				char problema[17] = "PROBLEMA TECNICO";
				strcpy(problema, "PROBLEMA TECNICO");
				char duda[14] = "DUDA DE STOCK";
				strcpy(duda, "DUDA DE STOCK");

				if (strcmp(recvBuff, devolucion) == 0) {

					devolucionServerSocket (comm_socket);
					break;

				} else if (strcmp(recvBuff, problema) == 0) {

					problemaServerSocket (comm_socket);
					break;

				} else if (strcmp(recvBuff, duda) == 0) {
					
					dudaServerSocket (comm_socket);
					break;

				} else {
					printf("Sending reply... \n");
					strcpy(sendBuff, "¡Hasta la proxima!");
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					printf("Mensaje enviado: %s \n", sendBuff);
					break;
				}

            }
		}
	} while (1);

    // ********************************************************************************************************************************
    // ********************************************************************************************************************************


	// CLOSING the sockets and cleaning Winsock...
	closesocket(comm_socket);
	WSACleanup();

	return 0;
}
