/*
 * temperature_sensor.c
 *
 *  Created on: Feb 18, 2018
 *      Author: bas
 */

#include "../include/sensor_interface.h"

// helper function to generate a common sensor struct
sensor create_sensor(char* name, int number_of_sensors, char** sensor_tags, int server_port, int delay_in_seconds){

	//seed randomizer
	srand((unsigned int)time(NULL));

	sensor si;
	si.name = name;
	si.number_of_sensors = number_of_sensors;

	for(int i = 0; i < si.number_of_sensors; i++){
		si.sensor_tags[0] = sensor_tags[0];
	}

	si.server_port = server_port;
	si.delay_in_seconds = delay_in_seconds;
	return si;
}

// get new sensor measurements
// the actual measurement is mocked by a randomizer
float* measure(sensor current_sensor){

	float* result = (float *) malloc(current_sensor.number_of_sensors);
	float random_measurement;
	for(int i = 0; i < current_sensor.number_of_sensors; i++){
		random_measurement = ((float)rand()/(float)(RAND_MAX)) * MAX_MEASUREMENT;
		result[i] = random_measurement;
	}
	return result;
}

void delay(sensor current_sensor){
	return;
}

char* convert_to_update(float* measurements, sensor current_sensor){
	return "TODO";
}

int send_to_port(char* XML, sensor current_sensor){
	return EXIT_FAILURE;
}


