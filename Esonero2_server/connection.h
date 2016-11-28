#ifndef CONNECTION_H_
#define CONNECTION_H_

int socketCreation(int *connectionSocket);
void defineServerIp(struct sockaddr_in *sad);
void ClearWinSock();

int bindIp(int socket, struct sockaddr_in* sad, size_t sadSize);
void startServerCycle(struct sockaddr_in *cad, int socket, unsigned int* cadSize);

#endif /* CONNECTION_H_ */
