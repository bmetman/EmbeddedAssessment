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

char* serve_client_request(ezxml_t* request){
	return "TODO";
}

measurement* store_measurement(float* values, char* descriptors){
	return NULL;
}

measurement* retrieve_measurement(char* desciptor){
	return NULL;
}



