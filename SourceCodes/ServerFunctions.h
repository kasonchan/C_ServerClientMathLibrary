/*
    ServerFunction.h
    Programmer: Ka Son Chan KaSonChan@my.unt.edu
    Class: CSCE 3530, Spring 2013
    Due: Mar 24, 2013
    cse01.cse.unt.edu
    Description: This ServerFunctions.h file contains all the functions declarations that is related to the server side.
 */

#ifndef SERVER_FUNCTIONS_H
#define SERVER_FUNCTIONS_H

#define OPERAND_DIGIT_SIZE 8
#define OPCODE_DIGIT_SIZE 7

// TCPServer()
// This function serves as setting up the TCP server
void TCPServer(int portNum);

// UDPServer()
// This function serves as setting up the UDP server
void UDPServer(int portNum);

// ConverBiToDec() function
// This function convert binary number to decimal number
int ConvertBiToDec(char * operand);

// GetOperator()
// This function translate the opcode and return the matched operator
char GetOperator(char * opcode);

// CalculateResult()
// This function calculate the result according to the operand 1, operand 2 and opcode
int CalculateResult(int op1, int op2, char * opcode);

#endif