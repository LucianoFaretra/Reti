#ifndef CONNECTION_H_
#define CONNECTION_H_

int creazioneSocket(int* Csocket);
void costruzioneIpServer(struct sockaddr_in* sad);
void ClearWinSock();
int connectionToServer(int Csocket, struct sockaddr_in* sad, size_t structSize);
void closeConnection(int socket);
int socketAscoltoDati(int ServerSocket);
int connectionAccept(struct sockaddr_in* cad, int serverSocket, int* clientSocket, unsigned int* clientLen, size_t cadSize);
int bindIp(int serverSocket, struct sockaddr_in* sad, size_t sadSize);
int setSocketInAscolto(int serverSocket);
void avviaRoutineServer(struct sockaddr_in* cad, int serverSocket, int* clientSocket, unsigned int* cadSize );

#endif /* CONNECTION_H_ */
