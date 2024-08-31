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
		bzero(buff, sizeof(buff));

        printf("Enter the string: ");
        n = 0;

		// copy client message in the buffer
		while ((buff[n++] = getchar()) != '\n');

		// send the message to the server
		write(connfd, buff, sizeof(buff));

		bzero(buff, MAX);
		// read the message from server and copy it in buffer
		read(connfd, buff, sizeof(buff));
		// print the message present in buffer
		printf("From server: %s", buff);

		// if message is exit then exit end the connection
		if((strncmp("exit", buff, 4)) == 0){
			printf("Client Exit....\n");
			break;
		}
	}


}

int main(){
	int sockfd;
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

	// connection with server socket 
	int is_bind = connect(sockfd, (SA*)&server_addr, sizeof(server_addr));
	if(is_bind != 0){
		printf("connection with server failed...\n");
		exit(0);
	}else{
		printf("connection with server successfully created...\n");
	}

	// chatting between client and server
	chat(sockfd);

	// closing the socket
	close(sockfd);

}
