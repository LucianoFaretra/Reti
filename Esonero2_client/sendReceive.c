/*
 * send.c
 *
 *  Created on: 19 ott 2016
 *      Author: luciano
 */
#include "dati_globali.h"
#include "sendReceive.h"
#include "initializeEnvironment.h"
#include "connection.h"
#include "operation.h"

/*!
 * Send a string to the connected client client
 * @param string - String to send
 * @param socket - Communication socket
 * @param stringLen - Length of string to send
 * @param cad - Client address structure containing the client information for communication propuse
 * @param cadSize - Size of cad structure
 * @return - Return a bool result, 0 for success, 1 for fault
 */
int send_string(char *string, int socket, int stringLen, struct sockaddr_in *cad, unsigned int cadSize) {
	int result = 0;
	char buf[BUFFERSIZE] = {""};
	size_t index = 0;

	while(index < stringLen){ /*Transfer const. string into a buffer*/
		buf[index] = string[index];
		index++;
	}
	buf[index] = '\0';

	if (sendto(socket, buf, BUFFERSIZE, 0, (struct sockaddr *)cad, cadSize) != BUFFERSIZE) {// INVIA DATI AL SERVER
		ErrorHandler("send() sent a different number of bytes than expected");
		result = 1;
	}
	return(result);
}

/*!
 * Receive a string from the server
 * @param socket - communication socket
 * @param buf - buffer to store the string
 * @param cad - structure containing the client to connect information
 * @param cadSize - size of cad structure
 * @return - bool response, 0 for success, 1 for fault
 */
int receive_string(int socket, char *buf, struct sockaddr_in *cad, unsigned int *cadSize) {

	ssize_t bytesRcvd = 0;
	int result = 0;

	cleanString(buf); /* Clean the string for reuse propose*/
	if ((bytesRcvd = recvfrom(socket, buf, BUFFERSIZE, 0, (struct sockaddr*)cad, cadSize)) > 0) {
		buf[bytesRcvd] = '\0'; // Add \0 so printf knows where to stop
	}
	else{
		ErrorHandler("recv() failed or connection closed prematurely");
		closesocket(socket);
		ClearWinSock();
		result = 1;
	}
	return(result);
}