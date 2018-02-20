/*
 * tcp_interaction.h
 *
 *  Created on: Feb 20, 2018
 *      Author: bas
 */

#ifndef INCLUDE_TCP_INTERACTION_H_
#define INCLUDE_TCP_INTERACTION_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int port;
	int connected;
} TCP_connection;

int start_connection(int, TCP_connection*);
int send_TCP_message(char*, TCP_connection*);
char* receive_TCP_message(TCP_connection*);
int terminate_connection(TCP_connection*);

#endif /* INCLUDE_TCP_INTERACTION_H_ */
