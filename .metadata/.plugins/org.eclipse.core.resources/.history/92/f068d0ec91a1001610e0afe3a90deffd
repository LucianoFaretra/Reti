/*
 * main.c
 *
 *  Created on: 19/ott/2016
 *      Author: luciano
 */

#include "dati_globali.h"
#include "initializeEnvironment.h"
#include "sendReceive.h"
#include "connection.h"

int main(void) {
	int Csocket;
	struct sockaddr_in sad;
	memset(&sad, 0, sizeof(sad));
	char stringa1[BUFFERSIZE] = { "" }; //Inizializza la stringa vuota
	char stringa2[BUFFERSIZE] = { "" }; //Inizializza la stringa vuota

	winSock(); //Int Socket se windows

	if (creazioneSocket(&Csocket) == 0) { // CREAZIONE DELLA SOCKET
		costruzioneIpServer(&sad); // COSTRUZIONE DELL’INDIRIZZO DEL SERVER

		if (connectionToServer(Csocket, &sad, sizeof(sad)) == 0) { // CONNESSIONE AL SERVER
			receive_string(Csocket, stringa1); // RICEVERE DATI DAL SERVER
			puts("");
			printf("inserire la prima stringa: ");

			scanf("%s", stringa1);								//Leggi prima stringa
			send_string(stringa1, Csocket, sizeof(stringa1));	//Invia stringa al server
			puts("");
			printf("inserire la seconda stringa: ");

			scanf("%s", stringa2);								//Leggi seconda stringa
			send_string(stringa2, Csocket, sizeof(stringa2));	//Invia la stringa al server

			puts("");
			if (receive_string(Csocket, stringa1) == 0) {		//Ricevi stringa dal server
				receive_string(Csocket, stringa2);				//Ricevi stringa dal server
			}

			closeConnection(Csocket); 							// CHIUSURA DELLA CONNESSIONE
			printf("\n"); // Print a final linefeed

			#if defined WIN32
				system("pause");
			#else
				getchar();
			#endif
		}
	}
	return (0);
}
