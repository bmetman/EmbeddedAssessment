/*
 * temperature_sensor.c
 *
 *  Created on: Feb 18, 2018
 *      Author: bas
 */

#include "../include/sensor_interface.h"

// helper function to generate a common sensor struct
void create_sensor(sensor* place_holder, char* name, int number_of_sensors, char** sensor_tags, int server_port, int delay_in_seconds){

	//seed randomizer
	srand((unsigned int)time(NULL));

	sensor si;
	place_holder->name = name;
	place_holder->number_of_sensors = number_of_sensors;

	//allocating memory for the number of sensor tags
	place_holder->sensor_tags = malloc(number_of_sensors * sizeof(char*));

	//the actual tags are provided in stack memory, so no allocation
	for (int i = 0; i < number_of_sensors; i++){
		place_holder->sensor_tags[i] = sensor_tags[i];
	}

	place_holder->server_port = server_port;
	place_holder->delay_in_seconds = delay_in_seconds;
}

// helper function to destroy sensor struct
int destroy_sensor(sensor* current_sensor){

	//only attribute which is malloced
	free(current_sensor->sensor_tags);
	return EXIT_SUCCESS;
}

// get new sensor measurements
// the actual measurement is mocked by a randomizer
float* measure(sensor* current_sensor){

	float* result = (float *) malloc(current_sensor->number_of_sensors);
	float random_measurement;
	for(int i = 0; i < current_sensor->number_of_sensors; i++){
		random_measurement = ((float)rand()/(float)(RAND_MAX)) * MAX_MEASUREMENT;
		result[i] = random_measurement;
	}
	return result;
}

void delay(sensor* current_sensor){
	return;
}

char* convert_to_update(float* measurements, sensor* current_sensor){
	return "TODO";
}

int send_to_port(char* XML, sensor* current_sensor){
	return EXIT_FAILURE;
}


