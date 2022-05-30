
// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <stdio.h>
#include <winsock2.h>
#include <ctype.h>
#include <iostream>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

using namespace std;

int main(int argc, char *argv[]) {

	WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in server;
	char sendBuff[512], recvBuff[512];

	cout << "Initialising Winsock..." << endl;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << "Failed. Error Code " << WSAGetLastError() << endl;
		return -1;
	}

	cout << "Initialised." << endl;

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		cout << "Could not create socket : " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}

	cout << "Socket created." << endl;

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		cout << "Connection error: " << WSAGetLastError() << endl;
		closesocket(s);
		WSACleanup();
		return -1;
	}

	cout << "Connection stablished with:" << inet_ntoa(server.sin_addr) << "(" << ntohs(server.sin_port) << ")" << endl;



    // *********************************************************************************************
    






    int bytes = recv(s, recvBuff, sizeof(recvBuff), 0);
		
    if (bytes > 0) {

		// INICIAR SESION

		cout << "Recibiendo mensaje... " << endl;
        recv(s, recvBuff, sizeof(recvBuff), 0);
		cout << "Mensaje recibido: " << recvBuff << endl;

		cout << "Recibiendo mensaje... " << endl;
        recv(s, recvBuff, sizeof(recvBuff), 0);
		cout << "Mensaje recibido: " << recvBuff << endl;


		char* cuenta;
		cuenta = new char[3];
	    cin >> cuenta;

	    cout << "Enviando mensaje... " << endl;
	    strcpy(sendBuff, cuenta);
        send(s, sendBuff, sizeof(sendBuff), 0);
	    cout << "Mensaje enviado: " << sendBuff << endl;


		if (strcmp(cuenta, "No") == 0) {

			char* entrado;
			entrado = new char[30];
			strcpy(entrado, "ERROR");

			do {

				cout << "Recibiendo mensaje... " << endl;
				recv(s, recvBuff, sizeof(recvBuff), 0);
				cout << "Mensaje recibido: " << recvBuff << endl;

				char* correo;
				correo = new char[70];
				cin >> cuenta;

				cout << "Enviando mensaje... " << endl;
				strcpy(sendBuff, correo);
				send(s, sendBuff, sizeof(sendBuff), 0);
				cout << "Mensaje enviado: " << sendBuff << endl;


				cout << "Recibiendo mensaje... " << endl;
				recv(s, recvBuff, sizeof(recvBuff), 0);
				cout << "Mensaje recibido: " << recvBuff << endl;

				char* contra;
				contra = new char[70];
				cin >> contra;

				cout << "Enviando mensaje... " << endl;
				strcpy(sendBuff, contra);
				send(s, sendBuff, sizeof(sendBuff), 0);
				cout << "Mensaje enviado: " << sendBuff << endl;


				cout << "Recibiendo mensaje... " << endl;
				recv(s, recvBuff, sizeof(recvBuff), 0);
				cout << "Mensaje recibido: " << recvBuff << endl;

				char* contra;
				contra = new char[70];
				cin >> contra;

				cout << "Enviando mensaje... " << endl;
				strcpy(sendBuff, contra);
				send(s, sendBuff, sizeof(sendBuff), 0);
				cout << "Mensaje enviado: " << sendBuff << endl;

				cout << "Recibiendo mensaje... " << endl;
				recv(s, recvBuff, sizeof(recvBuff), 0);
				cout << "Mensaje recibido: " << recvBuff << endl;

				strcpy(entrado, recvBuff);

			} while ((strcmp(entrado, "ERROR") == 0));

			delete[] entrado;

		} else if (strcmp(cuenta, "No") == 0) {

			cout << "Recibiendo mensaje... " << endl;
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout << "Mensaje recibido: " << recvBuff << endl;

			char* nombre;
			nombre = new char[15];
			cin >> nombre;

			cout << "Enviando mensaje... " << endl;
			strcpy(sendBuff, nombre);
			send(s, sendBuff, sizeof(sendBuff), 0);
			cout << "Mensaje enviado: " << sendBuff << endl;


			cout << "Recibiendo mensaje... " << endl;
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout << "Mensaje recibido: " << recvBuff << endl;

			int telf;
			cin >> telf;
			char* teleff;
			teleff = new char[sizeof(char)*10];
			std::sprintf(teleff, "%d", telf);

			cout << "Enviando mensaje... " << endl;
			strcpy(sendBuff, teleff);
			send(s, sendBuff, sizeof(sendBuff), 0);
			cout << "Mensaje enviado: " << sendBuff << endl;


			cout << "Recibiendo mensaje... " << endl;
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout << "Mensaje recibido: " << recvBuff << endl;

			char* correo;
			correo = new char[50];
			cin >> correo;

			cout << "Enviando mensaje... " << endl;
			strcpy(sendBuff, correo);
			send(s, sendBuff, sizeof(sendBuff), 0);
			cout << "Mensaje enviado: " << sendBuff << endl;


			cout << "Recibiendo mensaje... " << endl;
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout << "Mensaje recibido: " << recvBuff << endl;

			char* direc;
			direc = new char[60];
			cin >> direc;

			cout << "Enviando mensaje... " << endl;
			strcpy(sendBuff, direc);
			send(s, sendBuff, sizeof(sendBuff), 0);
			cout << "Mensaje enviado: " << sendBuff << endl;


			cout << "Recibiendo mensaje... " << endl;
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout << "Mensaje recibido: " << recvBuff << endl;

			char* contrasena;
			contrasena = new char[15];
			cin >> contrasena;

			cout << "Enviando mensaje... " << endl;
			strcpy(sendBuff, contrasena);
			send(s, sendBuff, sizeof(sendBuff), 0);
			cout << "Mensaje enviado: " << sendBuff << endl;


			cout << "Recibiendo mensaje... " << endl;
			recv(s, recvBuff, sizeof(recvBuff), 0);
			cout << "Mensaje recibido: " << recvBuff << endl;

			char* vip;
			vip = new char[3];
			cin >> vip;

			cout << "Enviando mensaje... " << endl;
			strcpy(sendBuff, vip);
			send(s, sendBuff, sizeof(sendBuff), 0);
			cout << "Mensaje enviado: " << sendBuff << endl;


			if (strcmp(vip, "Si") == 0) {

				cout << "Recibiendo mensaje... " << endl;
				recv(s, recvBuff, sizeof(recvBuff), 0);
				cout << "Mensaje recibido: " << recvBuff << endl;

				char* vipLevel;
				vipLevel = new char[10];
				cin >> vipLevel;

				cout << "Enviando mensaje... " << endl;
				strcpy(sendBuff, vipLevel);
				send(s, sendBuff, sizeof(sendBuff), 0);
				cout << "Mensaje enviado: " << sendBuff << endl;

			}

		}



		// PROGRAMA

		cout << "Recibiendo mensaje... " << endl;
        recv(s, recvBuff, sizeof(recvBuff), 0);
		cout << "Mensaje recibido: " << recvBuff << endl;

        int opcion;
	    cin >> opcion;
		char* opp;
		opp = new char[sizeof(char)*2];
		std::sprintf(opp, "%d", opcion);

	    cout << "Enviando mensaje... " << endl;
	    strcpy(sendBuff, opp);
        send(s, sendBuff, sizeof(sendBuff), 0);
	    cout << "Mensaje enviado: " << sendBuff << endl;

		if (strcmp(recvBuff, "Agur") != 0) {

            if (opcion == 1) {
                // ZAPATILLAS

				do {
					cout << "Recibiendo mensaje... " << endl;
					recv(s, recvBuff, sizeof(recvBuff), 0);
					cout << "Mensaje recibido: " << recvBuff << endl;
				} while (strcmp(recvBuff, "¿Te interesa alguna zapatilla? (Si o No)") != 0);

				char* respuesta;
				respuesta = new char[3];
	    		cin >> respuesta;

				cout << "Enviando mensaje... " << endl;
				strcpy(sendBuff, respuesta);
				send(s, sendBuff, sizeof(sendBuff), 0);
				cout << "Mensaje enviado: " << sendBuff << endl;

				if (strcmp(recvBuff, "Si") == 0) {

					cout << "Recibiendo mensaje... " << endl;
					recv(s, recvBuff, sizeof(recvBuff), 0);
					cout << "Mensaje recibido: " << recvBuff << endl;

					int id;
					cin >> id;
					char* idenn;
					idenn = new char[sizeof(char)*5];
					std::sprintf(idenn, "%d", id);

					cout << "Enviando mensaje... " << endl;
					strcpy(sendBuff, idenn);
					send(s, sendBuff, sizeof(sendBuff), 0);
					cout << "Mensaje enviado: " << sendBuff << endl;


					cout << "Recibiendo mensaje... " << endl;
					recv(s, recvBuff, sizeof(recvBuff), 0);
					cout << "Mensaje recibido: " << recvBuff << endl;

					int cant;
					cin >> cant;
					char* cannti;
					cannti = new char[sizeof(char)*10];
					std::sprintf(cannti, "%d", cant);

					cout << "Enviando mensaje... " << endl;
					strcpy(sendBuff, cannti);
					send(s, sendBuff, sizeof(sendBuff), 0);
					cout << "Mensaje enviado: " << sendBuff << endl;


					cout << "Recibiendo mensaje... " << endl;
					recv(s, recvBuff, sizeof(recvBuff), 0);
					cout << "Mensaje recibido: " << recvBuff << endl;

					
					if (strcmp(recvBuff, "¡No tenemos tantos zapatos! Te venderemos solo los que quedan") == 0) {

						cout << "Recibiendo mensaje... " << endl;
						recv(s, recvBuff, sizeof(recvBuff), 0);
						cout << "Mensaje recibido: " << recvBuff << endl;

					}

					cout << "Recibiendo mensaje... " << endl;
					recv(s, recvBuff, sizeof(recvBuff), 0);
					cout << "Mensaje recibido: " << recvBuff << endl;

				}

            } else if (opcion == 2) {
                // ROPA

				do {
					cout << "Recibiendo mensaje... " << endl;
					recv(s, recvBuff, sizeof(recvBuff), 0);
					cout << "Mensaje recibido: " << recvBuff << endl;
				} while (strcmp(recvBuff, "¿Te interesa alguna prenda? (Si o No)") != 0);

				char* respuesta;
				respuesta = new char[3];
	    		cin >> respuesta;

				cout << "Enviando mensaje... " << endl;
				strcpy(sendBuff, respuesta);
				send(s, sendBuff, sizeof(sendBuff), 0);
				cout << "Mensaje enviado: " << sendBuff << endl;

				if (strcmp(recvBuff, "Si") == 0) {

					cout << "Recibiendo mensaje... " << endl;
					recv(s, recvBuff, sizeof(recvBuff), 0);
					cout << "Mensaje recibido: " << recvBuff << endl;

					int id;
					cin >> id;
					char* idenn;
					idenn = new char[sizeof(char)*10];
					std::sprintf(idenn, "%d", id);

					cout << "Enviando mensaje... " << endl;
					strcpy(sendBuff, idenn);
					send(s, sendBuff, sizeof(sendBuff), 0);
					cout << "Mensaje enviado: " << sendBuff << endl;


					cout << "Recibiendo mensaje... " << endl;
					recv(s, recvBuff, sizeof(recvBuff), 0);
					cout << "Mensaje recibido: " << recvBuff << endl;

					int cant;
					cin >> cant;
					char* cannti;
					cannti = new char[sizeof(char)*10];
					std::sprintf(cannti, "%d", cant);

					cout << "Enviando mensaje... " << endl;
					strcpy(sendBuff, cannti);
					send(s, sendBuff, sizeof(sendBuff), 0);
					cout << "Mensaje enviado: " << sendBuff << endl;


					cout << "Recibiendo mensaje... " << endl;
					recv(s, recvBuff, sizeof(recvBuff), 0);
					cout << "Mensaje recibido: " << recvBuff << endl;


					if (strcmp(recvBuff, "¡No tenemos tantas prendas! Te venderemos solo las que quedan") == 0) {

						cout << "Recibiendo mensaje... " << endl;
						recv(s, recvBuff, sizeof(recvBuff), 0);
						cout << "Mensaje recibido: " << recvBuff << endl;

					}

				}

            } else if (opcion == 3) {
                // MATERIAL

				do {
					cout << "Recibiendo mensaje... " << endl;
					recv(s, recvBuff, sizeof(recvBuff), 0);
					cout << "Mensaje recibido: " << recvBuff << endl;
				} while (strcmp(recvBuff, "¿Te interesa algun material deportivo? (Si o No)") != 0);

				char* respuesta;
				respuesta = new char[3];
	    		cin >> respuesta;

				cout << "Enviando mensaje... " << endl;
				strcpy(sendBuff, respuesta);
				send(s, sendBuff, sizeof(sendBuff), 0);
				cout << "Mensaje enviado: " << sendBuff << endl;

				if (strcmp(recvBuff, "Si") == 0) {

					cout << "Recibiendo mensaje... " << endl;
					recv(s, recvBuff, sizeof(recvBuff), 0);
					cout << "Mensaje recibido: " << recvBuff << endl;

					int id;
					cin >> id;
					char* idenn;
					idenn = new char[sizeof(char)*10];
					std::sprintf(idenn, "%d", id);

					cout << "Enviando mensaje... " << endl;
					strcpy(sendBuff, idenn);
					send(s, sendBuff, sizeof(sendBuff), 0);
					cout << "Mensaje enviado: " << sendBuff << endl;


					cout << "Recibiendo mensaje... " << endl;
					recv(s, recvBuff, sizeof(recvBuff), 0);
					cout << "Mensaje recibido: " << recvBuff << endl;

					int cant;
					cin >> cant;
					char* cannti;
					cannti = new char[sizeof(char)*10];
					std::sprintf(cannti, "%d", cant);


					cout << "Enviando mensaje... " << endl;
					strcpy(sendBuff, cannti);
					send(s, sendBuff, sizeof(sendBuff), 0);
					cout << "Mensaje enviado: " << sendBuff << endl;

					cout << "Recibiendo mensaje... " << endl;
					recv(s, recvBuff, sizeof(recvBuff), 0);
					cout << "Mensaje recibido: " << recvBuff << endl;

					if (strcmp(recvBuff, "¡No tenemos tantos materiales! Te venderemos solo los que quedan") == 0) {

						cout << "Recibiendo mensaje... " << endl;
						recv(s, recvBuff, sizeof(recvBuff), 0);
						cout << "Mensaje recibido: " << recvBuff << endl;

					}

				}

            } else if (opcion == 4) {
				// ATENCION AL CLIENTE
			
                do {

                    int bytes = recv(s, recvBuff, sizeof(recvBuff), 0);
                    
                    if (bytes > 0) {

                        cout << "Recibiendo mensaje... " << endl;
                        recv(s, recvBuff, sizeof(recvBuff), 0);
                        cout << "Mensaje recibido: " << recvBuff << endl;

                        char str[512];
                        cin >> str;

                        cout << "Enviando mensaje... " << endl;
                        strcpy(sendBuff, str);
                        send(s, sendBuff, sizeof(sendBuff), 0);
                        cout << "Mensaje enviado: " << sendBuff << endl;

                        if (strcmp(recvBuff, "Agur") == 0) {
                            break;
                        }
                    }

                } while (1);

            }

        }

	}

	// CLOSING the socket and cleaning Winsock...
	closesocket(s);
	WSACleanup();

	return 0;
}

