/**
 * encoder.c
 * Created on: May 3, 2020
 * Author: Corentin Casier
 * Last update: May 3, 2020
 * This code manage the encoder interface of the TM4C123GXL
 *
 */
#include "encoder.h"

void initEncoder(int counts){
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
  //Unlock GPIOD7
  HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
  HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= 0x80;
  HWREG(GPIO_PORTD_BASE + GPIO_O_AFSEL) &= ~0x80;
  HWREG(GPIO_PORTD_BASE + GPIO_O_DEN) |= 0x80;
  HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;
  // Enable QEI Peripherals
  SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);
  //Set Pins to be PHA0 and PHB0
	GPIOPinConfigure(GPIO_PD6_PHA0); //GPIOPinConfigure(0x00031806);  //0x00031806 =>GPIO_PD6_PHA0
	GPIOPinConfigure(GPIO_PD7_PHB0); //GPIOPinConfigure(0x00031C06);  // 0x00031C06 => GPIO_PD7_PHB0
  //Set GPIO pins for QEI
	GPIOPinTypeQEI(GPIO_PORTD_BASE, (GPIO_PIN_6 | GPIO_PIN_7));
  // Enable the QEI0 peripheral
  SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);
  // Wait for the QEI0 module to be ready.
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_QEI0)){
  }
  // Configure the quadrature encoder to capture edges on both signals. Using a
  // 400 line encoder at four edges per line, there are 1600 pulses per
  // revolution; therefore set the maximum position to 1599 as the count
  // is zero based.
  QEIConfigure(QEI0_BASE, (QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_NO_RESET |QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP), counts);
  // Enable the quadrature encoder.
  QEIEnable(QEI0_BASE);
  //Configure and enable velocity
  QEIVelocityConfigure(QEI0_BASE, QEI_VELDIV_1, SysCtlClockGet()); // Divide by clock speed to get counts/sec
  QEIVelocityEnable(QEI0_BASE);

  return;
}
