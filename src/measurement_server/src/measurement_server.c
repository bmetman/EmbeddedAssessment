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

//starts the measurement servers
int start_measurement_server(){

	printf("STARTING MEASUREMENT_SERVER");

	TCP_connection conn;
	start_connection(6423, &conn);

	if(conn.connected == 1){

		char* sensor_update = receive_TCP_message(&conn);
		printf("INCOMING SENSOR UPDATE:\n%s", sensor_update);
		free(sensor_update);

	}

	terminate_connection(&conn);

	printf("EXITING MEASUREMENT_SERVER");

	return EXIT_SUCCESS;
}

//processes the xml updates coming from sensor clients
//returned result needs to be freed
char* process_client_update(ezxml_t update){

	char* result = (char*)calloc(MAX_STRING_SIZE, sizeof(char));
	strcat(result, "");
	//if it's an update
	if( update != NULL && strcmp(update->name, "update") == 0){

		ezxml_t child_XML = update->child;

		if(child_XML == NULL){
			return result;
		}
		strcat(result, "UPDATE containing:\n");
		char buffer[MAX_STRING_SIZE];

		while(child_XML != NULL){
			sprintf(buffer, "%s measurement with value: %s\n", child_XML->name, child_XML->txt);
			strcat(result, buffer);
			child_XML = child_XML->sibling;
		}

		strcat(result, "\n");
	}
	return result;
}

//processes the xml requests coming from request subsystems
//returned result needs to be freed
ezxml_t serve_client_request(ezxml_t request){

	ezxml_t status = ezxml_new("status");

	//retrieve measurements and amount of measurements from memory
	measurement* measurements = retrieve_measurements();
	int measurements_size = number_of_stored_measurements();

	if( request != NULL && strcmp(request->name, "retrieve") == 0){

		//get the xml with the key tag
		ezxml_t child_XML = ezxml_child(request, "key");

		//if no specific keys are requested, retrieve all measurements
		if(child_XML == NULL){

			//find the measurements with the requested tag
			//in the stored measurements
			for(int i = 0; i < measurements_size; i++){

				child_XML = ezxml_add_child(status, measurements[i].descriptor, 0);
				child_XML->txt = measurements[i].string_value;
			}

			free(measurements);
			return status;
		} else {

			//if there exists a key tag
			while(child_XML != NULL){

				//find the measurements with the requested tag
				//in the stored measurements
				for(int i = 0; i < measurements_size; i++){
					if(strcmp(measurements[i].descriptor, child_XML->txt) == 0){

						//now the value for the descriptor has been found
						//so add it to the XML status update
						ezxml_t add_XML = ezxml_add_child(status, measurements[i].descriptor, 0);
						add_XML->txt = measurements[i].string_value;

						//set the next child_XML to be the next one with "key" tag
						i = measurements_size;
					}
				}
				child_XML = child_XML->next;
			}
		}
	}
	free(measurements);
	return status;
}

//prettifies returned status updates
//returned result needs to be freed
char* prettify_status(ezxml_t status){

	char* result = (char*)calloc(MAX_STRING_SIZE, sizeof(char));
	strcat(result, "");
	//if it's a status
	if( status != NULL && strcmp(status->name, "status") == 0){

		ezxml_t child_XML = status->child;

		if(child_XML == NULL){
			return result;
		}
		strcat(result, "STATUS containing:\n");
		char buffer[MAX_STRING_SIZE];

		while(child_XML != NULL){
			sprintf(buffer, "%s measurement with value: %s\n", child_XML->name, child_XML->txt);
			strcat(result, buffer);
			child_XML = child_XML->sibling;
		}

		strcat(result, "\n");
	}
	return result;
}

/***********************************************************/
/* FUNCTIONS FOR OFFLINE/REDUNDANT STORAGE, MOCKED FOR NOW */
/***********************************************************/

//MOCKED
int number_of_stored_measurements(){
	return 2;
}

//MOCKED
int store_measurement(float value, char* tag){
	return EXIT_SUCCESS;
}

//MOCKED
int clear_stored_measurements(){
	return EXIT_SUCCESS;
}

//MOCKED
measurement* retrieve_measurements(){

//	int measurements_size = number_of_stored_measurements();
//	measurement* return_measurements = malloc(measurements_size * sizeof(measurement));

	measurement* measurements = calloc(2,sizeof(measurement));

	measurements[0].descriptor = "temperature";
	measurements[0].value = 25.0;
	measurements[0].string_value = "25.0";

	measurements[1].descriptor = "pressure";
	measurements[1].value = 42.0;
	measurements[1].string_value = "42.0";

	return measurements;
}

