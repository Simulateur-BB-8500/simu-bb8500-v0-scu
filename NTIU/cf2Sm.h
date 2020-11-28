/*
 * cf2Sm.h
 *
 * Ccf2ated: 13/06/2017.
 * Author: Ludovic.
 */

#ifndef CF2SM_H
#define CF2SM_H

#include <util/delay.h>
#include "gpio.h"

#define CF2_STEP_DELAY 20 // Delay between each step in ms. 

// Buttons state global variables
unsigned char previousCf2Plus, currentCf2Plus;
unsigned char previousCf2Moins, currentCf2Moins;

// State enumeration and global variables
enum cf2Step {CF2_STEP00, CF2_STEP01, CF2_STEP11, CF2_STEP10};
enum cf2Step cf2State;

void cf2BlocF() {
	previousCf2Plus = currentCf2Plus;
	previousCf2Moins = currentCf2Moins;
	currentCf2Plus = CF2_PLUS_PRESSED();
	currentCf2Moins = CF2_MOINS_PRESSED();
}

void cf2BlocM() {
	switch(cf2State) {
	case CF2_STEP00:
		#ifdef STEP_BY_STEP
			if ((currentCf2Plus != 0) && (previousCf2Plus == 0)) {
		#else
			if (currentCf2Plus != 0) {
		#endif
			cf2State = CF2_STEP01;
			_delay_ms(CF2_STEP_DELAY);
		}
		else {
			#ifdef STEP_BY_STEP
				if ((currentCf2Moins != 0) && (previousCf2Moins == 0)) {
			#else
				if (currentCf2Moins != 0) {
			#endif
				cf2State = CF2_STEP10;
				_delay_ms(CF2_STEP_DELAY);
			}
		}
		break;
	case CF2_STEP01:
		#ifdef STEP_BY_STEP
			if ((currentCf2Plus != 0) && (previousCf2Plus == 0)) {
		#else
			if (currentCf2Plus != 0) {
		#endif
			cf2State = CF2_STEP11;
			_delay_ms(CF2_STEP_DELAY);
		}
		else {
			#ifdef STEP_BY_STEP
				if ((currentCf2Moins != 0) && (previousCf2Moins == 0)) {
			#else
				if (currentCf2Moins != 0) {
			#endif
				cf2State = CF2_STEP00;
				_delay_ms(CF2_STEP_DELAY);
			}
		}
		break;
	case CF2_STEP11:
		#ifdef STEP_BY_STEP
			if ((currentCf2Plus != 0) && (previousCf2Plus == 0)) {
		#else
			if (currentCf2Plus != 0) {
		#endif
			cf2State = CF2_STEP10;
			_delay_ms(CF2_STEP_DELAY);
		}
		else {
			#ifdef STEP_BY_STEP
				if ((currentCf2Moins != 0) && (previousCf2Moins == 0)) {
			#else
				if (currentCf2Moins != 0) {
			#endif
				cf2State = CF2_STEP01;
				_delay_ms(CF2_STEP_DELAY);
			}
		}
		break;
	case CF2_STEP10:
		#ifdef STEP_BY_STEP
			if ((currentCf2Plus != 0) && (previousCf2Plus == 0)) {
		#else
			if (currentCf2Plus != 0) {
		#endif
			cf2State = CF2_STEP00;
			_delay_ms(CF2_STEP_DELAY);
		}
		else {
			#ifdef STEP_BY_STEP
				if ((currentCf2Moins != 0) && (previousCf2Moins == 0)) {
			#else
				if (currentCf2Moins != 0) {
			#endif
				cf2State = CF2_STEP11;
				_delay_ms(CF2_STEP_DELAY);
			}
		}
		break;
	default:
		break;
	}
}

void cf2BlocG() {
	switch(cf2State) {
	case CF2_STEP00:
		CF2_1_LOW();
		CF2_2_LOW();
		break;
	case CF2_STEP01:
		CF2_1_LOW();
		CF2_2_HIGH();
		break;
	case CF2_STEP11:
		CF2_1_HIGH();
		CF2_2_HIGH();
		break;
	case CF2_STEP10:
		CF2_1_HIGH();
		CF2_2_LOW();
		break;
	default:
		break;
	}
}

void runCf2StateMachine() {
	cf2BlocF();
	cf2BlocM();
	cf2BlocG();
}


#endif /* CF2SM_H_ */