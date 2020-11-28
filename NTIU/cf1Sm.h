/*
 * cf1Sm.h
 *
 * Ccf1ated: 13/06/2017.
 * Author: Ludovic.
 */

#ifndef CF1SM_H
#define CF1SM_H

#include <util/delay.h>
#include "gpio.h"

#define CF1_STEP_DELAY 20 // Delay between each step in ms. 

// Buttons state global variables
unsigned char previousCf1Plus, currentCf1Plus;
unsigned char previousCf1Moins, currentCf1Moins;

// State enumeration and global variables
enum cf1Step {CF1_STEP00, CF1_STEP01, CF1_STEP11, CF1_STEP10};
enum cf1Step cf1State;

void cf1BlocF() {
	previousCf1Plus = currentCf1Plus;
	previousCf1Moins = currentCf1Moins;
	currentCf1Plus = CF1_PLUS_PRESSED();
	currentCf1Moins = CF1_MOINS_PRESSED();
}

void cf1BlocM() {
	switch(cf1State) {
	case CF1_STEP00:
		#ifdef STEP_BY_STEP
			if ((currentCf1Plus != 0) && (previousCf1Plus == 0)) {
		#else
			if (currentCf1Plus != 0) {
		#endif
			cf1State = CF1_STEP01;
			_delay_ms(CF1_STEP_DELAY);
		}
		else {
			#ifdef STEP_BY_STEP
				if ((currentCf1Moins != 0) && (previousCf1Moins == 0)) {
			#else
				if (currentCf1Moins != 0) {
			#endif
				cf1State = CF1_STEP10;
				_delay_ms(CF1_STEP_DELAY);
			}
		}
		break;
	case CF1_STEP01:
		#ifdef STEP_BY_STEP
			if ((currentCf1Plus != 0) && (previousCf1Plus == 0)) {
		#else
			if (currentCf1Plus != 0) {
		#endif
			cf1State = CF1_STEP11;
			_delay_ms(CF1_STEP_DELAY);
		}
		else {
			#ifdef STEP_BY_STEP
				if ((currentCf1Moins != 0) && (previousCf1Moins == 0)) {
			#else
				if (currentCf1Moins != 0) {
			#endif
				cf1State = CF1_STEP00;
				_delay_ms(CF1_STEP_DELAY);
			}
		}
		break;
	case CF1_STEP11:
		#ifdef STEP_BY_STEP
			if ((currentCf1Plus != 0) && (previousCf1Plus == 0)) {
		#else
			if (currentCf1Plus != 0) {
		#endif
			cf1State = CF1_STEP10;
			_delay_ms(CF1_STEP_DELAY);
		}
		else {
			#ifdef STEP_BY_STEP
				if ((currentCf1Moins != 0) && (previousCf1Moins == 0)) {
			#else
				if (currentCf1Moins != 0) {
			#endif
				cf1State = CF1_STEP01;
				_delay_ms(CF1_STEP_DELAY);
			}
		}
		break;
	case CF1_STEP10:
		#ifdef STEP_BY_STEP
			if ((currentCf1Plus != 0) && (previousCf1Plus == 0)) {
		#else
			if (currentCf1Plus != 0) {
		#endif
			cf1State = CF1_STEP00;
			_delay_ms(CF1_STEP_DELAY);
		}
		else {
			#ifdef STEP_BY_STEP
				if ((currentCf1Moins != 0) && (previousCf1Moins == 0)) {
			#else
				if (currentCf1Moins != 0) {
			#endif
				cf1State = CF1_STEP11;
				_delay_ms(CF1_STEP_DELAY);
			}
		}
		break;
	default:
		break;
	}
}

void cf1BlocG() {
	switch(cf1State) {
	case CF1_STEP00:
		CF1_1_LOW();
		CF1_2_LOW();
		break;
	case CF1_STEP01:
		CF1_1_LOW();
		CF1_2_HIGH();
		break;
	case CF1_STEP11:
		CF1_1_HIGH();
		CF1_2_HIGH();
		break;
	case CF1_STEP10:
		CF1_1_HIGH();
		CF1_2_LOW();
		break;
	default:
		break;
	}
}

void runCf1StateMachine() {
	cf1BlocF();
	cf1BlocM();
	cf1BlocG();
}


#endif /* CF1SM_H_ */