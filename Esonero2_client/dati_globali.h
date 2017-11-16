/*
 * dati_globali.h
 *
 *  Created on: 19 ott 2016
 *      Author: luciano
 */

#ifndef DATI_GLOBALI_H_
#define DATI_GLOBALI_H_

#if defined WIN32
#include <winsock.h>
#else
#define closesocket close
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFERSIZE 500 //Grandezza buffer invio/ricezione
#define PORTMIN 1024
#define PORTMAX 49151
#define DEFPORT 18000

typedef struct {
    char *stringaA;
    char *stringaB;
    char *stringaC;
} triplaStringhe;

#endif /* DATI_GLOBALI_H_ */
