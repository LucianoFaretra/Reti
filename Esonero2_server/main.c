/*
 ============================================================================
 Name        : Esercizio1.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include "dati_globali.h"
#include "initializeEnvironment.h"
#include "connection.h"
/*!
 *
 * @param argc - Server port Value
 * @param argv - List of accepted arguments, in fact 2nd argument is the port value
 * @return
 *
 * @var port - int contain server port value
 * @var serverSocket - int contain the server socket ID
 * @struct sad - structure containing server address
 * @struct cad - structure containing client address
 * @var clientAddressLen
 */

int main(int argc, char *argv[]) {
    int port;
    int socket;
    struct sockaddr_in sad;
    struct sockaddr_in cad;
    unsigned int* cadSize;

    *cadSize = sizeof(cad);
    memset(&sad, 0, sizeof(sad));   // ensures that extra bytes contain 0

    if (argc > 1) {
        port = atoi(argv[1]);   // if argument specified convert argument tobinary
    } else
        port = PROTOPORT;     // use default port number
    if (port < 0) {
        printf("bad port number %s \n", argv[1]);
        return 0;
    }
    winSock();    //Int Socket on Windows Systems

    if(socketCreation(&socket) == 0){
        defineServerIp(&sad);
        if(bindIp(socket, &sad, sizeof(sad)) == 0){
            startServerCycle(&cad, socket, cadSize);
        }
    }
    return(0);
}
