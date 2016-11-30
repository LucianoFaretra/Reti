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
 * @param string2 - buffer string
 * @var nmbVowel - var containing vowel numbers
 * @param sadSize - size of the sad struct
 * @return nmbVowel - return the number of vowel
 */
int serverCycle(int clientSocket, struct sockaddr_in *sad, char *string2, unsigned int *sadSize) {
    int nmbVowel;

    cleanString(string2);
    printf("Insert an alphanumeric string: ");
    scanf("%s", string2);
    send_string(string2, clientSocket, (int) strlen(string2), sad, sizeof((*sad)));

    receive_int(clientSocket, &nmbVowel, sad, sadSize);

    if ((nmbVowel % EVEN) == 0) {
        printf("%d: Numero di vocali pari. Fine esecuzione\n", nmbVowel);
    } else {
        printf("%d: Numero di vocali dispari. Continua l'inserimento\n", nmbVowel);
    }
    return nmbVowel;
}
