/**
 * encoder.h
 * Created on: May 3, 2020
 * Author: Corentin Casier
 * Last update: May 3, 2020
 * This file contains the prototypes of the functions of encoder.c
 *
 */
#include "driverlib/sysctl.h"
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_qei.h"
#include "driverlib/qei.h"

void initEncoder(void);
