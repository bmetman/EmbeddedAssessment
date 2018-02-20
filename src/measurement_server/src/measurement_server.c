/*
 ============================================================================
 Name        : measurement_client.c
 Author      : S. P. Metman
 Version     :
 Copyright   : 
 Description : Measurement Client
 ============================================================================
 */

#include "../include/measurement_server.h"

int start_measurement_server(){

	printf("STARTING MEASUREMENT_SERVER");

	//TODO: code here

	printf("EXITING MEASUREMENT_SERVER");

	return EXIT_SUCCESS;
}

char* process_client_update(ezxml_t* update){
	return "TODO";
}

int serve_client_request(ezxml_t* request, ezxml_t* status){
	*status = ezxml_new("TODO");
	return EXIT_SUCCESS;
}

int number_of_stored_measurements(){
	return 0;
}

int store_measurement(float value, char* tag){
	return EXIT_SUCCESS;
}

int clear_stored_measurements(){
	return EXIT_SUCCESS;
}

int retrieve_measurements(measurement* return_measurements){
	return EXIT_SUCCESS;
}

