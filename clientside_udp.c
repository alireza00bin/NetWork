// Client side implementation of UDP client-server model
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
	char dns[100], server_message[100], client_message[100];
	struct sockaddr_in	 servaddr;
	
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);
	
	printf("Enter message: ");
    scanf("%s", dns);
	strcpy(client_message, dns);
	printf("%s\n", client_message);
	unsigned int len;
	if(sendto(sockfd, (char *)client_message, strlen(client_message),
		MSG_CONFIRM, (struct sockaddr*) &servaddr,
			sizeof(servaddr)) < 0){
        printf("Unable to send message\n");
        exit(0);
    }

	if(recvfrom(sockfd, (char *)server_message, 99,
				MSG_WAITALL, (struct sockaddr*) &servaddr,
				&len) < 0){
        printf("Error while receiving server's msg!\n");
        exit(0);
    }		
	printf("Server : %s\n", server_message);
	
	close(sockfd);
}
