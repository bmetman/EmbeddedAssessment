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

typedef struct {
	char* descriptor;
	float value;
} measurement;

int start_measurement_server(void);
char* process_client_update(ezxml_t*);
char* serve_client_request(ezxml_t*);
measurement* store_measurement(float*, char*);
measurement* retrieve_measurement(char*);

#endif /* MEASUREMENT_CLIENT_H_ */
