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
 * Count the number of vowel
 * @param string_to_analyze - the string to analyze
 * @return vowel_nbr - number of vowel in a string
 */
unsigned int string_vowel_analyzer(char* string_to_analyze){
    unsigned int vowel_nbr = 0;
	size_t indexer;
	size_t strLen = strlen(string_to_analyze);
	char oneChar;

    indexer = 0;
	while(indexer < strLen){
		oneChar = string_to_analyze[indexer];
        vowel_nbr += ifVowel(oneChar);
        indexer++;
	}
	return(vowel_nbr);
}

/*!
 * Define if the char is a vowel or not
 * @param oneChar - the chat to analyze
 * @return - Return 1 if the char is a vowel or return 0 if not
 */
unsigned int ifVowel(char oneChar) {
    if(oneChar == 'a' || oneChar == 'A'
       || oneChar == 'e' || oneChar == 'E'
       || oneChar == 'i' || oneChar == 'I'
       || oneChar == 'o' || oneChar == 'O'
       || oneChar == 'u' || oneChar == 'U' ) {
			return(1);
		}
    return(0);
}

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
 * Convert one int in a string
 * @param vowel_numb - int to convert
 * @param string - the string result of conversion
 */
void convertInToString(int vowel_numb, char* string){
    cleanString(string); /* Clean the string for reuse propose*/
    snprintf(string, BUFFERSIZE, "%d", vowel_numb );
    return;
}

/*!
 * Receive a string ad output the number of vowel find
 * @param cad - Structure containing client data
 * @param socket - Socket for communication
 * @param cadSize - Size of cad structure
 * @param string - String for storing data
 * @param vowel_numb - Number of vowel find
 * @return - Return the number of vowel in string param
 */
int
receiveStringCalculateVolweSendtoClientResult(struct sockaddr_in *cad, int socket, unsigned int *cadSize,
                                              char *string, int vowel_numb) {
    receive_string(socket, string, cad, cadSize); /*Receive string to analyze*/
    vowel_numb = string_vowel_analyzer(string);
    convertInToString(vowel_numb, string);/*Calculate number of vowel and convert*/
    send_string(string, socket, BUFFERSIZE, cad, *cadSize);
    return vowel_numb;
}
