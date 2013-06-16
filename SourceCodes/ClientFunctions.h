/*
    ClientFunction.h
    Programmer: Ka Son Chan KaSonChan@my.unt.edu
    Class: CSCE 3530, Spring 2013
    Due: Mar 24, 2013
    cse01.cse.unt.edu
    Description: This ClientFunctions.h file contains all the functions declarations that is related to the client side.
 */

#ifndef CLIENT_FUNCTIONS_H
#define CLIENT_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

// Structure declaration
struct hostent * server;
struct hostent * hp;

// TCPClient()
// This function serves as setting up the TCP client
void TCPClient(int portNum, struct hostent * server, char * buffer);

// UDPClient()
// This function serves as setting up the UDP client
void UDPClient(int portNum, struct hostent * hp, char * buffer);

#endif