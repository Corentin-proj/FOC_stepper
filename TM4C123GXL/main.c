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
#include "driverlib/timer.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"

#include "encoder.h"
#include "serial.h"
#include "stepper.h"

// WTimer5
void Init_Uptime(void){
    // Configure WTimer5 to control system up time
    SysCtlPeripheralDisable(SYSCTL_PERIPH_WTIMER5);
    SysCtlPeripheralReset(SYSCTL_PERIPH_WTIMER5);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER5);
    while( !SysCtlPeripheralReady( SYSCTL_PERIPH_WTIMER5 ) ){}
    TimerConfigure(WTIMER5_BASE,TIMER_CFG_PERIODIC_UP);
    TimerEnable(WTIMER5_BASE, TIMER_A);
}

//wait in millisec
void wait(int millis){
	uint32_t g_ui32SysClock = MAP_SysCtlClockGet();
	int32_t timeMillis = (int32_t)(TimerValueGet64(WTIMER5_BASE)/(g_ui32SysClock/1000));
	int32_t lastTime=timeMillis;
	while(timeMillis-lastTime < millis){
		timeMillis = (int32_t)(TimerValueGet64(WTIMER5_BASE)/(g_ui32SysClock/1000));
	}
}

int main(void){
	uint32_t position=0;
	//set the system clock to 80Mhz
	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

	//Initialize Timer to get elapsed time
	Init_Uptime();

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
    //position = QEIPositionGet(QEI0_BASE);

		setVoltage_PhaseA(1000);
		setVoltage_PhaseB(1000);
		wait(10);
		setVoltage_PhaseA(0);
		setVoltage_PhaseB(1000);
		wait(10);
		setVoltage_PhaseA(-1000);
		setVoltage_PhaseB(1000);
		wait(10);
		setVoltage_PhaseA(-1000);
		setVoltage_PhaseB(0);
		wait(10);
		setVoltage_PhaseA(-1000);
		setVoltage_PhaseB(-1000);
		wait(10);
		setVoltage_PhaseA(0);
		setVoltage_PhaseB(-1000);
		wait(10);
		setVoltage_PhaseA(1000);
		setVoltage_PhaseB(-1000);
		wait(10);
		setVoltage_PhaseA(1000);
		setVoltage_PhaseB(0);
		wait(10);
  }
  return 0;
}
