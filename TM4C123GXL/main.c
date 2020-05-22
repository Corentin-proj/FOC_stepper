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
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#include "encoder.h"
#include "serial.h"
#include "stepper.h"

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

	initStepper();
	SysCtlDelay(3);
  //init serial at 115200bps
  initSerial(115200);
	//delay for 112,5ns
	SysCtlDelay(3);
	UARTprintf("Ready\n");
	SysCtlDelay(6000);//delay for 250ms
	UARTprintf("Starting loop\n");
	SysCtlDelay(6000);//delay for 250ms
  while(1){
    position = QEIPositionGet(QEI0_BASE);
		setVoltage_PhaseA(position-750);
		setVoltage_PhaseB(position-750);
		UARTprintf("%d\n",position-750);
		SysCtlDelay(6000);//delay for 250ms
  }
  return 0;
}
