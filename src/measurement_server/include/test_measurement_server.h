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
#include <ezxml.h>

#include "measurement_server.h"

typedef enum { FALSE, TRUE } bool;

int evaluate_result(int, char*);
int main();

int test_measurement_server();
int test_process_client_update();
int test_serve_client_request();
int test_store_measurement();
int test_retrieve_measurement();

#endif /* TEST_MEASUREMENT_CLIENT_H_ */
