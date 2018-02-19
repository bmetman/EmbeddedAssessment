/*
 * measurement_client.h
 *
 *  Created on: Feb 17, 2018
 *      Author: bas
 */

#ifndef MEASUREMENT_CLIENT_H_
#define MEASUREMENT_CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include "sensor_interface.h"

#define NUMBER_OF_UPDATES 5
#define UPDATE_DELAY_IN_SECONDS 2
#define MAX_SEND_RETRY_COUNT 5

int start_measurement_client(void);
void delay(int);

#endif /* MEASUREMENT_CLIENT_H_ */
