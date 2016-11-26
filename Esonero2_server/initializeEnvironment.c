/*
 * initialize.c
 *
 *  Created on: 19 ott 2016
 *      Author: luciano
 */
#include "dati_globali.h"
#include "initializeEnvironment.h"

void ErrorHandler(char *errorMessage) {
	printf("%s", errorMessage);
}

void winSock(){
#if defined WIN32
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2 ,2), &wsaData);
	if (iResult != 0) {
		printf ("error at WSAStartup\n");
		return 0;
	}
#endif
}
