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

	printf("STARTING MEASUREMENT_CLIENT");

	//create temperature sensor
	char* temperature_sensor_tags[1];
	temperature_sensor_tags[0] = "temperature";
	create_sensor(&temperature_sensor, "TEMPERATURE_SENSOR", 1, temperature_sensor_tags, 6423);

	//create gyroscope sensor
	char* gyroscope_sensor_tags[3];
	gyroscope_sensor_tags[0] = "x-axis";
	gyroscope_sensor_tags[1] = "y-axis";
	gyroscope_sensor_tags[2] = "z-axis";
	create_sensor(&gyroscope_sensor, "GYROSCOPE_SENSOR", 3, gyroscope_sensor_tags, 6423);

	ezxml_t temperature_update;
	ezxml_t gyroscope_update;
	int send_status = EXIT_FAILURE;
	int retry_count = 0;
	for(int i = 0; i < NUMBER_OF_UPDATES; i++){

		printf("STARTING NEW MEASUREMENT\n");

		//send temperature update
		measure(&temperature_sensor);
		convert_to_update(&temperature_sensor, &temperature_update);
		while(send_status != EXIT_SUCCESS && retry_count < MAX_SEND_RETRY_COUNT){
			send_status = send_to_port(temperature_update, &temperature_sensor);
			retry_count++;
		}
		ezxml_free(temperature_update);
		send_status = EXIT_FAILURE;
		retry_count = 0;

		//send gyroscope update
		measure(&gyroscope_sensor);
		convert_to_update(&gyroscope_sensor, &gyroscope_update);
		while(send_status != EXIT_SUCCESS && retry_count < MAX_SEND_RETRY_COUNT){
			send_status = send_to_port(gyroscope_update, &gyroscope_sensor);
			retry_count++;
		}
		ezxml_free(gyroscope_update);
		send_status = EXIT_FAILURE;
		retry_count = 0;

		printf("NEW MEASUREMENT SENT\n");
		delay(UPDATE_DELAY_IN_SECONDS);
	}


	printf("EXITING MEASUREMENT_CLIENT");
	destroy_sensor(&temperature_sensor);
	destroy_sensor(&gyroscope_sensor);

	return EXIT_SUCCESS;
}

void delay(int seconds){
	sleep(seconds);
	return;
}




