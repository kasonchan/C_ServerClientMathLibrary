Server:	Server.o ServerFunctions.o ServerFunctions.h
	gcc ServerFunctions.o Server.o -lm -o Server

Client:	Client.o ClientFunctions.o ClientFunctions.h
	gcc ClientFunctions.o Client.o -lm -o Client

Server.o:	ServerFunctions.h ServerFunctions.c Server.c

Client.o:	ClientFunctions.h ClientFunctions.c Client.c

clean:
	rm -f *.o
