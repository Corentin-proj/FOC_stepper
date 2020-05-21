/**
 * stepper.c
 * Created on: May 22, 2020
 * Author: Corentin Casier
 * Last update: May 22, 2020
 * This code manage the stepper motor (the voltage across its phases)
 * PWM phase A is on PB6 and PWM phase B on PB7
 *
 */
#include "stepper.h"

//*****************************************************************************
//
// Configure PWM for a 25% duty cycle signal running at 250Hz.
//
//*****************************************************************************
void initStepper(void)
{
    //
    // Set the clocking to run directly from the external crystal/oscillator.
    //
    /*
    MAP_SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    */

    //
    // Set the PWM clock to the system clock.
    //
    MAP_SysCtlPWMClockSet(SYSCTL_PWMDIV_1);
    /*
    //
    // Display the setup on the console.
    //
    UARTprintf("PWM ->\n");
    UARTprintf("  Module: PWM0\n");
    UARTprintf("  Pin: PB6\n");
    UARTprintf("  Configured Duty Cycle: 25%%\n");
    UARTprintf("  Inverted Duty Cycle: 75%%\n");
    UARTprintf("  Features: PWM output inversion every 2 seconds.\n\n");
    UARTprintf("Generating PWM on PWM0 (PB6) -> State = ");
    */

    //
    // The PWM peripheral must be enabled for use.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);

    //
    // Enable the GPIO port that is used for the PWM output.
    //
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    //
    // Configure the GPIO pad for PWM function on pins PB6 and PB7.
    //
    MAP_GPIOPinConfigure(GPIO_PB6_M0PWM0);
    MAP_GPIOPinConfigure(GPIO_PB7_M0PWM1);
    MAP_GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_6);
    MAP_GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_7);

    //
    // Configure PWM0 to count up/down without synchronization.
    //
    MAP_PWMGenConfigure(PWM0_BASE, PWM_GEN_0, PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC);

    //
    // Set the PWM period to 10000Hz.  To calculate the appropriate parameter
    // use the following equation: N = (1 / f) * SysClk.  Where N is the
    // function parameter, f is the desired frequency, and SysClk is the
    // system clock frequency.
    //
    MAP_PWMGenPeriodSet(PWM0_BASE, PWM_GEN_0, (SysCtlClockGet() / 10000));

    //
    // Set PWM0 to a duty cycle of 25%.  You set the duty cycle as a function
    // of the period.  Since the period was set above, you can use the
    // PWMGenPeriodGet() function.  For this example the PWM will be high for
    // 25% of the time or (PWM Period / 4).
    //
    //MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) / 4);
    //here the duty cycle is 0% on PB6
    MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) * 0);
    //here the duty cycle is 0% on PB7
    MAP_PWMPulseWidthSet(PWM0_BASE, PWM_OUT_1, MAP_PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0) * 0);

    //
    // Enable PWM Out Bit 0 (PB6) output signal.
    //
    MAP_PWMOutputState(PWM0_BASE, PWM_OUT_0_BIT | PWM_OUT_1_BIT, true);

    //
    // Enable the PWM generator block.
    //
    MAP_PWMGenEnable(PWM0_BASE, PWM_GEN_0);
    return;
}
