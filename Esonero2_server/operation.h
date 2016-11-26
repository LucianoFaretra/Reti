/*
 * operation.h
 *
 *  Created on: 24 nov 2016
 *      Author: ibanez89
 */

#ifndef OPERATION_H_
#define OPERATION_H_

unsigned int string_vowel_analyzer(char* string_to_analyze);
void cleanString(char* string);
void convertInToString(int vowel_numb, char* string);
unsigned int ifVowel(char oneChar);
int receiveStringCalculateVolweSendtoClientResult(struct sockaddr_in *cad, int socket, unsigned int *cadSize,
                                                  char *string, int vowel_numb);

#endif /* OPERATION_H_ */
