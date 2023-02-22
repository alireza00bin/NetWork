#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#include <time.h>
#define PORT 8080
#define SA struct sockaddr

// Function designed for chat between client and server.
void serv(int connfd)
{
	char buff[100];
    time_t t = time(NULL);
    snprintf(buff, sizeof(buff), "%s\r\n", ctime(&t));
    printf("Date And Time Sent!\n");
    write(connfd, buff, strlen(buff));
}

// Driver function
int main()
{
	int MAX_Client;
	scanf("%d", &MAX_Client);
	int sockfd, connfd;
	struct sockaddr_in servaddr, cliaddr;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
			printf("socket bind failed...\n");
			exit(0);
		}
	else
		printf("Socket successfully binded..\n");
	int i = 0;
	while (i < MAX_Client) {
		
		// Now server is ready to listen and verification
		if ((listen(sockfd, 5)) != 0) {
			printf("Listen failed...\n");
			exit(0);
		}
		else
			printf("Server listening..\n");
		unsigned int len = sizeof(cliaddr);

		// Accept the data packet from client and verification
		connfd = accept(sockfd, (SA*)&cliaddr, &len);
		if (connfd < 0) {
			printf("server accept failed...\n");
			exit(0);
		}
		else
			printf("server accept the client %d...\n", i++);
		// Function for chatting between client and server
		serv(connfd);
	}

	// After chatting close the socket
	close(sockfd);
}
