/*
 ============================================================================
 Name        : Esercizio1.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include "dati_globali.h"
#include "initializeEnvironment.h"
#include "sendReceive.h"
#include "connection.h"

int main(int argc, char *argv[]) {
	int port;
	int serverSocket;
	struct sockaddr_in sad;
	struct sockaddr_in cad; 	// structure for the client address
	int clientSocket; 			// socket descriptor for the client
	unsigned int cadSize;

	memset(&sad, 0, sizeof(sad)); // ensures that extra bytes contain 0
	memset(&cad, 0, sizeof(cad));

	if (argc > 1) {
		port = atoi(argv[1]); // if argument specified convert argument tobinary
	} else
		port = PROTOPORT; // use default port number
	if (port < 0) {
		printf("bad port number %s \n", argv[1]);
		return 0;
	}

	winSock();//Int Socket se windows


	if(creazioneSocket(&serverSocket) == 0){// CREAZIONE DELLA SOCKET
		costruzioneIpServer(&sad);// COSTRUZIONE DELL’INDIRIZZO DEL SERVER
		if(bindIp(serverSocket, &sad, sizeof(sad)) == 0){//ASSEGNAZIONE INDIRIZZO AL SOCKET
			if(setSocketInAscolto( serverSocket) == 0){// SETTAGGIO DELLA SOCKET ALL'ASCOLTO
				cadSize = sizeof(cad);

				avviaRoutineServer(&cad, serverSocket, &clientSocket, &cadSize);

			}
		}
	}
	return(0);
}
