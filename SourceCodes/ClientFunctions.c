/*
    ClientFunction.c
    Programmer: Ka Son Chan KaSonChan@my.unt.edu
    Class: CSCE 3530, Spring 2013
    Due: Mar 24, 2013
    cse01.cse.unt.edu
    Description: This ClientFunctions.c file contains all the definition of ClientFunctions.h file.
    It contains all functions related to the client side.
 */

#include "ClientFunctions.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

// TCPClient()
// This function serves as setting up the TCP client
void TCPClient(int portNum, struct hostent * server, char * buffer)
{
	// Variables declarations
	int sockfd, n;
    struct sockaddr_in serv_addr;

	// Print statement to notify the user that chosen TCP
	printf("Setting up TCP client...\n");
	printf("Sending packet: %s\n", buffer);

	// Set up the transport end point
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) 
	{
		perror("Error! Socket call failed!\n");
		exit(1);
	}

    // Set up connection
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portNum);

    // Connect the socket to the server's address
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    {
        perror("Error! Connecting failed!\n");
        exit(1);
    }

	// Writing the message
    n = write(sockfd,buffer,strlen(buffer));
    
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);

    // Reading the message
    n = read(sockfd,buffer,255);
    
    if (n < 0) 
         error("ERROR reading from socket");
    printf("Result: %s\n",buffer);
    
    close(sockfd);
}

// UDPClient()
// This function serves as setting up the UDP client
void UDPClient(int portNum, struct hostent * hp, char * buffer)
{
    // Variables declarations
    int sock, n;
    unsigned int length;
    struct sockaddr_in UDPserver, from;

	// Print statement to notify the user that chosen UDP
	printf("Setting up UDP client...\n");
    printf("Sending to datagram: %s\n", buffer);

    // Set up the transport end point
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) 
    {
        perror("Error! Socket call failed!\n");
        exit(1);
    }

    // Set up connection
    UDPserver.sin_family = AF_INET;
    bcopy((char *)hp->h_addr, (char *)&UDPserver.sin_addr, hp->h_length);
    UDPserver.sin_port = htons(portNum);
    length = sizeof(struct sockaddr_in);

    // Sending datagram
    n = sendto(sock, buffer, strlen(buffer), 0, (const struct sockaddr *)&UDPserver, length);
    if (n < 0)
    {
        perror("Error! Sending the packet to datagram\n");
        exit(1);
    }
    
    // Receiving datagram
    n = recvfrom(sock, buffer, 256, 0, (struct sockaddr *)&from, &length);
    if (n < 0)
    {
        perror("Error! Receiving the packet from datagram\n");
        exit(1);
    }
    write(1, "Got an ack... Result: ", 22);
    write(1, buffer, n);
    printf("\n");

    close(sock);
}