/*
 * operation.c
 *
 *  Created on: 24 nov 2016
 *      Author: ibanez89
 */
#include "dati_globali.h"
#include "sendReceive.h"
#include "operation.h"

/*!
 * Clean String for reuse
 * @param string - String to clean
 * @def BUFFERSIZE - size of the string
 */
void cleanString(char* string) {
    memset( string, 0x00, BUFFERSIZE );
    return;
}
/*!
 * Do the server operation
 * @param clientSocket - socket for communication
 * @param sad - server information
 * @param welcomeString - welcome string
 * @param stringa2 - buffer string
 * @var nmbVowel - var containing vowel numbers
 * @param sadSize - size of the sad struct
 * @return nmbVowel - return the number of vowel
 */
int serverCycle(int clientSocket, struct sockaddr_in *sad, char *welcomeString, char *stringa2, unsigned int *sadSize) {
    send_string(welcomeString, clientSocket, (int) strlen(welcomeString), sad, sizeof((*sad)));
    receive_string(clientSocket, stringa2, sad, sadSize);
    puts(stringa2);

    int nmbVowel;

    cleanString(stringa2);
    printf("Insert an alphanumeric string: ");
    scanf("%s", stringa2);
    send_string(stringa2, clientSocket, (int) strlen(welcomeString), sad, sizeof((*sad)));

    //TODO receive a int
    receive_int(clientSocket, &nmbVowel, sad, sadSize);

    if ((nmbVowel % EVEN) == 0) {
        printf("%d: Numero di vocali pari. Fine esecuzione", nmbVowel);
    } else {
        printf("%d: Numero di vocali dispari. Continua l'inserimento", nmbVowel);
    }
    return nmbVowel;
}
