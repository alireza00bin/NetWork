// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
	
#define PORT 8080	
#define SA struct sockaddr

// Driver code
int main() {
	int sockfd;
	char server_message[100], client_message[100];
	struct sockaddr_in servaddr, cliaddr;
		
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
		
	bzero(&servaddr, sizeof(servaddr));
	bzero(&cliaddr, sizeof(cliaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
		
	// Bind the socket with the server address
	if ( bind(sockfd, (SA*)&servaddr, sizeof(servaddr)) < 0 )
	{
		perror("Bind failed");
		exit(EXIT_FAILURE);
	}
	else
		printf("Socket successfully binded..\n");
		
	unsigned int len;
	
	len = sizeof(cliaddr); //len is value/result
	if (recvfrom(sockfd, (char *)client_message, 99,
				MSG_WAITALL, (SA*) &cliaddr,
				&len) < 0){
        printf("Couldn't receive\n");
        return -1;
    }

	printf("Received message from IP: %s and port: %i\n",
           inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

	printf("Client : %s\n", client_message);

	struct hostent *host = gethostbyname(client_message);
	printf("host by name: %p\n", host);
	struct in_addr a;
	while (*host->h_addr_list != NULL)
	{
		bcopy(*host->h_addr_list++, (char *) &a, sizeof(a));
		char*address = inet_ntoa(a);
		printf("address: %s\n", address);
		strcat(server_message, address);
		strcat(server_message, "\n");
	}
	if (sendto(sockfd, (char *)server_message, strlen(server_message),
		MSG_CONFIRM, (SA*) &cliaddr,
			len) < 0){
        printf("Can't send\n");
        return -1;
    }		
	close(sockfd);
}
