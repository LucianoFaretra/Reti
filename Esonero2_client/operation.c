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

char *serializeStruct(triplaStringhe daSerializzare, unsigned int elementSize) {


    char *serializzato = calloc(elementSize * 3, sizeof(char));
    int index;

    index = 0;
    while (index < elementSize) {
        serializzato[index] = daSerializzare.stringaA[index];
        index++;
    }

    index = 0;
    while (index < elementSize) {
        serializzato[index + elementSize] = daSerializzare.stringaB[index];
        index++;
    }

    index = 0;
    while (index < elementSize) {
        serializzato[index + elementSize + elementSize] = daSerializzare.stringaC[index];
        index++;
    }

    return serializzato;
}

triplaStringhe *deSerializeStruct(char *daDeSerializzare, unsigned int elementSize) {


    triplaStringhe *deSerializzato;

    deSerializzato = (triplaStringhe *) calloc(1, sizeof(triplaStringhe));


    deSerializzato->stringaA = (char *) calloc(elementSize, sizeof(char));
    deSerializzato->stringaB = (char *) calloc(elementSize, sizeof(char));
    deSerializzato->stringaC = (char *) calloc(elementSize, sizeof(char));

    int index;

    index = 0;
    while (index < elementSize) {
        deSerializzato->stringaA[index] = daDeSerializzare[index];
        index++;
    }

    index = 0;
    while (index < elementSize) {
        deSerializzato->stringaB[index] = daDeSerializzare[index + BUFFERSIZE];
        index++;
    }

    index = 0;
    while (index < elementSize) {
        deSerializzato->stringaC[index] = daDeSerializzare[index + BUFFERSIZE + BUFFERSIZE];
        index++;
    }

    return deSerializzato;
}


void freeStruct(triplaStringhe *daLiberare) {
    if (daLiberare->stringaA != NULL) {
        free(daLiberare->stringaA);
        daLiberare->stringaA = NULL;
    }
    if (daLiberare->stringaB != NULL) {
        free(daLiberare->stringaB);
        daLiberare->stringaB = NULL;
    }
    if (daLiberare->stringaC != NULL) {
        free(daLiberare->stringaC);
        daLiberare->stringaC = NULL;
    }
}
