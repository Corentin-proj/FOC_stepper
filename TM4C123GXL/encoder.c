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
  return;
}
