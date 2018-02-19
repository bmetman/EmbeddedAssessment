/*
 ============================================================================
 Name        : measurement_client.c
 Author      : S. P. Metman
 Version     :
 Copyright   : 
 Description : Measurement Client
 ============================================================================
 */

#include "../include/measurement_client.h"

static sensor temperature_sensor;
static sensor gyroscope_sensor;

int start_measurement_client(){

	//create temperature sensor
	char* temperature_sensor_tags[1];
	temperature_sensor_tags[0] = "temperature";
	create_sensor(&temperature_sensor, "TEMPERATURE_SENSOR", 1, temperature_sensor_tags, 6423, 900);

	//create gyroscope sensor
	char* gyroscope_sensor_tags[3];
	gyroscope_sensor_tags[0] = "x-axis";
	gyroscope_sensor_tags[1] = "y-axis";
	gyroscope_sensor_tags[2] = "z-axis";
	create_sensor(&gyroscope_sensor, "GYROSCOPE_SENSOR", 3, gyroscope_sensor_tags, 6423, 900);

	//measure new values
	measure(&temperature_sensor);
	ezxml_t temperature_update = convert_to_update(&temperature_sensor);

	measure(&gyroscope_sensor);
	ezxml_t gyroscope_update = convert_to_update(&gyroscope_sensor);


	ezxml_free(temperature_update);
	ezxml_free(gyroscope_update);
	return EXIT_SUCCESS;
}

void pretty_print_update(ezxml_t XML){

}


