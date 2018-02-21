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
#include <string.h>
#include <tcp_interaction.h>

#define MAX_STRING_SIZE 200
#define LOG_FILENAME "measurements.log"

typedef struct {
	char* descriptor;
	float value;
	char* string_value;
} measurement;

int start_measurement_server(void);
char* process_client_update(ezxml_t);
ezxml_t serve_client_request(ezxml_t);
char* prettify_status(ezxml_t status);

int number_of_stored_measurements();
int store_measurement(float, char*);
int clear_stored_measurements();
measurement* retrieve_measurements();


#endif /* MEASUREMENT_CLIENT_H_ */
