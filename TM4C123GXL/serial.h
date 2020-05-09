/**
 * serial.h
 * Created on: May 9, 2020
 * Author: Corentin Casier
 * Last update: May 9, 2020
 * This file contains the prototypes of the functions of serial.c
 *
 */

#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

void initSerial(int baudrate);
void sendSerial(const uint8_t *pui8Buffer, uint32_t ui32Count);

#endif
