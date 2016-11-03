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

int send_string(char* stringa, int Ssocket, unsigned int stringLen){
	int esito = 0;
	char buf[BUFFERSIZE] = {""};
	size_t index = 0;
	while(index < stringLen){
		buf[index] = stringa[index];
		index++;
	}
	buf[index] = '\0';
	if (send(Ssocket, buf, BUFFERSIZE - 1, 0) != BUFFERSIZE - 1) {// INVIA DATI AL SERVER
		ErrorHandler("send()sent a different number of bytes than expected");
		esito = 1;
	}
	return(esito);
}

int receive_string(int Rsocket, char buf[BUFFERSIZE]){

	size_t bytesRcvd;
	int esito = 0;

	bytesRcvd = 0;
	if ((bytesRcvd = recv(Rsocket, buf, BUFFERSIZE - 1, 0)) > 0) {
		buf[bytesRcvd] = '\0'; // Add \0 so printf knows where to stop
		puts(buf); // Print the echo buffer
	}
	else{
		ErrorHandler("recv() failed or connection closed prematurely");
		closesocket(Rsocket);
		ClearWinSock();
		esito = 1;
	}
	return(esito);
}
