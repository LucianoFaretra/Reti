/*
 * connection.c
 *
 *  Created on: 20 ott 2016
 *      Author: luciano
 */
#include <netdb.h>
#include "dati_globali.h"
#include "connection.h"
#include "initializeEnvironment.h"
#include "sendReceive.h"
#include "operation.h"

void ClearWinSock() {
#if defined WIN32
	WSACleanup();
#endif
}

/*!
 *
 * @param connectionSocket - Pointer to Server socket ID var
 * @return - 0 if Success, 1 if Fault
 *
 * @var result - bool variable for exit state
 */
int socketCreation(int *connectionSocket){
	int result = 0;
	*connectionSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (connectionSocket < 0) {
		ErrorHandler("connectionSocket creation failed.\n");
		closesocket(*connectionSocket);
		ClearWinSock();
		result = 1;
	}
	return (result);
}

/*!
 * Construct the server address structure
 * @param sad - Pointer to server address structure containing the information for connect to the server
 */
void defineServerIp(struct sockaddr_in *sad){
	sad->sin_family = AF_INET;
	(*sad).sin_addr.s_addr = inet_addr("127.0.0.1");    // Server IP address
	sad->sin_port = htons(PROTOPORT);   // Server port
	return;
}

/*!
 * Bind ip to socket
 * @param socket - Socket to bind
 * @param sad - Pointer to Server Address structure
 * @param sadSize - Server address structure size
 * @return - bool value, 0 success, 1 fault
 */
int bindIp(int socket, struct sockaddr_in* sad, size_t sadSize){
	int result = 0;
	if (bind(socket, (struct sockaddr*) sad, (socklen_t)sadSize) < 0) {
		ErrorHandler("bind() failed.\n");
		closesocket(socket);
		ClearWinSock();
		result = 1;
	}
	return(result);
}

/*!
 * Start server cycle
 * @param cad - Structure containing client information
 * @param socket - Socket used for connection
 * @param cadSize - Size of cad structure
 * @var string - String used for storing data
 * @var welcomeString - String containing welcome message
 * @var escapeValue - boolean escape value
 * @var vowel_numb - number of vowel in a string
 */
void startServerCycle(struct sockaddr_in *cad, int socket, unsigned int* cadSize){
	char string[BUFFERSIZE] = {""};
    char *welcomeString = "messaggio ricevuto";
	int escapeValue;
    struct hostent* host;
    struct in_addr addr;
    triplaStringhe *triplaStringhe1 = (triplaStringhe *) calloc(1, sizeof(triplaStringhe));
    char stringa_QUIT[BUFFERSIZE] = {"bye"};
    char stringa_CONTAIN[BUFFERSIZE] = {"quit"};

	/*puts("Waiting for a client to connect...");*/
	for (;;) { //Infinite loop for server execution

        receive_string( socket, string, cad, cadSize );
        addr.s_addr = inet_addr(inet_ntoa( cad->sin_addr ));
        host = gethostbyaddr((char *)&addr, 4, AF_INET);
        char* canonical_name = host->h_name;
        printf("Stringa '%s' ricevuta dal client con nome host: %s\n", string, canonical_name);

        /* Send a welcome string to the connected client */
		if( send_string( welcomeString, socket, (int)strlen(welcomeString), cad, *cadSize ) == 0 ){

            escapeValue = 0;
			while( escapeValue == 0 ){	/*Close connection with escape set to 1*/
                if (receive_triplaStringhe(triplaStringhe1, socket, cad, *cadSize) ==
                    0) {            //Riceve una struct dal client
                    if ((strstr(triplaStringhe1->stringaA, stringa_CONTAIN) != NULL) ||
                        (strstr(triplaStringhe1->stringaB, stringa_CONTAIN) != NULL)) {
                        cleanString(triplaStringhe1->stringaC);
                        strcpy(triplaStringhe1->stringaC, stringa_QUIT);
                        if ((send_triplaStringhe(triplaStringhe1, socket, cad, *cadSize) == 0)) {
                            escapeValue = 1;
                        } else {
                            puts("Errore durante l'invio");
                            escapeValue = 1;
                        }
                    } else {
                        strcpy(triplaStringhe1->stringaC, triplaStringhe1->stringaA);
                        strcat(triplaStringhe1->stringaC, triplaStringhe1->stringaB);
                        if ((send_triplaStringhe(triplaStringhe1, socket, cad, *cadSize) == 1)) {
                            puts("Errore durante l'invio");
                            escapeValue = 1;
                        }
                    }
				}
			}
		}
	}
}

