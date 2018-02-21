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
		printf("SENDING MESSAGE:\n %s over port %i successful\n", message, conn->port);
		return EXIT_SUCCESS;
	} else {
		printf("SENDING MESSAGE FAILED");
		return EXIT_FAILURE;
	}
}

char* receive_TCP_message(TCP_connection* conn){
	if(conn->connected){

		ezxml_t update = ezxml_new("update");
		ezxml_t child_XML;
		child_XML = ezxml_add_child(update, "temperature", 0);
		ezxml_set_txt(child_XML,"25.0");
		child_XML = ezxml_add_child(update, "pressure", 0);
		ezxml_set_txt(child_XML,"42.42");

		char* prettified_update = process_client_update(update);

		ezxml_free(update);

		return prettified_update;
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
