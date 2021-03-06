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
	//char stringa2[BUFFERSIZE] = { "" }; //Inizializza la stringa vuota
	char* stringa2;
	char stringa_quit[BUFFERSIZE] = {"QUIT"};

	winSock(); //Int Socket se windows

	if (creazioneSocket(&Csocket) == 0) { // CREAZIONE DELLA SOCKET
		costruzioneIpServer(&sad); // COSTRUZIONE DELL’INDIRIZZO DEL SERVER

		if (connectionToServer(Csocket, &sad, sizeof(sad)) == 0) { // CONNESSIONE AL SERVER
			receive_string(Csocket, stringa1); // RICEVERE DATI DAL SERVER

			do{
				if(stringa2 != NULL){
					free(stringa2);
					stringa2 = NULL;
				}
				stringa2 = (char*)malloc(BUFFERSIZE * sizeof(char));
				puts("");
				printf("inserire un intero: ");

				scanf("%s", stringa2);								//Leggi primo intero
				send_string(stringa2, Csocket, sizeof(stringa2));	//Invia stringa con intero al server
				receive_string(Csocket, stringa2);					//Ricevi esito elaborazione
			}while(strcmp(stringa2, stringa_quit) != 0);			//Se ricevo quit, esco dal ciclo

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
