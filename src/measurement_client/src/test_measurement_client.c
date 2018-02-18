/*
 ============================================================================
 Name        : main.c
 Author      : S. P. Metman
 Version     :
 Copyright   : 
 Description : Main file for testing Measurement Client
 ============================================================================
 */

#include "../include/test_measurement_client.h"

int main(void) {
	printf("test");
	return test_measurement_client();
}

int test_measurement_client(){
	int result = start_measurement_client();

	if(result == EXIT_SUCCESS){
		return EXIT_SUCCESS;
	} else {
		return EXIT_FAILURE;
	}
}