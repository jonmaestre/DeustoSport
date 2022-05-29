
// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <stdio.h>
#include <winsock2.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

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



    // *********************************************************************************************
    // El ClienteQueAtender es un cliente de la plataforma que acude al servicio de Atencion al Cliente de DeustoSportKit.
    // Aquí podrá comunicarse libremente con un trabajador de la empresa dispuesto a ayudarle.
    // La dieferencia con el "ClienteSocket.c" es que podrá consultar dudas que no sean sobre devoluciones, problemas tecnicos o stock.


    int bytes = recv(s, recvBuff, sizeof(recvBuff), 0);
		
    if (bytes > 0) {

		cout << "Recibiendo mensaje... " << endl;
        recv(s, recvBuff, sizeof(recvBuff), 0);
		cout << "Mensaje recibido: " << recvBuff << endl;

        int opcion;
	    cin >> opcion;

	    cout << "Enviando mensaje... " << endl;
	    strcpy(sendBuff, opcion);
        send(s, sendBuff, sizeof(sendBuff), 0);
	    cout << "Mensaje enviado: " << sendBuff << endl;

		if (strcmp(recvBuff, "Agur") != 0) {

            if (opcion == 1) {
                // ZAPATILLAS

            } else if (opcion == 2) {
                // ROPA

            } else if (opcion == 3) {
                // MATERIAL

            } else (opcion == 4) {
			
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

        

	// CLOSING the socket and cleaning Winsock...
	closesocket(s);
	WSACleanup();

	return 0;
}

