/*
    Client.c
    Programmer: Ka Son Chan KaSonChan@my.unt.edu
    Class: CSCE 3530, Spring 2013
    Due: Mar 24, 2013
    cse01.cse.unt.edu
    Description: This progrom for the client side to request and receive some math result from server.
    The program let user to choose either TCP or UDP connection.
 */

#include "ClientFunctions.h"

#include <stdio.h>
#include <stdlib.h>

#define PROMPT ">>> "
#define OPERAND_DIGIT_SIZE 8

int main(int argc, char *argv[])
{
	// Variables declarations and definitions
	int i;
	int enterOp2 = 0;
	int connectionType;
	int portNum;
	char hostname[128 + 1];

    char buffer[128 + 1], operand1[128 + 1], operand2[128 + 1], opcode[128 + 1];

    int op1Digit = 0, op2Digit = 0;

	// Let the user to enter the connection type
	printf("Enter the number of the connection type: (1) TCP or (2) UDP.\n");
	printf(PROMPT);
	scanf("%d", &connectionType);

	// Check the user entered connection type
	while(connectionType > 2 || connectionType < 1)
	{
		printf("Error! Invalid connection type number!\n");
		printf(PROMPT);
		scanf("%d", &connectionType);
	}

    // Let the user to enter the hostname
	printf("Enter the host name.\n");
	printf(PROMPT);
	scanf("%s", hostname);

	// Check the host
	if(connectionType == 1)
	{
	    server = gethostbyname(hostname);
	    if (server == NULL) 
	    {
	        perror("Error! No such host!\n");
	        exit(1);
	    }
	}
	else if(connectionType == 2)
	{
	    hp = gethostbyname(hostname);
	    if (hp == NULL) 
	    {
	        perror("Error! No such host!\n");
	        exit(1);
	    }
	}

	// Let the user to enter the port number
	printf("Enter a port number.\n");
	printf(PROMPT);
	scanf("%d", &portNum);

	// Check the user entered port number
	while(portNum < 0 || connectionType > 60000)
	{
		printf("Error! Invalid connection type number!\n");
		printf(PROMPT);
		scanf("%d", &connectionType);
	}

	// Let the user to enter the opcode
    printf("Enter a opcode in binary of 7 digits\n");
    printf("Enter 0000000 for +\n");
    printf("Enter 0000001 for -\n");
    printf("Enter 0000010 for *\n");
    printf("Enter 0000011 for /\n");
    printf(PROMPT);
    scanf("%s", opcode);

    // Validate the user input opcode
    while(strlen(opcode) != 7)
    {
    	printf("Error! Invalid opcode.\n");
	    printf(PROMPT);
	    scanf("%s", opcode);
    }
    for(;;)
    {
		if(strcmp(opcode, "0000000") == 0)
		{
			break;
		}
		else if(strcmp(opcode, "0000001") == 0)
		{
			break;
		}
		else if(strcmp(opcode, "0000010") == 0)
		{
			break;
		}
		else if(strcmp(opcode, "0000011") == 0)
		{
			break;
		}
		else
	    {
	    	printf("Error! Invalid opcode.\n");
		    printf(PROMPT);
		    scanf("%s", opcode);
	    }
	}

	// Let the user to enter the first operand
    printf("Enter a binary number for the first operand.\n");
    printf(PROMPT);
    scanf("%s", operand1);

    // Validate the user input first operand
    while(strlen(operand1) > 8)
    {
    	printf("Error! Invalid first operand.\n");
	    printf(PROMPT);
	    scanf("%s", operand1);
    }

    // Let the user to enter the second operand
    printf("Enter a binary number for the second operand.\n");
    printf(PROMPT);
    scanf("%s", operand2);

    // Validate the user input first operand
    while(strlen(operand2) > 8)
    {
    	printf("Error! Invalid second operand.\n");
	    printf(PROMPT);
	    scanf("%s", operand2);
    }

    // Compose the packet
    // Version
    strcpy(buffer, "1");
    // Type of Msg
    strcat(buffer, "0");
    // Length of Msg
    strcat(buffer, "35");
    // Operand 1
    if(strlen(operand1) < OPERAND_DIGIT_SIZE)
    {
    	for(i = 0; i < OPERAND_DIGIT_SIZE - strlen(operand1); i++)
    		strcat(buffer, "0");
	    strcat(buffer, operand1);
    }
    else
    	strcat(buffer, operand1);
    // Operand 2
    if(strlen(operand2) < OPERAND_DIGIT_SIZE)
    {
    	for(i = 0; i < OPERAND_DIGIT_SIZE - strlen(operand2); i++)
    		strcat(buffer, "0");
	    strcat(buffer, operand2);
    }
    else
    	strcat(buffer, operand2);
    // Opcode
    strcat(buffer, opcode);

    printf("%s\n", buffer);

    // If user input connection type equals 1, call TCPClient() function
	if(connectionType == 1)
	{
		TCPClient(portNum, server, buffer);
	}
	// Else if user input connection type equals 2, call UDPClient() function
	else if(connectionType == 2)
	{
		UDPClient(portNum, hp, buffer);
	}

	return 0;
}