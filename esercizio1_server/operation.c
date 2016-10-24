/*
  * operation.c
 *
 *  Created on: 24 ott 2016
 *      Author: luciano
 */
#include "dati_globali.h"
#include "operation.h"

void minuscolo_to_MAIUSCOLO(char* stringa, size_t stringLen){
	int ascii;
	size_t index = 0;

	while(index < stringLen){
		ascii = (int)stringa[index];		//Trasforma il carattere in codice ASCII
		if(ascii >= 97 && ascii <= 122){	//Controlla che sia una lettera minuscola
			ascii -= 32;					//Rendi il carattere maiuscolo
			stringa[index] = (char)ascii;	//Salva il carattere modificato nella stringa
		}
		index++;
	}
	return;
}

void MAIUSCOLO_to_minuscolo(char* stringa, size_t stringLen){
	int ascii;
	size_t index = 0;

	while(index < stringLen){
		ascii = (int)stringa[index];		//Trasforma il carattere in codice ASCII
		if(ascii >= 65 && ascii <= 90){		//Controlla che sia una lettera minuscola
			ascii += 32;					//Rendi il carattere maiuscolo
			stringa[index] = (char)ascii;	//Salva il carattere modificato nella stringa
		}
		index++;
	}
	return;
}
