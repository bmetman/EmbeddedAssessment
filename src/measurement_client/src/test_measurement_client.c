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
		printf("Found %i errors when testing %s\n", result, current_module);
		return EXIT_FAILURE;
	} else {
		printf("%s passed testing\n", current_module);
		return EXIT_SUCCESS;
	}
}

int main(void) {
	printf("TESTING measurement_client\n");
	int result = EXIT_SUCCESS;

	char* sensor_tags[4];
	sensor_tags[0] = "TAG1";
	sensor_tags[1] = "TAG2";
	sensor_tags[2] = "TAG3";
	sensor_tags[3] = "TAG4";
	test_sensor = create_sensor("TEST_SENSOR", 4, sensor_tags, 4242, 1);

	result += test_sensor_interface();
	result += test_measurement_client();

	return evaluate_result(result, "MEASUREMENT_CLIENT");
}



/***********************************/
/* UNIT TESTS FOR SENSOR INTERFACE */
/***********************************/

int test_sensor_interface(){
	int result = EXIT_SUCCESS;
	result += test_create_sensor();
	result += test_measure();
	result += test_delay();
	result += test_convert_to_update();

	return evaluate_result(result, "SENSOR_INTERFACE");
}

int test_create_sensor(){
	int result = EXIT_SUCCESS;

	if(test_sensor.name != "TEST_SENSOR"){result++;}
	if(test_sensor.sensor_tags[0] != "TAG1"){result++;};
	if(test_sensor.sensor_tags[1] != "TAG2"){result++;};
	if(test_sensor.sensor_tags[2] != "TAG3"){result++;};
	if(test_sensor.sensor_tags[3] != "TAG4"){result++;};
	if(test_sensor.number_of_sensors != 4){result++;}
	if(test_sensor.number_of_sensors != 4242){result++;}
	if(test_sensor.delay_in_seconds != 900){result++;}

	return evaluate_result(result, "CREATE_SENSOR");
}

int test_measure(){
	int result = EXIT_SUCCESS;
	float* measurements = measure(test_sensor);

	if(!measurements[0]){result++;}
	if(!measurements[1]){result++;}
	if(!measurements[2]){result++;}
	if(!measurements[3]){result++;}

	return evaluate_result(result, "MEASUREMENTS");
}

int test_delay(){
	int result = EXIT_SUCCESS;
	clock_t start_time, end_time;

	start_time = clock();
	delay(test_sensor);
	end_time = clock();

	if( ((double)(end_time-start_time)/CLOCKS_PER_SEC) < test_sensor.delay_in_seconds ){result++;};

	return evaluate_result(result, "DELAY");
}

int test_convert_to_update(){
	int result = EXIT_SUCCESS;

	float* measurements = measure(test_sensor);
	char* XML = convert_to_update(measurements, test_sensor);

	if(XML != "<update>\n\t<personsPassed>12</personsPassed>\n\t<lightCondition>bright</lightCondition>\n\t<humidity>52</humidity>\n</update>"){result++;};

	return evaluate_result(result, "CONVERT_TO_UPDATE");
}


/*************************************/
/* UNIT TESTS FOR MEASUREMENT CLIENT */
/*************************************/


int test_measurement_client(){
	//TODO: implement tests
	return EXIT_SUCCESS;
}
