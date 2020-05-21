/**
 * serial.c
 * Created on: May 9, 2020
 * Author: Corentin Casier
 * Last update: May 22, 2020
 * This code manage the serial interface of the TM4C123GXL
 *
 */
#include "serial.h"

//*****************************************************************************
//
// Initialize UART0.
//
//*****************************************************************************
void initSerial(int baudrate){
  /*
  //
  // Enable lazy stacking for interrupt handlers.  This allows floating-point
  // instructions to be used within interrupt handlers, but at the expense of
  // extra stack usage.
  //
  MAP_FPUEnable();
  MAP_FPULazyStackingEnable();
  //
  // Set the clocking to run directly from the crystal.
  //
  MAP_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);
  //
  // Enable the GPIO port that is used for the on-board LED.
  //
  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  //
  // Enable the GPIO pins for the LED (PF2).
  //
  MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
  //
  // Enable the peripherals used by this example.
  //
  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
  //
  // Set GPIO A0 and A1 as UART pins.
  //
  GPIOPinConfigure(GPIO_PA0_U0RX);
  GPIOPinConfigure(GPIO_PA1_U0TX);
  MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
  //
  // Configure the UART for 115,200, 8-N-1 operation.
  //
  MAP_UARTConfigSetExpClk(UART0_BASE, MAP_SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |UART_CONFIG_PAR_NONE));
  */
  //
  // Enable the GPIO Peripheral used by the UART.
  //
  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  //
  // Enable UART0.
  //
  MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

  //
  // Configure GPIO Pins for UART mode.
  //
  MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
  MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
  MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

  //
  // Use the internal 16MHz oscillator as the UART clock source.
  //
  UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

  //
  // Initialize the UART for console I/O.
  //
  UARTStdioConfig(0, baudrate, 16000000);
  return;
}

//*****************************************************************************
//
// Send a string to the UART.
//
// Parameters: string and the number of characters in that string
//*****************************************************************************
void sendSerial(const uint8_t *pui8Buffer, uint32_t ui32Count){
    //
    // Loop while there are more characters to send.
    //
    while(ui32Count--){
        //
        // Write the next character to the UART.
        //
        MAP_UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
    }
    //MAP_UARTCharPutNonBlocking(UART0_BASE,'\n');
}
