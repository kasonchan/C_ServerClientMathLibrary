/*
    README.txt
    Programmer: Ka Son Chan KaSonChan@my.unt.edu
    Class: CSCE 3530, Spring 2013
    Due: Mar 24, 2013
    cse01.cse.unt.edu
    Description: This README.txt file contains instructions how to compile and execute the programs.
 */

(1) To compile program, input the following command
% make Server Client clean

(2) To run/execute Server, input the following command
% ./Server

(3) To run/execute Client, input the following command
% ./Client
*Please input "localhost" as the hostname

Sample result of Server side:
kc0284@cse01:~/public_html/CSCE3530/Project1$ ./Server
Enter the number of the connection type: (1) TCP or (2) UDP.
>>> 2
Enter a port number.
>>> 51717
Setting up UDP server...
Waiting for client...
Receiving a datagram... 
103500001111000111110000001
Calculating... 15 - 31 = -16
Receiving a datagram... 
103500000111000001100000000
Calculating... 7 + 6 = 13
Receiving a datagram... 
103500001111000011000000000
Calculating... 15 + 12 = 27

Sample result of the client side:
kc0284@cse01:~/public_html/CSCE3530/Project1$ ./Client
Enter the number of the connection type: (1) TCP or (2) UDP.
>>> 2
Enter the host name.
>>> localhost
Enter a port number.
>>> 51717
Enter a opcode in binary of 7 digits
Enter 0000000 for +
Enter 0000001 for -
Enter 0000010 for *
Enter 0000011 for /
>>> 00000001
Error! Invalid opcode.
>>> 00000
Error! Invalid opcode.
>>> 0000000
Enter a binary number for the first operand.
>>> 111
Enter a binary number for the second operand.
>>> 110
103500000111000001100000000
Setting up UDP client...
Sending to datagram: 103500000111000001100000000
Got an ack... Result: 13
