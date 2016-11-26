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
    struct sockaddr_in fad;
    char welcomeString[BUFFERSIZE] = { "Client Online..." }; //Inizializza la stringa vuota
    char stringa2[BUFFERSIZE] = {""};
    int nmbVowel = 0;
    unsigned int sadSize;
    char hostnameServer[BUFFERSIZE] = {""};

	winSock(); //Int Socket se windows

    memset(&sad, 0, sizeof(sad));
    sadSize=sizeof(sad);
    //TODO Lettura da stdin hoste numero porta
    printf("Insert Server hostname: ");
    scanf("%s", hostnameServer);

        socketCreation(&clientSocket);
        if(defineServerIpByHostname(&sad, hostnameServer) == 0) {

            do {
                nmbVowel = serverCycle(clientSocket, &sad, welcomeString, stringa2, nmbVowel, &sadSize);
            } while ((nmbVowel % EVEN) != 0);//Exit from cycle if the nbr of vowes is EVEN
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