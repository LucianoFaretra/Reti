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
#include "netdb.h"

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
int socketCreation(int *clientSocket){
	int result = 0;
	*clientSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (clientSocket < 0) {
		ErrorHandler("socket creation failed.\n");
		closesocket(*clientSocket);
		ClearWinSock();
		result = 1;
	}
	return (result);
}

/*!
 * Construct the server address structure
 * @param sad - Pointer to server address structure containing the information for connect to the server
 * @param hostnameServer - string containing hostname of the server
 * @var host - hostnet struct
 * @var result - bool, 0 success, 1 fault
 */
int defineServerIpByHostname(struct sockaddr_in *sad, char *hostnameServer, unsigned short serverPort) {
    struct hostent* host;
    int result = 0;
    host = gethostbyname(hostnameServer);
    if(host != NULL){
        unsigned long ul = *((unsigned long *) host->h_addr_list[0]);
        sad->sin_family = AF_INET;
        (*sad).sin_addr.s_addr = (in_addr_t)ul; // IP del server
        sad->sin_port = htons(serverPort); // Server port
    }
    else{
        fprintf(stderr, "gethostbyname() failed.\n");
        result = 1;
    }
	return(result);
}

/*!
 * Close the connection socket
 * @param socket - socket to close
 */
void closeConnection(int socket){
	closesocket(socket);
	ClearWinSock();
	return;
}

/*!
 * Read an int, if in range with unassigned user port return the port to the caller
 * @var numPort - var containing the port read from stdin
 * @var success - bool success status, 1 success, 0 fault
 * @def PORTMIN - minimum port accepted
 * @def PORTMAX - maxinum port accepted
 * @return numPort - The port of the server
 */
unsigned short readConnectionPortNumber() {
    unsigned short numPort;
    int success;
    do {
        printf("Inserire una porta compresa tra 1024 e 49151, port di default: %d: ", DEFPORT);
        scanf("%hu", &numPort);
        if(numPort >= PORTMIN && numPort <= PORTMAX){
            success = 1;
        }
        else{
            printf("Porta %d non disponibile, ripetere l'inserimento!\n", numPort);
            success = 0;
        }
    }while(success == 0);
    return(numPort);
}