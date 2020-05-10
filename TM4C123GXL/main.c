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

#include "driverlib/sysctl.h"

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
	uint32_t position=0;
	//set the system clock to 80Mhz
	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
  //Initialize quadrature encoder using a
  // 400 line encoder at four edges per line, there are 1600 pulses per
  // revolution; therefore set the maximum position to 1599 as the count
  // is zero based.
  initEncoder(1599);
	// delay 3 x 3 clock cycles (clock at 80Mhz so clock cycle is 12,5ns)
	// so it means delay for 112,5ns
	SysCtlDelay(3);
  //init serial at 115200bps
  initSerial(115200);
	//delay for 112,5ns
	SysCtlDelay(3);
  //send test communication
  sendSerial((uint8_t *)"Test\n", 6);
	SysCtlDelay(6000);//delay for 250ms
  while(1){
    position = QEIPositionGet(QEI0_BASE);
		sendSerial((uint8_t *)itoa(position,10), 12);// here 10 means decimal
		SysCtlDelay(6000);//delay for 250ms
		sendSerial((uint8_t *)"\n",1);
		SysCtlDelay(6000);//delay for 250ms
  }
  return 0;
}
