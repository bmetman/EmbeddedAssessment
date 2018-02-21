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
	} else {
		printf("PASSED: %s\n", current_module);
	}

	return result;
}

int main(void) {

	int result = EXIT_SUCCESS;
	result += test_measurement_server();
	result += test_tcp_connection();
	return evaluate_result(result, "ALL TESTS\n");
}


/*************************************/
/* UNIT TESTS FOR MEASUREMENT SERVER */
/*************************************/

int test_measurement_server(){
	printf("TESTING measurement_server\n");
	int result = EXIT_SUCCESS;

	result += test_process_client_update();
	result += test_serve_client_request();
	result += test_prettify_status();
//
//	result += test_number_of_stored_measurements();
//	result += test_store_measurement();
//	result += test_clear_stored_measurements();
//	result += test_retrieve_measurements();

	return evaluate_result(result, "measurement_server\n");
}



int test_process_client_update(){
	int result = EXIT_SUCCESS;

	//testing simple usecase
	ezxml_t update = ezxml_new("update");
	ezxml_t child_XML;
	char* prettified_update;

	child_XML = ezxml_add_child(update, "temperature", 0);
	ezxml_set_txt(child_XML,"25.0");

	child_XML = ezxml_add_child(update, "pressure", 0);
	ezxml_set_txt(child_XML,"42.42");

	prettified_update = process_client_update(update);
	char* expected_update = "UPDATE containing:\ntemperature measurement with value: 25.0\npressure measurement with value: 42.42\n\n";

	if(strcmp(prettified_update, expected_update)){result++;};

	ezxml_free(update);
	free(prettified_update);

	//testing update with wrong parent tag
	update = ezxml_new("updat");
	prettified_update = process_client_update(update);
	expected_update = "";

	if(strcmp(prettified_update, expected_update)){result++;};

	ezxml_free(update);
	free(prettified_update);

	//testing empty update
	update = ezxml_new("update");
	prettified_update = process_client_update(update);
	expected_update = "";

	if(strcmp(prettified_update, expected_update)){result++;};

	ezxml_free(update);
	free(prettified_update);

	return evaluate_result(result, "test_process_client_update");
}

int test_serve_client_request(){
	int result = EXIT_SUCCESS;

	//multiple sensor retrieval
	ezxml_t request = ezxml_new("retrieve");
	ezxml_t child_XML;

	child_XML = ezxml_add_child(request, "key", 0);
	ezxml_set_txt(child_XML,"temperature");

	child_XML = ezxml_add_child(request, "key", 0);
	ezxml_set_txt(child_XML,"pressure");

	ezxml_t status = serve_client_request(request);

	if(strcmp(status->name,"status") != 0){result++;};
	if(status->name != NULL) {
		if(strcmp(ezxml_child(status, "temperature")->name, "temperature")){result++;};
		if(strcmp(ezxml_child(status, "temperature")->txt, "25.0")){result++;};

		if(strcmp(ezxml_child(status, "pressure")->name, "pressure")){result++;};
		if(strcmp(ezxml_child(status, "pressure")->txt, "42.0")){result++;};
	} else {
		result++;
	}

	ezxml_free(request);
	ezxml_free(status);

	//all sensor retrieval with no values stored
	request = ezxml_new("retrieve");
	status = serve_client_request(request);

	if(strcmp(status->name,"status") != 0){result++;};
	if(status->name != NULL) {
		if(strcmp(ezxml_child(status, "temperature")->name, "temperature")){result++;};
		if(strcmp(ezxml_child(status, "temperature")->txt, "25.0")){result++;};

		if(strcmp(ezxml_child(status, "pressure")->name, "pressure")){result++;};
		if(strcmp(ezxml_child(status, "pressure")->txt, "42.0")){result++;};
	} else {
		result++;
	}

	ezxml_free(request);
	ezxml_free(status);

	//wrong tag
	request = ezxml_new("update");

	status = serve_client_request(request);
	if(strcmp(status->name,"status") != 0){result++;};
	if(status->child != NULL){result++;};

	ezxml_free(request);
	ezxml_free(status);
	clear_stored_measurements();

	return evaluate_result(result, "test_serve_client_request");
}

int test_prettify_status(){
	int result = EXIT_SUCCESS;

	//testing simple usecase
	ezxml_t status = ezxml_new("status");
	ezxml_t child_XML;
	char* prettified_status;

	child_XML = ezxml_add_child(status, "personsPassed", 0);
	ezxml_set_txt(child_XML,"12");

	child_XML = ezxml_add_child(status, "humidity", 0);
	ezxml_set_txt(child_XML,"42");

	prettified_status= prettify_status(status);
	char* expected_status = "STATUS containing:\npersonsPassed measurement with value: 12\nhumidity measurement with value: 42\n\n";

	if(strcmp(prettified_status, expected_status) != 0){result++;};

	ezxml_free(status);
	free(prettified_status);

	//testing update with wrong parent tag
	status = ezxml_new("whatever");
	prettified_status = prettify_status(status);
	expected_status = "";

	if(strcmp(prettified_status, expected_status)){result++;};

	ezxml_free(status);
	free(prettified_status);

	//testing empty update
	status = ezxml_new("status");
	prettified_status = prettify_status(status);
	expected_status = "";

	if(strcmp(prettified_status, expected_status)){result++;};

	ezxml_free(status);
	free(prettified_status);

	return evaluate_result(result, "test_prettify_status");
}


//MOCKED
int test_number_of_stored_measurements(){
	int result = EXIT_SUCCESS;

//	store_measurement(42.42, "temperature");
//	int number = number_of_stored_measurements();
//	if(number != 1){result++;};
//	clear_stored_measurements();
//	number = number_of_stored_measurements();
//	if(number != 0){result++;};

	int number = number_of_stored_measurements();
	if(number != 2){result++;};
	return evaluate_result(result, "test_number_of_stored_measurements");
}

//MOCKED
int test_store_measurement(){
	int result = EXIT_SUCCESS;

	store_measurement(25.0, "temperature");
	store_measurement(42.42, "pressure");

	measurement* current_measurements;
	current_measurements = retrieve_measurements();

	if(current_measurements != NULL){
		if( strcmp(current_measurements[0].descriptor,"temperature") != 0){result++;};
		if( current_measurements[0].value != 25.0){result++;};

		if( strcmp(current_measurements[1].descriptor,"pressure") != 0){result++;};
		if( current_measurements[1].value != 42.42){result++;};
	}

	result += clear_stored_measurements();
	free(current_measurements);

	return evaluate_result(result, "test_store_measurement");
}

int test_clear_stored_measurements(){
	int result = EXIT_SUCCESS;

//	int number = number_of_stored_measurements();
//	if(number != 1){result++;};
//	clear_stored_measurements();
//	number = number_of_stored_measurements();
//	if(number != 0){result++;};

	result += clear_stored_measurements();
	return evaluate_result(result, "test_clear_stored_measurements");
}


//MOCKED
int test_retrieve_measurements(){
	int result = EXIT_SUCCESS;

	store_measurement(25.0, "temperature");
	store_measurement(42.42, "pressure");

	measurement* measurements;
	measurements = retrieve_measurements();

	if( strcmp(measurements[0].descriptor,"temperature") != 0){result++;};
	if( measurements[0].value != 25.0){result++;};

	if( strcmp(measurements[1].descriptor,"pressure") != 0){result++;};
	if( measurements[1].value != 42.00){result++;};


	result += clear_stored_measurements();
	free(measurements);

	return evaluate_result(result, "test_retrieve_measurements");
}

/*********************************/
/* UNIT TESTS FOR TCP CONNECTION */
/*********************************/

static TCP_connection test_conn;

int test_tcp_connection(){
	printf("TESTING tcp_connection\n");
	int result = EXIT_SUCCESS;

	result += test_start_connection();
	result += test_send_TCP_message();
	result += test_receive_TCP_message();
	result += test_terminate_connection();

	return evaluate_result(result, "tcp_connection\n");
}

int test_start_connection(){
	int result = EXIT_SUCCESS;

	start_connection(42, &test_conn);

	if(test_conn.port != 42){result++;};
	if(test_conn.connected != 1){result++;};

	return evaluate_result(result, "test_start_connection");
}

int test_send_TCP_message(){
	int result = EXIT_SUCCESS;

	result += send_TCP_message("TEST MESSAGE", &test_conn);

	return evaluate_result(result, "test_send_TCP_message");
}

int test_receive_TCP_message(){
	int result = EXIT_SUCCESS;

	char* prettified_update = receive_TCP_message(&test_conn);
	char* expected_update = "UPDATE containing:\ntemperature measurement with value: 25.0\npressure measurement with value: 42.42\n\n";

	if(strcmp(prettified_update, expected_update)){result++;};
	free(prettified_update);

	return evaluate_result(result, "test_receive_TCP_message");
}

int test_terminate_connection(){
	int result = EXIT_SUCCESS;

	terminate_connection(&test_conn);

	if(test_conn.connected != 0){result++;};

	return evaluate_result(result, "test_terminate_connection");
}


