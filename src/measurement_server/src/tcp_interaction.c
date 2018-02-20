/*
 * tcp_interaction.c
 *
 *  Created on: Feb 20, 2018
 *      Author: bas
 */

#include "../include/tcp_interaction.h"

//TODO: implement TCP connection
int start_connection(int port, TCP_connection* conn){

	conn->port = port;
	conn->connected = 1;
	printf("STARTED TCP CONNECTION ON PORT: %i\n", port);
	return EXIT_SUCCESS;
}

//TODO: implement sending
int send_TCP_message(char* message, TCP_connection* conn){
	if(conn->connected){
		printf("SENDING MESSAGE %s over port %i successful\n", message, conn->port);
		return EXIT_SUCCESS;
	} else {
		printf("SENDING MESSAGE FAILED");
		return EXIT_FAILURE;
	}
}

char* receive_TCP_message(TCP_connection* conn){
	if(conn->connected){
		return "MESSAGE";
	} else {
		return "";
	}
}

int terminate_connection(TCP_connection* conn){
	if(conn->connected){
		conn->connected = 0;
		printf("TERMINATED TCP CONNECTION ON PORT: %i\n", conn->port);
		return EXIT_SUCCESS;
	} else {
		printf("FAILED TERMINATED TCP CONNECTION");
		return EXIT_FAILURE;
	}
}
