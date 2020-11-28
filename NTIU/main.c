/*
 * main.c
 *
 * Created: 26/05/2017.
 * Author: Ludovic.
 */


/* Control mode :	if 'STEP_BY_STEP' : 1 button press = 1 step.
					otherwise : Revolution while the button is pressed. */
//#define STEP_BY_STEP

#define F_CPU 1000000 // AVR clock frequency in Hz, used by util/delay.h

#include <util/delay.h>
#include <avr/io.h>
#include "gpio.h"
#include "cpSm.h"
#include "reSm.h"
#include "cgSm.h"
#include "cf1Sm.h"
#include "cf2Sm.h"

int main(void) {
	
	gpioInit();

	while (1) {
		runCpStateMachine();
		runReStateMachine();
		runCgStateMachine();
		runCf1StateMachine();
		runCf2StateMachine();
	}
}

