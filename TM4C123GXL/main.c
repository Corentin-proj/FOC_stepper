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
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/fpu.h"

#include "encoder.h"
#include "serial.h"
#include "stepper.h"
#include "FOC.h"

#define M_PI 3.14159265358979323846

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
  float d=1000.0, q=0.0, elecAngle=0.0, alpha=0.0, beta=0.0;
  int poles = 100;//number of rotor poles

  //enable floating point operations
  MAP_FPULazyStackingEnable();
  MAP_FPUEnable();

  //Initialize Field Oriented Control
  //void initFOC();

	//set the system clock to 80Mhz
	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

	//Initialize Timer to get elapsed time
	Init_Uptime();

  //Initialize quadrature encoder using a
  // 400 line encoder at four edges per line, there are 1600 pulses per
  // revolution; therefore set the maximum position to 1599 as the count
  // is zero based.
  uint32_t maxEncoder = 1599;//maximum encoder value
  initEncoder(maxEncoder);
	// delay 3 x 3 clock cycles (clock at 80Mhz so clock cycle is 12,5ns)
	// so it means delay for 112,5ns
	SysCtlDelay(3);

	initStepper();
	SysCtlDelay(3);
  setVoltage_PhaseA(1000);
  setVoltage_PhaseB(1000);
  SysCtlDelay(3);
  //init serial at 115200bps
  initSerial(115200);
	//delay for 112,5ns
	SysCtlDelay(3);
	UARTprintf("Ready\n");
	wait(250);
	UARTprintf("Starting loop\n");
	wait(250);

  while(1){
    position = QEIPositionGet(QEI0_BASE);
    elecAngle = mech2elec(poles, position * (2*M_PI/maxEncoder));
    alpha = invParkAlpha(d,q,elecAngle);
    beta = invParkBeta(d,q,elecAngle);
    setVoltage_PhaseA((int32_t)alpha);
    setVoltage_PhaseB((int32_t)beta);
    //UARTprintf("alpha=%d",(int32_t)alpha);
    //UARTprintf(" beta=%d",(int32_t)beta);
    //UARTprintf(" elecAngle=%d\n",(int32_t)elecAngle);
    wait(5);

/*
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
    */
  }
  return 0;
}
