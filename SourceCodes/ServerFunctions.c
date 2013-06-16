/*
    ClientFunction.c
    Programmer: Ka Son Chan KaSonChan@my.unt.edu
    Class: CSCE 3530, Spring 2013
    Due: Mar 24, 2013
    cse01.cse.unt.edu
    Description: This ServerFunctions.c file contains all the definition of ServerFunctions.h file.
    It contains all functions related to the server side.
 */

#include "ServerFunctions.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <math.h>

// TCPServer()
// This function serves as setting up the TCP server
void TCPServer(int portNum)
{
	// Variable declarations
	int sockfd, newsockfd;
	socklen_t clilen;
	char msg[256], replyMsg[256];
	struct sockaddr_in serv_addr, cli_addr;
	int i, n;

	char operand1[128], operand2[128], opcode[128];
	int op1 = 0, op2 = 0;

	// Print statement to notify the user that chosen TCP
	printf("Setting up TCP server...\n");
	printf("Waiting for client...\n");

	// Set up the transport end point
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0) 
	{
		perror("Error! Socket call failed!\n");
		exit(1);
	}	
	
	bzero((char *) &serv_addr, sizeof(serv_addr));
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portNum);

	// Bind an address to the end point
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
	{
		perror("Error! Bind call failed!\n");
		exit(1);
	}

	// Start listening for incoming connections
	if(listen(sockfd,5) == -1)
	{
		perror("Error! Listen call failed!\n");
		exit(1);
	}
	
	clilen = sizeof(cli_addr);
	
	for(;;)
	{		
		// Accept a connection
		newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		if (newsockfd < 0) 
		{
			perror("Error! Accept call failed!\n");
			exit(1);
		}

		// Reading from the packet
		bzero(msg, 256);
		n = read(newsockfd, msg, 255);
		if (n < 0)
		{
			perror("Error! Failed reading message!\n");
			exit(1);
		}
		printf("Receiving packet: %s\n",msg);

		// Retrieve the first operand, second operand and opcode		
		strncpy(operand1, msg + 4, OPERAND_DIGIT_SIZE);
		operand1[OPERAND_DIGIT_SIZE] = '\0';

		strncpy(operand2, msg + 12, OPERAND_DIGIT_SIZE);
		operand2[OPERAND_DIGIT_SIZE] = '\0';

		strncpy(opcode, msg + 20, OPCODE_DIGIT_SIZE);
		opcode[OPCODE_DIGIT_SIZE] = '\0';
		
		// // Test print the reading from the packet
		// printf("operand1: %s ", operand1);
		// printf("operand2: %s ", operand2);
		// printf("opcode: %s\n", opcode);

		op1 = ConvertBiToDec(operand1);
		op2 = ConvertBiToDec(operand2);

	 	// // Test print the first operand, second operand after conversion from binary to decimal
		// printf("op1: %d ", op1);
		// printf("op2: %d\n", op2);
		// printf("Result %d\n: ", CalculateResult(op1, op2, opcode));

		printf("Calculating... ");
		sprintf(replyMsg, "%d", CalculateResult(op1, op2, opcode));

		// Writing to the packet
		n = write(newsockfd, replyMsg, 28);
		printf("Sending back result...\n");
		if (n < 0)
		{
			perror("Error! Failed writing message!\n");
			exit(1);
		}
	}

	// Close connections
	close(newsockfd);
	close(sockfd);
}

// UDPServer()
// This function serves as setting up the UDP server
void UDPServer(int portNum)
{	
	// Variable declarations
	int sock, length, n;
	socklen_t fromlen;
	struct sockaddr_in server;
	struct sockaddr_in from;
	char buf[256];

	char msg[256], replyMsg[256];
	struct sockaddr_in serv_addr, cli_addr;
	int i;

	char operand1[128], operand2[128], opcode[128];
	int op1 = 0, op2 = 0;

	// Print statement to notify the user that chosen UDP
	printf("Setting up UDP server...\n");
	printf("Waiting for client...\n");

	// Set up the transport end point
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0) 
	{
		perror("Error! Socket call failed!\n");
		exit(1);
	}	
	
	length = sizeof(server);

	bzero(&server,length);
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portNum);

	// Bind an address to the end point
	if (bind(sock, (struct sockaddr *) &serv_addr, length) < 0) 
	{
		perror("Error! Bind call failed!\n");
		exit(1);
	}

	fromlen = sizeof(struct sockaddr_in);
	
	for(;;)
	{
		bzero(buf, 256);

		// Reading and writing the message
		// Reading from the packet
		n = recvfrom(sock, buf, 256, 0, (struct sockaddr *)&from, &fromlen);
		if (n < 0)
		{
			perror("Error! Failed receiving from the datagram!\n");
			exit(1);
		}
		write(1, "Receiving a datagram... \n", 27);
		write(1, buf, n);
		printf("\n");

		// // Used to check if the buffer is receiving correctly
		// printf("%s\n", buf);

		// Retrieve the first operand, second operand and opcode		
		strncpy(operand1, buf + 4, OPERAND_DIGIT_SIZE);
		operand1[OPERAND_DIGIT_SIZE] = '\0';

		strncpy(operand2, buf + 12, OPERAND_DIGIT_SIZE);
		operand2[OPERAND_DIGIT_SIZE] = '\0';

		strncpy(opcode, buf + 20, OPCODE_DIGIT_SIZE);
		opcode[OPCODE_DIGIT_SIZE] = '\0';
		
		// // Test print the reading from the packet
		// printf("operand1: %s ", operand1);
		// printf("operand2: %s ", operand2);
		// printf("opcode: %s\n", opcode);

		op1 = ConvertBiToDec(operand1);
		op2 = ConvertBiToDec(operand2);

	 	// // Test print the first operand, second operand after conversion from binary to decimal
		// printf("op1: %d ", op1);
		// printf("op2: %d\n", op2);
		// printf("Result: %d\n: ", CalculateResult(op1, op2, opcode));

		printf("Calculating... ");
		sprintf(replyMsg, "%d", CalculateResult(op1, op2, opcode));

		// Writing back to the datagram
		n = sendto(sock, replyMsg, strlen(replyMsg), 0, (struct sockaddr *)&from, fromlen);
		if (n < 0)
		{
			perror("Error! Failed writing to the datagram!\n");
			exit(1);
		}	
	}
}

// ConverBiToDec() function
// This function convert binary number to decimal number
int ConvertBiToDec(char * operand)
{
	int i = 0, op = 0;

	// printf("operand: %s\n", operand);

	for(i = 0; i < strlen(operand); i++)
    {
        if(operand[i] == '1')
        {
        	op += pow(2, (strlen(operand) - 1) - i);
        }
    }

    // printf("op: %d\n", op);

    return op;
}

// GetOperator()
// This function translate the opcode and return the matched operator
char GetOperator(char * opcode)
{
	if(strcmp(opcode, "0000000") == 0)
	{
		return '+';
	}
	// Perform subtraction
	else if(strcmp(opcode, "0000001") == 0)
	{
		return '-';
	}
	// Perform multiplication
	else if(strcmp(opcode, "0000010") == 0)
	{
		return '*';
	}
	// Perform division
	else if(strcmp(opcode, "0000011") == 0)
	{
		return '/';
	}
}

// CalculateResult()
// This function calculate the result according to the operand 1, operand 2 and opcode
int CalculateResult(int op1, int op2, char * opcode)
{
	// Perform addition
	if(strcmp(opcode, "0000000") == 0)
	{
		printf("%d + %d = %d\n", op1, op2, op1 + op2);
		return op1 + op2;
	}
	// Perform subtraction
	else if(strcmp(opcode, "0000001") == 0)
	{
		printf("%d - %d = %d\n", op1, op2, op1 - op2);
		return op1 - op2;
	}
	// Perform multiplication
	else if(strcmp(opcode, "0000010") == 0)
	{
		printf("%d * %d = %d\n", op1, op2, op1 * op2);
		return op1 * op2;
	}
	// Perform division
	else if(strcmp(opcode, "0000011") == 0)
	{
		printf("%d / %d = %d\n", op1, op2, op1 / op2);
		return op1 / op2;
	}
}