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

int start_measurement_client(void);
void pretty_print_update(ezxml_t);

#endif /* MEASUREMENT_CLIENT_H_ */
