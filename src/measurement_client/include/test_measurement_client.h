/*
 ============================================================================
 Name        : measurement_client.c
 Author      : S. P. Metman
 Version     :
 Copyright   : 
 Description : Measurement Client
 ============================================================================
 */

#ifndef TEST_MEASUREMENT_CLIENT_H_
#define TEST_MEASUREMENT_CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "measurement_client.h"
#include "sensor_interface.h"

typedef enum { FALSE, TRUE } bool;



int evaluate_result(int, char*);
int main();

int test_sensor_interface();
int test_create_sensor();
int test_measure();
int test_delay();
int test_convert_to_update();

int test_measurement_client();

#endif /* TEST_MEASUREMENT_CLIENT_H_ */
