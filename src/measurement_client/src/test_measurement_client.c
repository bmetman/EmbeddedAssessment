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

static sensor test_sensor;

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

	char* sensor_tags[4];
	sensor_tags[0] = "TAG1";
	sensor_tags[1] = "TAG2";
	sensor_tags[2] = "TAG3";
	sensor_tags[3] = "TAG4";

	create_sensor(&test_sensor, "TEST_SENSOR", 4, sensor_tags, 4242, 1);

	result += test_sensor_interface();
	result += test_measurement_client();
	result += test_destroy_sensor();

	return evaluate_result(result, "ALL TESTS\n");
}

int test_destroy_sensor(){
	int result = EXIT_SUCCESS;

	destroy_sensor(&test_sensor);

	if(strcmp(test_sensor.name, "") != 0){result++;}
	if(test_sensor.number_of_sensors != 0){result++;}
	if(test_sensor.server_port != 0){result++;}
	if(test_sensor.delay_in_seconds != 0){result++;}

	return evaluate_result(result, "DESTROY_SENSOR");
}

/***********************************/
/* UNIT TESTS FOR SENSOR INTERFACE */
/***********************************/

int test_sensor_interface(){
	printf("TESTING test_sensor_interface\n");
	int result = EXIT_SUCCESS;
	result += test_create_sensor();
	result += test_measure();
	result += test_delay();
	result += test_convert_to_update();
	result += test_send_to_port();

	return evaluate_result(result, "test_sensor_interface\n");
}

int test_create_sensor(){
	int result = EXIT_SUCCESS;

	if(test_sensor.name != "TEST_SENSOR"){result++;}
	if(test_sensor.sensor_tags[0] != "TAG1"){result++;};
	if(test_sensor.sensor_tags[1] != "TAG2"){result++;};
	if(test_sensor.sensor_tags[2] != "TAG3"){result++;};
	if(test_sensor.sensor_tags[3] != "TAG4"){result++;};
	if(test_sensor.number_of_sensors != 4){result++;}
	if(test_sensor.server_port != 4242){result++;}
	if(test_sensor.delay_in_seconds != 1){result++;}

	return evaluate_result(result, "CREATE_SENSOR");
}

int test_measure(){
	int result = EXIT_SUCCESS;
	float* measurements = measure(&test_sensor);

	if(!measurements[0] || measurements[0] > MAX_MEASUREMENT){result++;}
	if(!measurements[1] || measurements[0] > MAX_MEASUREMENT){result++;}
	if(!measurements[2] || measurements[0] > MAX_MEASUREMENT){result++;}
	if(!measurements[3] || measurements[0] > MAX_MEASUREMENT){result++;}

	return evaluate_result(result, "MEASUREMENTS");
}

int test_delay(){
	int result = EXIT_SUCCESS;
	time_t start_time, end_time;

	start_time = time(NULL);;
	delay(&test_sensor);
	end_time = time(NULL);

	if( (double)(end_time - start_time) < test_sensor.delay_in_seconds ){result++;};

	return evaluate_result(result, "DELAY");
}

int test_convert_to_update(){
	int result = EXIT_SUCCESS;

	float* measurements = measure(&test_sensor);
	ezxml_t XML = convert_to_update(measurements, &test_sensor);

	if(strcmp(XML->name,"update") != 0){result++;};

	for(int i = 0; i < test_sensor.number_of_sensors; i++){
		if(ezxml_attr(XML, test_sensor.sensor_tags[i]) == NULL){result++;};
	}

	ezxml_free(XML);

	return evaluate_result(result, "CONVERT_TO_UPDATE");
}

int test_send_to_port(){
	int result = EXIT_SUCCESS;
	float* measurements = measure(&test_sensor);
	ezxml_t XML = convert_to_update(measurements, &test_sensor);

	result += send_to_port(XML, &test_sensor);

	ezxml_free(XML);

	return evaluate_result(result, "SEND_TO_PORT");
}



/*************************************/
/* UNIT TESTS FOR MEASUREMENT CLIENT */
/*************************************/


int test_measurement_client(){
	printf("TESTING measurement_client\n");
	//TODO: implement tests
	int result = EXIT_SUCCESS;
	return evaluate_result(result, "measurement_client\n");
}
