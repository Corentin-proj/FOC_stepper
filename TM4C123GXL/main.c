/**
 * main.c
 * Created on: May 3, 2020
 * Author: Corentin Casier
 * Last update: May 9, 2020
 * This software is a Field Oriented Control (FOC) algorithm for 2 phases stepper motor.
 *
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<string.h>
#include<math.h>

#include "encoder.h"
#include "serial.h"


//convert int to char
char* itoa(int val, int base){

	static char buf[32] = {0};

	int i = 30;

	for(; val && i ; --i, val /= base)

		buf[i] = "0123456789abcdef"[val % base];

	return &buf[i+1];

}

int main(void){
  //First initialize quadrature encoder using a
  // 400 line encoder at four edges per line, there are 1600 pulses per
  // revolution; therefore set the maximum position to 1599 as the count
  // is zero based.
  initEncoder(1599);

  //init serial at 115200bps
  initSerial(115200);

  //send test communication
  sendSerial((uint8_t *)"Test", 5);

  int someInt = 368;
  sendSerial((uint8_t *)itoa(someInt,10), 12);// here 10 means decimal
  while(1){
    //sendSerial((uint8_t *)"Test\n", 5);
  }
  return 0;
}
