/*
 * temperature_sensor.h
 *
 *  Created on: Feb 18, 2018
 *      Author: bas
 */

#ifndef SRC_SENSOR_INTERFACE_H_
#define SRC_SENSOR_INTERFACE_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <ezxml.h>

#define MAX_MEASUREMENT 100
#define MAX_TAG_LENGTH 50
#define MAX_VAL_STRING_LENGTH 10

typedef struct {
	char* name;
	int number_of_sensors;
	char** sensor_tags;
	int server_port;
	int delay_in_seconds;
	float* measurements;
	char** string_measurements;
} sensor;

void create_sensor(sensor*, char*, int, char**, int, int);
int destroy_sensor(sensor*);
float* measure(sensor*);
void delay(sensor*);
ezxml_t convert_to_update(float*, sensor*);
int send_to_port(ezxml_t, sensor*);

#endif /* SRC_SENSOR_INTERFACE_H_ */
