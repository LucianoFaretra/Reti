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
	char stringa_quit[BUFFERSIZE] = {"bye"};
    char stringaBenvenutoServer[BUFFERSIZE];
    char ipServer[16];                                                                                                     //Variabile contenente l'indirizzo IP del server
    u_short serverPort;
    triplaStringhe triplaInvioRicevi = {NULL, NULL, NULL};
    char rispostaElaborazione[BUFFERSIZE];

	winSock(); //Int Socket se windows

    printf("Inserisci l'indirizzo IP del server da contattare: ");
    scanf("%s", ipServer);
    puts("");
    printf("Inserisci la porta con cui contattare il server: ");
    puts("");
    scanf("%hu", &serverPort);



    if (creazioneSocket(&Csocket) == 0) { // CREAZIONE DELLA SOCKET
		costruzioneIpServer(&sad, ipServer, serverPort); // COSTRUZIONE DELL’INDIRIZZO DEL SERVER

		if (connectionToServer(Csocket, &sad, sizeof(sad)) == 0) { // CONNESSIONE AL SERVER
			receive_string(Csocket, stringaBenvenutoServer); // RICEVERE DATI DAL SERVER
            puts(stringaBenvenutoServer);

            do{
				if(triplaInvioRicevi.stringaA != NULL){
					free(triplaInvioRicevi.stringaA);
                    triplaInvioRicevi.stringaA = NULL;
				}
                if(triplaInvioRicevi.stringaB != NULL){
                    free(triplaInvioRicevi.stringaB);
                    triplaInvioRicevi.stringaB = NULL;
                }
                if(triplaInvioRicevi.stringaC != NULL){
                    free(triplaInvioRicevi.stringaC);
                    triplaInvioRicevi.stringaC = NULL;
                }

                triplaInvioRicevi.stringaA = (char*) calloc (BUFFERSIZE,sizeof(char));
                triplaInvioRicevi.stringaB = (char*) calloc (BUFFERSIZE,sizeof(char));
                triplaInvioRicevi.stringaC = (char*) calloc (BUFFERSIZE,sizeof(char));


				puts("");
				printf("inserire il contenuto della stringa A: ");
				scanf("%s", triplaInvioRicevi.stringaA);            //Leggi la stringa A
				puts("");
				printf("inserire il contenuto della stringa B: ");
				scanf("%s", triplaInvioRicevi.stringaB);            //Leggi la stringa A

                if(send_triplaStringhe(triplaInvioRicevi, Csocket) == 0){
                    if(receive_string(Csocket, rispostaElaborazione) == 0){
                        puts(rispostaElaborazione);
                    }
                }
			}while(strcmp(rispostaElaborazione, stringa_quit) != 0);			//Se ricevo quit, esco dal ciclo

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
