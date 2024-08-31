#include<stdio.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include <unistd.h> 

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

// Chat between client and server using TCP

void chat(int connfd){
	char buff[MAX];
	int n;

	// infinite loop for chat between client and server
	for(;;){
		bzero(buff, MAX);

		// read the message from client and copy it in buffer
		read(connfd, buff, sizeof(buff));

		// print the message present in buffer
		printf("From client: %s\t To client : ", buff);

		bzero(buff, MAX);
		n = 0;
		// copy server message in the buffer
		while ((buff[n++] = getchar()) != '\n');

		// send the message to the client
		write(connfd, buff, sizeof(buff));

		// if message is exit then exit end the connection
		if(strncmp("exit", buff, 4) == 0){
			printf("Server Exit....\n");
			break;
		}
	}


}

int main(){
	int sockfd, connfd;
	struct sockaddr_in server_addr, client_addr;

	// create socket and verify it
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1){
		printf("Socket connection failed...\n");
		exit(0);
	}else{
		printf("Socket created successfully...\n");
	}
	bzero(&server_addr, sizeof(server_addr));

	// assign IP and PORT
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	server_addr.sin_port = htons(PORT);

	// Bind socket to IP and verify
	int is_bind = bind(sockfd, (SA*)&server_addr, sizeof(server_addr));
	if(is_bind != 0){
		printf("socket bind failed...\n");
		exit(0);
	}else{
		printf("Socket successfully binded...\n");
	}

	// server is ready to listen and verify
	if((listen(sockfd, 5)) != 0){
		printf("listen failed....\n");
		exit(0);
	}else{
		printf("Sever is listening....\n");
	}
	socklen_t len = sizeof(client_addr);

	// accept the data from client and verify
	connfd = accept(sockfd, (SA*)&client_addr, &len);
	if(connfd < 0){
		printf("server accept failed...\n");
		exit(0);
	}else{
		printf("server accept the client...\n");
	}

	// chatting between client and server
	chat(connfd);

	// closing the socket
	close(sockfd);
	return 0;
}
