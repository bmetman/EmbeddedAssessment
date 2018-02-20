/*
 * measurement_client.h
 *
 *  Created on: Feb 17, 2018
 *      Author: bas
 */

#ifndef MEASUREMENT_CLIENT_H_
#define MEASUREMENT_CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <ezxml.h>
#include <tcp_interaction.h>

typedef struct {
	char* descriptor;
	float value;
} measurement;

int start_measurement_server(void);
char* process_client_update(ezxml_t*);
int serve_client_request(ezxml_t*, ezxml_t*);

int number_of_stored_measurements();
int store_measurement(float, char*);
int clear_stored_measurements();
int retrieve_measurements(measurement*);


#endif /* MEASUREMENT_CLIENT_H_ */
