/*
 * temperature_sensor.c
 *
 *  Created on: Feb 18, 2018
 *      Author: bas
 */

#include "../include/sensor_interface.h"

// helper function to generate a common sensor struct
void create_sensor(sensor* current_sensor, char* name, int number_of_sensors, char** sensor_tags, int server_port, int delay_in_seconds){

	//seed randomizer
	srand((unsigned int)time(NULL));

	sensor si;
	current_sensor->name = name;
	current_sensor->number_of_sensors = number_of_sensors;

	//allocating memory for the number of sensor tags
	current_sensor->sensor_tags = malloc(number_of_sensors * sizeof(char*));

	//the actual tags are provided in stack memory, so no allocation
	for (int i = 0; i < number_of_sensors; i++){
		current_sensor->sensor_tags[i] = sensor_tags[i];
	}

	current_sensor->server_port = server_port;
	current_sensor->delay_in_seconds = delay_in_seconds;
	current_sensor->measurements = malloc(number_of_sensors * sizeof(float));

	current_sensor->string_measurements = malloc(number_of_sensors * sizeof(char*));
	//float with two decimals and max measurement of 100 is at most "100.00\0"
	//so at most 7 chars, use 10 to be on the safe side
	for (int i = 0; i < number_of_sensors; i++){
		current_sensor->string_measurements[i] = malloc(MAX_VAL_STRING_LENGTH * sizeof(char));
	}

}

// helper function to destroy sensor struct
int destroy_sensor(sensor* current_sensor){

	//only free malloced attributes
	free(current_sensor->sensor_tags);
	free(current_sensor->measurements);
	for (int i = 0; i < current_sensor->number_of_sensors; i++){
		free(current_sensor->string_measurements[i]);
	}
	free(current_sensor->string_measurements);


	//set other stuff to bogus values to be sure
	current_sensor->name = "";
	current_sensor->number_of_sensors = 0;
	current_sensor->server_port = 0;
	current_sensor->delay_in_seconds = 0;

	return EXIT_SUCCESS;
}

// get new sensor measurements
// the actual measurement is mocked by a randomizer
float* measure(sensor* current_sensor){

	float random_measurement;
	for(int i = 0; i < current_sensor->number_of_sensors; i++){
		current_sensor->measurements[i] = ((float)rand()/(float)(RAND_MAX)) * MAX_MEASUREMENT;
	}
	return current_sensor->measurements;
}

void delay(sensor* current_sensor){
	sleep(current_sensor->delay_in_seconds);
	return;
}

ezxml_t convert_to_update(float* measurements, sensor* current_sensor){
	ezxml_t XML = ezxml_new("update");

	for(int i = 0; i < current_sensor->number_of_sensors; i++){
		sprintf(current_sensor->string_measurements[i], "%.2f", measurements[i]);
		XML = ezxml_set_attr(XML, current_sensor->sensor_tags[i], current_sensor->string_measurements[i]);
	}

	return XML;
}

int send_to_port(ezxml_t XML, sensor* current_sensor){
	return EXIT_SUCCESS;
}


