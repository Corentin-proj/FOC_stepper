/**
 * encoder.h
 * Created on: May 3, 2020
 * Author: Corentin Casier
 * Last update: May 3, 2020
 * This file contains the prototypes of the functions of encoder.c
 *
 */

#ifndef ENCODER_H
#define ENCODER_H

#include <stdbool.h>
#include <stdint.h>

#include "driverlib/sysctl.h"
//#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_qei.h"
#include "driverlib/qei.h"

//Init encoder with the number of counts per revolution
void initEncoder(int counts);

#endif
