#include "sqlite3.h"
#include "Admin/Estructuras.h"
#include "bbdd.h"

// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <stdio.h>
#include <winsock2.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

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
	if (bind(conn_socket, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
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
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);



    // *********************************************************************************************
  

	// INICIAR SESIOOOOOOOON
	int idComprador;

	bool vip;

	printf("Enviando mensaje... \n");
	strcat(sendBuff, "¡Buenos dias! Antes de comprar en DeustoSportKit, deberas iniciar sesion.");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
	printf("Mensaje enviado: %s \n", sendBuff);

	printf("Enviando mensaje... \n");
	strcat(sendBuff, "¿Tienes cuenta de DeustoSportKit? (Si o No)");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
	printf("Mensaje enviado: %s \n", sendBuff);

	printf("Recibiendo mensaje... \n");
	recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
	printf("Mensaje recibido: %s \n", recvBuff);

	if (strcmp(recvBuff, "Si") == 0) {

		do {

			printf("Enviando mensaje... \n");
			strcat(sendBuff, "¿Correo?");
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			printf("Mensaje enviado: %s \n", sendBuff);

			printf("Recibiendo mensaje... \n");
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			printf("Mensaje recibido: %s \n", recvBuff);

			char* correo;
			correo = malloc(sizeof(char)*70);

			strcpy(correo, sendBuff);


			printf("Enviando mensaje... \n");
			strcat(sendBuff, "¿Contrasena?");
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			printf("Mensaje enviado: %s \n", sendBuff);

			printf("Recibiendo mensaje... \n");
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			printf("Mensaje recibido: %s \n", recvBuff);

			char* contra;
			contra = malloc(sizeof(char)*70);

			strcpy(contra, sendBuff);
			

			bool existe = existeComprador (db, correo);

			if (existe == TRUE) {

				printf("Enviando mensaje... \n");
				strcat(sendBuff, "¡Bienvenido de vuelta!");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Mensaje enviado: %s \n", sendBuff);

			} else {

				printf("Enviando mensaje... \n");
				strcat(sendBuff, "ERROR");
				send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				printf("Mensaje enviado: %s \n", sendBuff);

			}

		} while (existe == FALSE);

		Comprador cliente = obtenerComprador (db, correo);

		idComprador = cliente.identificativo;

		vip = compradorEsVip(db, idComprador);


	} else if (strcmp(recvBuff, "No") == 0) {

		printf("Enviando mensaje... \n");
		strcat(sendBuff, "¿Como te llamas?");
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Mensaje enviado: %s \n", sendBuff);

		printf("Recibiendo mensaje... \n");
		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		printf("Mensaje recibido: %s \n", recvBuff);

		char* nombre;
		nombre = malloc(sizeof(char)*15);

		strcpy(nombre, sendBuff);


		printf("Enviando mensaje... \n");
		strcat(sendBuff, "¿Numero de telefono?");
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Mensaje enviado: %s \n", sendBuff);

		printf("Recibiendo mensaje... \n");
		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		printf("Mensaje recibido: %s \n", recvBuff);

		int telf = strtol(recvBuff, NULL, 10);


		printf("Enviando mensaje... \n");
		strcat(sendBuff, "¿Correo?");
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Mensaje enviado: %s \n", sendBuff);

		printf("Recibiendo mensaje... \n");
		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		printf("Mensaje recibido: %s \n", recvBuff);

		char* correo;
		correo = malloc(sizeof(char)*50);

		strcpy(correo, sendBuff);


		printf("Enviando mensaje... \n");
		strcat(sendBuff, "¿Direccion?");
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Mensaje enviado: %s \n", sendBuff);

		printf("Recibiendo mensaje... \n");
		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		printf("Mensaje recibido: %s \n", recvBuff);

		char* direc;
		direc = malloc(sizeof(char)*60);

		strcpy(direc, sendBuff);


		printf("Enviando mensaje... \n");
		strcat(sendBuff, "¿Contrasena?");
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Mensaje enviado: %s \n", sendBuff);

		printf("Recibiendo mensaje... \n");
		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		printf("Mensaje recibido: %s \n", recvBuff);

		char* contra;
		contra = malloc(sizeof(char)*15);

		strcpy(contra, sendBuff);


		printf("Enviando mensaje... \n");
		strcat(sendBuff, "¿Quieres ser cliente VIP? (Si o No)");
		send(comm_socket, sendBuff, sizeof(sendBuff), 0);
		printf("Mensaje enviado: %s \n", sendBuff);

		printf("Recibiendo mensaje... \n");
		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		printf("Mensaje recibido: %s \n", recvBuff);

		char* esVip;
		esVip = malloc(sizeof(char)*3);

		strcpy(esVip, sendBuff);

		if (strcmp(recvBuff, "No") == 0) {

			vip = FALSE;

			registrarComprador(db, nombre, telf, correo, direc, contra);

			Comprador cliente = obtenerComprador (db, correo);
			idComprador = cliente.identificativo;

		} else if (strcmp(recvBuff, "Si") == 0) {

			vip = TRUE;

			printf("Enviando mensaje... \n");
			strcat(sendBuff, "¿Quieres ser VIP standard o premium?");
			send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			printf("Mensaje enviado: %s \n", sendBuff);

			printf("Recibiendo mensaje... \n");
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			printf("Mensaje recibido: %s \n", recvBuff);


			char* nivel;
			nivel = malloc(sizeof(char)*10);

			strcpy(esVip, sendBuff);

			registrarCompradorVip(db, nombre, telf, correo, direc, contra, nivel);

			Comprador cliente = obtenerComprador (db, correo);
			idComprador = cliente.identificativo;

		}

	}



	// PROGRAMA

    printf("Enviando mensaje... \n");
	strcat(sendBuff, "¡Buenos dias! Le atiende el servicio de atencion al cliente de DeustoSporKit. \nUn operador se encargara de ayudarle en todo lo necesario. Para terminar la conexion solo debe decir 'Agur'. \n ¿En que puedo ayudarle?");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
	printf("Mensaje enviado: %s \n", sendBuff);

    printf("Enviando mensaje... \n");
	strcat(sendBuff, "¿Qué Tipo de producto esta buscando? Eliga el numero del tipo de producto que busca o lo que quiera hacer");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
	printf("Mensaje enviado: %s \n", sendBuff);

    printf("Enviando mensaje... \n");
	strcat(sendBuff, "1. Zapatillas");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
	printf("Mensaje enviado: %s \n", sendBuff);

    printf("Enviando mensaje... \n");
	strcat(sendBuff, "2. Ropa");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
	printf("Mensaje enviado: %s \n", sendBuff);

    printf("Enviando mensaje... \n");
	strcat(sendBuff, "3. Material deportivo");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
	printf("Mensaje enviado: %s \n", sendBuff);

    printf("Enviando mensaje... \n");
	strcat(sendBuff, "4. Hablar con atencion al cliente");
	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
	printf("Mensaje enviado: %s \n", sendBuff);


	printf("Esperando a mensajes del cliente... \n");

	sqlite3 *db;

	do {

		int bytes = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		
        if (bytes > 0) {

            printf("Recibiendo mensaje... \n");
            recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			printf("Mensaje recibido: %s \n", recvBuff);

            if (strcmp(recvBuff, "Agur") == 0) {

                printf("Enviando despedida... \n");
			    strcat(sendBuff, "Agur");
			    send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			    printf("Despedida enviada.");

				break;
            }

            int num = strtol(recvBuff, NULL, 10);

            if (num == 1) {
                // ZAPATILLAS

				int size = sizeCalzado(db);
        		int i=0;
        		Calzado* listaCalzado = showCalzado(db);

				printf("Enviando zapatillas... \n");

				char *texto;
				texto = malloc(sizeof(char)*256);

				do{
					texto = "%i. %s %s %i Precio: %2f", (i+1), listaCalzado[i]->tipo, listaCalzado[i]->nombre, listaCalzado[i]->talla listaCalzado[i]->precioBase;
					strcat(sendBuff, texto);
			    	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				}while (i<size);

				printf("Zapatillas enviadas.");

				free(texto);
				texto = NULL;

				printf("Enviando mensaje... \n");
			    strcat(sendBuff, "¿Te interesa alguna zapatilla? (Si o No)");
			    send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			    printf("Mensaje enviado.");

				printf("Recibiendo mensaje... \n");
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				printf("Mensaje recibido: %s \n", recvBuff);

				if (strcmp(recvBuff, "Si") == 0) {

					printf("Enviando mensaje... \n");
					strcat(sendBuff, "Escribe el numero.");
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					printf("Mensaje enviado.");

					printf("Recibiendo mensaje... \n");
					recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
					printf("Mensaje recibido: %s \n", recvBuff);

					int id = strtol(recvBuff, NULL, 10);


					printf("Enviando mensaje... \n");
					strcat(sendBuff, "¿Cuantos?");
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					printf("Mensaje enviado.");

					printf("Recibiendo mensaje... \n");
					recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
					printf("Mensaje recibido: %s \n", recvBuff);

					int cant = strtol(recvBuff, NULL, 10);

					Calzado zap = listaCalzado[id-1];
					

					if (cant > zap.stock) {

						printf("Enviando mensaje... \n");
						strcat(sendBuff, "¡No tenemos tantos zapatos! Te venderemos solo los que quedan");
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						printf("Mensaje enviado.");

						cant = zap.stock;

					}

					int idCompra = ultimaCompra(db) + 1;

					Compra comprita = {idCompra, id, idComprador, cant};

					agregarCompra(db, Compra compra);

					Compra* comprita = comprasConId (db, zap.identificativo);


					char* ticket;
					ticket = malloc (sizeof(char)*256);
					ticket = "TICKET: (ID: %i, Producto: %i x %i)", idCompra, id, cant;

					printf("Enviando mensaje... \n");
					strcat(sendBuff, ticket);
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					printf("Mensaje enviado.");

					free(ticket);
					ticket = NULL;


					float dinero = cant * zap.precioBase;

					if (vip == TRUE) {
						ClienteVip cli = obtenerClienteVIP(db, idComprador);
						dinero = cli.rebajarPrecio(dinero);
					}

					char* precio;
					precio = malloc (sizeof(char)*256);
					precio = "PRECIO: %f", dinero;

					printf("Enviando mensaje... \n");
					strcat(sendBuff, precio);
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					printf("Mensaje enviado.");

					free(ticket);
					ticket = NULL;

				}


            } else if (num == 2) {
                // ROPA

				int size = sizePrenda(db);
        		int i=0;
        		Prenda* listaPrenda = showPrenda(db);

				printf("Enviando prendas... \n");

				char *texto;
				texto = malloc(sizeof(char)*256);

				do{
					texto = "%i. %s %s %i Precio: %2f", (i+1), listaPrenda[i]->tipo, listaPrenda[i]->nombre, listaPrenda[i]->talla, listaPrenda[i]->precioBase;
					strcat(sendBuff, texto);
			    	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				}while (i<size);

				printf("Prendas enviadas.");

				free(texto);
				texto = NULL;

				printf("Enviando mensaje... \n");
			    strcat(sendBuff, "¿Te interesa alguna prenda? (Si o No)");
			    send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			    printf("Mensaje enviado.");

				printf("Recibiendo mensaje... \n");
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				printf("Mensaje recibido: %s \n", recvBuff);

				if (strcmp(recvBuff, "Si") == 0) {

					printf("Enviando mensaje... \n");
					strcat(sendBuff, "Escribe el numero.");
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					printf("Mensaje enviado.");

					printf("Recibiendo mensaje... \n");
					recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
					printf("Mensaje recibido: %s \n", recvBuff);

					int id = strtol(recvBuff, NULL, 10);


					printf("Enviando mensaje... \n");
					strcat(sendBuff, "¿Cuantas?");
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					printf("Mensaje enviado.");

					printf("Recibiendo mensaje... \n");
					recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
					printf("Mensaje recibido: %s \n", recvBuff);

					int cant = strtol(recvBuff, NULL, 10);

					Prenda pren = listaPrenda[id-1];


					if (cant > pren.stock) {

						printf("Enviando mensaje... \n");
						strcat(sendBuff, "¡No tenemos tantas prendas! Te venderemos solo las que quedan");
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						printf("Mensaje enviado.");

						cant = pren.stock;

					}


					int idCompra = ultimaCompra(db) + 1;

					Compra comprita = {idCompra, id, idComprador, cant};

					agregarCompra(db, Compra compra);

					Compra* comprita = comprasConId (db, pren.identificativo);


					char* ticket;
					ticket = malloc (sizeof(char)*256);
					ticket = "TICKET: (ID: %i, Producto: %i x %i)", idCompra, id, cant;

					printf("Enviando mensaje... \n");
					strcat(sendBuff, ticket);
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					printf("Mensaje enviado.");

					free(ticket);
					ticket = NULL;

				}

            } else if (num == 3) {
                // MATERIAL DEPORTIVO

				int size = sizeMD(db);
        		int i=0;
        		MaterialDeportivo* listaMD = showMD(db);

				printf("Enviando material... \n");

				char *texto;
				texto = malloc(sizeof(char)*256);

				do{
					texto = "%i. %s %s %i Precio: %2f", (i+1), listaMD[i]->tipo, listaMD[i]->nombre, listaMD[i]->talla, listaMD[i]->precioBase;
					strcat(sendBuff, texto);
			    	send(comm_socket, sendBuff, sizeof(sendBuff), 0);
				}while (i<size);

				printf("Materiales enviados.");

				free(texto);
				texto = NULL;

				printf("Enviando mensaje... \n");
			    strcat(sendBuff, "¿Te interesa algun material deportivo? (Si o No)");
			    send(comm_socket, sendBuff, sizeof(sendBuff), 0);
			    printf("Mensaje enviado.");

				printf("Recibiendo mensaje... \n");
				recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
				printf("Mensaje recibido: %s \n", recvBuff);

				if (strcmp(recvBuff, "Si") == 0) {

					printf("Enviando mensaje... \n");
					strcat(sendBuff, "Escribe el numero.");
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					printf("Mensaje enviado.");

					printf("Recibiendo mensaje... \n");
					recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
					printf("Mensaje recibido: %s \n", recvBuff);

					int id = strtol(recvBuff, NULL, 10);


					printf("Enviando mensaje... \n");
					strcat(sendBuff, "¿Cuantas?");
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					printf("Mensaje enviado.");

					printf("Recibiendo mensaje... \n");
					recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
					printf("Mensaje recibido: %s \n", recvBuff);

					int cant = strtol(recvBuff, NULL, 10);

					MaterialDeportivo md = listaMD[id-1];


					if (cant > md.stock) {

						printf("Enviando mensaje... \n");
						strcat(sendBuff, "¡No tenemos tantos materiales! Te venderemos solo los que quedan");
						send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						printf("Mensaje enviado.");

						cant = md.stock;

					}


					int idCompra = ultimaCompra(db) + 1;

					Compra comprita = {idCompra, id, idComprador, cant};

					agregarCompra(db, Compra compra);


					char* ticket;
					ticket = malloc (sizeof(char)*256);
					ticket = "TICKET: (ID: %i, Producto: %i x %i)", idCompra, id, cant;

					printf("Enviando mensaje... \n");
					strcat(sendBuff, ticket);
					send(comm_socket, sendBuff, sizeof(sendBuff), 0);
					printf("Mensaje enviado.");

					free(ticket);
					ticket = NULL;

				}

            } else if (num == 4) {
                // ATENCION AL CLIENTE

                printf("Enviando mensaje... \n");
	            strcat(sendBuff, "¿Que desea?");
	            send(comm_socket, sendBuff, sizeof(sendBuff), 0);
	            printf("Mensaje enviado: %s \n", sendBuff);

                printf("Recibiendo mensaje... \n");
                recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                printf("Mensaje recibido: %s \n", recvBuff);

                do {

                    char str[512];
                    fflush(stdout);
                    fgets(str, 512, stdin);
                    scanf("%i", str);

                    printf("Enviando mensaje... \n");
                    strcpy(sendBuff, str);
                    send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                    printf("Mensaje enviado: %s \n", sendBuff);

                    printf("Recibiendo mensaje... \n");
                    recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                    printf("Mensaje recibido: %s \n", recvBuff);

                } while (strcmp(recvBuff, "Agur") != 0);

            }

            char str[512];
	        int texto;
	        fflush(stdout);
	        fgets(str, 512, stdin);
	        sscanf(str, "%i", &texto);

	        printf("Enviando mensaje... \n");
	        strcpy(sendBuff, texto);
	        send(comm_socket, sendBuff, sizeof(sendBuff), 0);
	        printf("Mensaje enviado: %s \n", sendBuff);

		}

	} while (1);

	// CLOSING the sockets and cleaning Winsock...
	closesocket(comm_socket);
	WSACleanup();

	return 0;
}

