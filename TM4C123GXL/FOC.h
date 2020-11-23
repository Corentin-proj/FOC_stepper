/**
 * FOC.h
 * Created on: June 8, 2020
 * Author: Corentin Casier
 * Last update: June 8, 2020
 * This file contains the prototypes of the functions of FOC.c
 *
 */

#ifndef FOC_H
#define FOC_H

#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include "inc/hw_memmap.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/fpu.h"

void initFOC(void);
float _sin(float angle);
float _cos(float angle);
float _wrapAngle(float angle)
float invParkAlpha(float d, float q, float theta);
float invParkBeta(float d, float q, float theta);
float mech2elec(int poles, float thetaMech);

#endif
