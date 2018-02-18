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

#define MAX_MEASUREMENT 100
#define MAX_TAG_LENGTH 50

typedef struct {
	char* name;
	int number_of_sensors;
	char** sensor_tags;
	int server_port;
	int delay_in_seconds;
} sensor;

void create_sensor(sensor*, char*, int, char**, int, int);
int destroy_sensor(sensor*);
float* measure(sensor*);
void delay(sensor*);
char* convert_to_update(float*, sensor*);
int send_to_port(char*, sensor*);

#endif /* SRC_SENSOR_INTERFACE_H_ */
