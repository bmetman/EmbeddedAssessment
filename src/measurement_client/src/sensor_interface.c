/*
 * temperature_sensor.c
 *
 *  Created on: Feb 18, 2018
 *      Author: bas
 */

#include "../include/sensor_interface.h"

// helper function to generate a common sensor struct
void create_sensor(sensor* current_sensor, char* name, int number_of_sensors, char** sensor_tags, int server_port){

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

	return EXIT_SUCCESS;
}

// get new sensor measurements
// the actual measurement is mocked by a randomizer
int measure(sensor* current_sensor){

	float random_measurement;
	for(int i = 0; i < current_sensor->number_of_sensors; i++){
		current_sensor->measurements[i] = ((float)rand()/(float)(RAND_MAX)) * MAX_MEASUREMENT;
	}

	return EXIT_SUCCESS;
}

void convert_to_update(sensor* current_sensor, ezxml_t* update){
	*update = ezxml_new("update");
	ezxml_t child_XML;

	for(int i = 0; i < current_sensor->number_of_sensors; i++){
		sprintf(current_sensor->string_measurements[i], "%.2f", current_sensor->measurements[i]);

		child_XML = ezxml_add_child(*update, current_sensor->sensor_tags[i], 0);
		ezxml_set_txt(child_XML,current_sensor->string_measurements[i]);
	}
}

void pretty_print_update(ezxml_t XML, sensor* current_sensor){

	ezxml_t child_XML;

	if(!strcmp(XML->name, "update")){

		printf("UPDATE containing:\n");

		for(int i = 0; i < current_sensor->number_of_sensors; i++){
			child_XML = ezxml_child(XML, current_sensor->sensor_tags[i]);
			if(child_XML != NULL){
				if(child_XML->name && child_XML->txt){
					printf("%s measurement with value: %s\n", child_XML->name, child_XML->txt);
				}
			}
		}
		printf("\n");
	} else {
		printf("INCORRECT UPDATEFORMAT\n\n");
	}
}

int send_to_port(ezxml_t XML, sensor* current_sensor){

	//TODO: implement send over TCP, for now mocking it
	printf("SENDING UPDATE TO PORT %i\n", current_sensor->server_port);
	pretty_print_update(XML, current_sensor);
	return EXIT_SUCCESS;
}


