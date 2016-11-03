/*
 * connection.c
 *
 *  Created on: 20 ott 2016
 *      Author: luciano
 */
#include "dati_globali.h"
#include "connection.h"
#include "initializeEnvironment.h"

void ClearWinSock() {
#if defined WIN32
	WSACleanup();
#endif
}


/**
 * Crea socket del client utilizzato per le comunicazioni,
 * viene utilizzato un puntatore ad intero per restituire
 * il valore assegnato alla socket alla funazione chiamante.
 *
 * Restituisce 0 se la creazione della socket ha avuto successo.
 * Restituisce 1 se la creazione della socket è fallita
 */
int creazioneSocket(int* Csocket){
	int esito = 0;
	*Csocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Csocket < 0) {
		ErrorHandler("socket creation failed.\n");
		closesocket(*Csocket);
		ClearWinSock();
		esito = 1;
	}
	return (esito);
}

/**
 *Assegna alla struttura sad - serveraddress - i dati del server
 *PROTOPORT = varibiale globale contenente la porta utilizzata dal server
 */
void costruzioneIpServer(struct sockaddr_in* sad){
	sad->sin_family = AF_INET;
	(*sad).sin_addr.s_addr = inet_addr("127.0.0.1"); // IP del server
	sad->sin_port = htons(PROTOPORT); // Server port
	return;
}

/**
 * Effettua una connessione al server utilizzando i dati contenuti nella
 * struttura sad. Per la funzione connect è necessario effettuare un cast
 * di sad da sockaddr_in a sockaddr
 * sad = struttura contenente i dati di connessione
 * structSize = variabile di tipo size_t contenente il footprint in memoria della
 * struttura passata come puntatore.
 *
 * Restituisce 0 se il tentativo di connessione ha avuto successo
 * Restituisce 1 se il tentativo di connessione è fallito
 */
int connectionToServer(int Csocket, struct sockaddr_in* sad, size_t structSize){
	int esito = 0;

	if (connect(Csocket, (struct sockaddr *) sad, structSize) < 0) {//Cast a sockaddr
		ErrorHandler("Failed to connect.\n");
		closesocket(Csocket);
		ClearWinSock();
		esito = 1;
	}
	return(esito);
}
/*
 * Chiude il socket inserito come paramentro
 */
void closeConnection(int socket){
	closesocket(socket);
	ClearWinSock();
	return;
}
