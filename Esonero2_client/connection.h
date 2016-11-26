/*
 * connection.h
 *
 *  Created on: 20 ott 2016
 *      Author: luciano
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_

int socketCreation(int *clientSocket);
int defineServerIpByHostname(struct sockaddr_in *sad, char *hostnameServer);
void ClearWinSock();
int connectionToServer(int Csocket, struct sockaddr_in* sad, size_t structSize);
void closeConnection(int socket);

#endif /* CONNECTION_H_ */
