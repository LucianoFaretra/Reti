/*
 * operation.h
 *
 *  Created on: 24 nov 2016
 *      Author: ibanez89
 */

#ifndef OPERATION_H_
#define OPERATION_H_

void cleanString(char* string);
unsigned short readConnectionPortNumber();

triplaStringhe *deSerializeStruct(char *daDeSerializzare, unsigned int elementSize);

char *serializeStruct(triplaStringhe daSerializzare, unsigned int elementSize);

void freeStruct(triplaStringhe *daLiberare);


#endif /* OPERATION_H_ */
