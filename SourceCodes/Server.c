/*
    Server.c
    Programmer: Ka Son Chan KaSonChan@my.unt.edu
    Class: CSCE 3530, Spring 2013
    Due: Mar 24, 2013
    cse01.cse.unt.edu
    Description: This progrom is for the server side to accept and receive some math result from client.
    The program allows either TCP or UDP connection.
 */

#include "ServerFunctions.h"

#include <stdio.h>
#include <stdlib.h>

#define PROMPT ">>> "
#define OPERAND_DIGIT_SIZE 8

int main(int argc, char * argv[])
{
	// Variable declarations
	int connectionType;
	int portNum;

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

	// Call TCPServer() function to set up connection
	if(connectionType == 1)
	{
		TCPServer(portNum);
	}
	// Call UDPServer() function to set up connection
	else if(connectionType == 2)
	{
		UDPServer(portNum);
	}

	return 0;
}