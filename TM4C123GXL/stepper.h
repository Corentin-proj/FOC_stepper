/**
 * stepper.h
 * Created on: May 22, 2020
 * Author: Corentin Casier
 * Last update: May 22, 2020
 * This file contains the prototypes of the functions of stepper.c
 *
 */

#ifndef STEPPER_H
#define STEPPER_H

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"

void initStepper(void);

#endif
