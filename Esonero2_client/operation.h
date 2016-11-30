/*
 * operation.h
 *
 *  Created on: 24 nov 2016
 *      Author: ibanez89
 */

#ifndef OPERATION_H_
#define OPERATION_H_

void cleanString(char* string);
int serverCycle(int clientSocket, struct sockaddr_in *sad, char *string2, unsigned int *sadSize);
unsigned short readConnectionPortNumber();

#endif /* OPERATION_H_ */
