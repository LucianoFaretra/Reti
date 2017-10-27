/*
 * send.h
 *
 *  Created on: 19 ott 2016
 *      Author: luciano
 */

#ifndef SENDRECEIVE_H_
#define SENDRECEIVE_H_

int send_string(const char *stringa, int Csocket, unsigned int stringLen);
int receive_string(int Rsocket, char buf[BUFFERSIZE]);
int receive_triplaStringhe(triplaStringhe *daInviare, int Ssocket);


#endif /* SENDRECEIVE_H_ */
