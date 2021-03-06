/*
 * connection.c
 *
 *  Created on: 20 ott 2016
 *      Author: luciano
 */
#include "dati_globali.h"
#include "connection.h"
#include "initializeEnvironment.h"
#include "sendReceive.h"

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

	if (connect(Csocket, (struct sockaddr *) sad, structSize) < 0) {
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

/*
 * bind del socket con sad
 * Restituisce 0 se il bind ha avuto successo
 * Restituisce 1 se il bind è fallito
 */
int bindIp(int serverSocket, struct sockaddr_in* sad, size_t sadSize){
	int esito = 0;
	if (bind(serverSocket, (struct sockaddr*) sad, sadSize) < 0) {
		ErrorHandler("bind() failed.\n");
		closesocket(serverSocket);
		ClearWinSock();
		esito = 1;
	}
	return(esito);
}

/*
 * Crea il socket dedicato all'ascolto dei dati per il server
 *
 * serverSocket = socket utilizzato per instaurare la prima connessione
 * QLEN = massimo numero di clienti collegabili simultaneamente
 */
int socketAscoltoDati(int serverSocket){
	int esito = 0;
	if (listen(serverSocket, QLEN) < 0) {//
		ErrorHandler("listen() failed.\n");
		closesocket(serverSocket);
		ClearWinSock();
		esito = 1;
	}
	return(esito);
}

/*
 *La funzione di occupa di stabilire la connessione con il client
 *cad = dati del client
 *serverSocket = valore passato per parametro contentente l'id del socket del server
 *clientSocket = puntatore ad intero contenente il valore del socket del client
 *
 *Restituisce 0 se è stato possibile accettare la connessione
 *Restituisce 1 se non è stato possibile accettare la connessione del client
 */
int connectionAccept(struct sockaddr_in* cad, int serverSocket, int* clientSocket, unsigned int* clientLen, size_t cadSize){
	int esito = 0;
	//puts("Waiting for a client to connect...");
	while (1) { /* oppure for (;;) */
		*clientLen = cadSize; // set the size of the client address
		if ((*clientSocket = accept(serverSocket, (struct sockaddr *) cad, clientLen)) < 0) {//Crea il socket client
			ErrorHandler("accept() failed.\n");
			closesocket(serverSocket);	// CHIUSURA DELLA CONNESSIONE
			ClearWinSock();			// CHIUSURA DELLA CONNESSIONE
			esito = 1;
		}
		//printf("Connessione stabilita con il client il cui indirizzo è: %s\n", inet_ntoa(cad->sin_addr));
	}
	return(esito);
}

/*
 * Imposta la socket del server in ascolto
 * QLEN = massima lunghezza coda client connessi
 *
 * Restituisce 0 se è stato possibile impostare il socket in ascolto
 * Restituisce 1 se non è stato possibile settare il socket in ascolto
 */
int setSocketInAscolto(int serverSocket){
	int esito = 0;
	if (listen(serverSocket, QLEN) < 0) {
		ErrorHandler("listen() failed.\n");
		closesocket(serverSocket);
		ClearWinSock();
		esito = 1;
	}
	return(esito);
}

/*
 * La funzione svolge le routine del server, cioè tutto ciò che il server dovrebbe fare una volta stabilita la connessioen
 *
 */
void avviaRoutineServer(struct sockaddr_in* cad, int serverSocket, int* clientSocket, unsigned int* cadSize ){
	char stringa1[BUFFERSIZE] = {""};
	char stringa_QUIT[BUFFERSIZE] = {"QUIT"};
	char stringa_CONTINUE[BUFFERSIZE] = {"CONTINUE"};
	char* stringaBenvenuto = "connessione avvenuta";
	int stringLen = strlen(stringaBenvenuto); // Determina la lunghezza stringa benvenuto
	int exit;


	puts("Waiting for a client to connect...");
	while (1) { // oppure for (;;) - crea un ciclo infinito per permettere l'esecuzione ad inoltranza del server
		if ((*clientSocket = accept(serverSocket, (struct sockaddr *) cad, cadSize)) < 0) {
			ErrorHandler("accept() failed.\n");
			closesocket(serverSocket);	// CHIUSURA DELLA CONNESSIONE
			ClearWinSock();			// CHIUSURA DELLA CONNESSIONE
		}
		printf("Connessione stabilita con il client il cui indirizzo è: %s\n", inet_ntoa(cad->sin_addr));

		//OPERAZIONI CHE IL SERVER DEVE ESEGUIRE APPENA VIENE STABILITA UNA CONNESSIONE
		if(send_string(stringaBenvenuto, *clientSocket, stringLen) == 0){	//Invia stringa di benvenuto
			exit = 0;														//Inizializza valore escape
			while( exit == 0){												//Controlla se deve chiudere la connessione al client
				if(receive_string(*clientSocket, stringa1) == 0){			//Riceve una stringa dal client
					if(atoi(stringa1)>INTMAX){									//Interpreta la stringa come intero e valuta se maggiore o monore di INTMAX
						send_string(stringa_QUIT, *clientSocket, BUFFERSIZE);		//Invia la stringa al client Per chiudere la connessione
						exit = 1;													//Setta il valore di exit per terminare la routine
					}
					else{
						send_string(stringa_CONTINUE, *clientSocket, BUFFERSIZE);		//Invia la stringa al client per continuare la connessione
					}
				}
			}
		}
	}

}
