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
#include <string.h>

#include <ezxml.h>
#include <measurement_server.h>
#include <tcp_interaction.h>

typedef enum {FALSE, TRUE} bool;

int evaluate_result(int, char*);
int main();

int test_measurement_server();
int test_tcp_connection();


int test_process_client_update();
int test_serve_client_request();

int test_number_of_stored_measurements();
int test_store_measurement();
int test_clear_stored_measurements();
int test_retrieve_measurements();

int test_start_connection();
int test_send_TCP_message();
int test_receive_TCP_message();
int test_terminate_connection();

#endif /* TEST_MEASUREMENT_CLIENT_H_ */
