/*
 * main.c
 *
 *  Created on: 19/ott/2016
 *      Author: luciano
 */

#include <netdb.h>
#include "dati_globali.h"
#include "initializeEnvironment.h"
#include "sendReceive.h"
#include "connection.h"
#include "operation.h"

int main(void) {
	int clientSocket;
	struct sockaddr_in sad;
    char welcomeString[BUFFERSIZE] = {"Hello"}; //Inizializza la stringa vuota
    char string2[BUFFERSIZE] = {""};
    char string3[BUFFERSIZE] = {""};
    unsigned int sadSize;
    char hostnameServer[BUFFERSIZE] = {""};
    triplaStringhe triplaInvioRicevi = {NULL, NULL, NULL};
    char stringa_quit[BUFFERSIZE] = {"bye"};

	winSock(); //Int Socket se windows

    memset(&sad, 0, sizeof(sad));
    sadSize=sizeof(sad);
    printf("Insert Server hostname: ");
    scanf("%s", hostnameServer);

    socketCreation(&clientSocket);
        if(defineServerIpByHostname(&sad, hostnameServer, readConnectionPortNumber()) == 0) {

            send_string(welcomeString, clientSocket, (int)strlen(welcomeString), &sad, sizeof(sad));
            receive_string(clientSocket, string2, &sad, &sadSize);//Riceve eventuale OK
            puts(string2);//Stampa eventuale OK

            do {
                freeStruct(&triplaInvioRicevi);

                triplaInvioRicevi.stringaA = (char *) calloc(BUFFERSIZE, sizeof(char));
                triplaInvioRicevi.stringaB = (char *) calloc(BUFFERSIZE, sizeof(char));
                triplaInvioRicevi.stringaC = (char *) calloc(BUFFERSIZE, sizeof(char));

                cleanString(string3);

                puts("");
                printf("inserire il contenuto della stringa A: ");
                scanf("%s", string3);
                strcpy(triplaInvioRicevi.stringaA, string3);
                puts("");

                cleanString(string3);
                printf("inserire il contenuto della stringa B: ");
                scanf("%s", string3);
                strcpy(triplaInvioRicevi.stringaB, string3);


                if (send_triplaStringhe(triplaInvioRicevi, clientSocket, &sad, sizeof(sad)) == 0) {

                    freeStruct(&triplaInvioRicevi);
                    if (receive_triplaStringhe(&triplaInvioRicevi, clientSocket, &sad, sizeof(sad)) == 0) {
                        puts(triplaInvioRicevi.stringaC);
                    }
                } else {
                    puts("Errore durante l'invio");
                }
            } while (strcmp(triplaInvioRicevi.stringaC, stringa_quit) != 0);            //Se ricevo quit, esco dal ciclo


        }

        closeConnection(clientSocket);
        printf("\n"); // Print a final linefeed

    #if defined WIN32
        system("pause");
    #else
        getchar();
    #endif

	return (0);
}