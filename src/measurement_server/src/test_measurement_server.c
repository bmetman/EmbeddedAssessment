/*
 ============================================================================
 Name        : main.c
 Author      : S. P. Metman
 Version     :
 Copyright   : 
 Description : Main file for testing Measurement Client
 ============================================================================
 */

#include "../include/test_measurement_server.h"

int evaluate_result(int result, char* current_module){
	if(result){
		printf("FAILED: %i errors found, %s\n", result, current_module);
		return EXIT_FAILURE;
	} else {
		printf("PASSED: %s\n", current_module);
		return EXIT_SUCCESS;
	}

}

int main(void) {

	int result = EXIT_SUCCESS;
	result += test_measurement_server();
	return evaluate_result(result, "ALL TESTS\n");
}


/*************************************/
/* UNIT TESTS FOR MEASUREMENT SERVER */
/*************************************/

//char* process_client_update(ezxml_t);
//char* serve_client_request(ezxml_t);
//measurement* store_measurement(float*, char*);
//measurement* retrieve_measurement(char*);

int test_measurement_server(){
	printf("TESTING measurement_server\n");
	int result = EXIT_SUCCESS;

	result += test_process_client_update();
	result += test_serve_client_request();
	result += test_store_measurement();
	result += test_retrieve_measurement();

	return evaluate_result(result, "measurement_server\n");
}

int test_process_client_update(){
	int result = EXIT_SUCCESS;

	ezxml_t update = ezxml_new("update");
	ezxml_t child_XML;

	child_XML = ezxml_add_child(update, "temperature", 0);
	ezxml_set_txt(child_XML,"25.0");

	child_XML = ezxml_add_child(update, "pressure", 0);
	ezxml_set_txt(child_XML,"42.42");

	ezxml_free(update);

	return evaluate_result(result, "test_process_client_update");
}

int test_serve_client_request(){
	int result = EXIT_SUCCESS;

	return evaluate_result(result, "test_serve_client_request");
}

int test_store_measurement(){
	int result = EXIT_SUCCESS;

	return evaluate_result(result, "test_store_measurement");
}

int test_retrieve_measurement(){
	int result = EXIT_SUCCESS;

	return evaluate_result(result, "test_retrieve_measurement");
}


