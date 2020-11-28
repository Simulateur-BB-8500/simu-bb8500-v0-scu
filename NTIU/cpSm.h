/*
 * cpSm.h
 *
 * Created: 13/06/2017.
 * Author: Ludovic.
 */

#ifndef CPSM_H
#define CPSM_H

#include <util/delay.h>
#include "gpio.h"

#define CP_STEP_DELAY 20 // Delay between each step in ms. 

// Buttons state global variables
unsigned char previousCpPlus, currentCpPlus;
unsigned char previousCpMoins, currentCpMoins;

// State enumeration and global variables
enum cpStep {CP_STEP00, CP_STEP01, CP_STEP11, CP_STEP10};
enum cpStep cpState;

void cpBlocF() {
	previousCpPlus = currentCpPlus;
	previousCpMoins = currentCpMoins;
	currentCpPlus = CP_PLUS_PRESSED();
	currentCpMoins = CP_MOINS_PRESSED();
}

void cpBlocM() {
	switch(cpState) {
	case CP_STEP00:
		#ifdef STEP_BY_STEP
			if ((currentCpPlus != 0) && (previousCpPlus == 0)) {
		#else
			if (currentCpPlus != 0) {
		#endif
			cpState = CP_STEP01;
			_delay_ms(CP_STEP_DELAY);
		}
		else {
			#ifdef STEP_BY_STEP
				if ((currentCpMoins != 0) && (previousCpMoins == 0)) {
			#else
				if (currentCpMoins != 0) {
			#endif
				cpState = CP_STEP10;
				_delay_ms(CP_STEP_DELAY);
			}
		}
		break;
	case CP_STEP01:
		#ifdef STEP_BY_STEP
			if ((currentCpPlus != 0) && (previousCpPlus == 0)) {
		#else
			if (currentCpPlus != 0) {
		#endif
			cpState = CP_STEP11;
			_delay_ms(CP_STEP_DELAY);
		}
		else {
			#ifdef STEP_BY_STEP
				if ((currentCpMoins != 0) && (previousCpMoins == 0)) {
			#else
				if (currentCpMoins != 0) {
			#endif
				cpState = CP_STEP00;
				_delay_ms(CP_STEP_DELAY);
			}
		}
		break;
	case CP_STEP11:
		#ifdef STEP_BY_STEP
			if ((currentCpPlus != 0) && (previousCpPlus == 0)) {
		#else
			if (currentCpPlus != 0) {
		#endif
			cpState = CP_STEP10;
			_delay_ms(CP_STEP_DELAY);
		}
		else {
			#ifdef STEP_BY_STEP
				if ((currentCpMoins != 0) && (previousCpMoins == 0)) {
			#else
				if (currentCpMoins != 0) {
			#endif
				cpState = CP_STEP01;
				_delay_ms(CP_STEP_DELAY);
			}
		}
		break;
	case CP_STEP10:
		#ifdef STEP_BY_STEP
			if ((currentCpPlus != 0) && (previousCpPlus == 0)) {
		#else
			if (currentCpPlus != 0) {
		#endif
			cpState = CP_STEP00;
			_delay_ms(CP_STEP_DELAY);
		}
		else {
			#ifdef STEP_BY_STEP
				if ((currentCpMoins != 0) && (previousCpMoins == 0)) {
			#else
				if (currentCpMoins != 0) {
			#endif
				cpState = CP_STEP11;
				_delay_ms(CP_STEP_DELAY);
			}
		}
		break;
	default:
		break;
	}
}

void cpBlocG() {
	switch(cpState) {
	case CP_STEP00:
		CP_1_LOW();
		CP_2_LOW();
		break;
	case CP_STEP01:
		CP_1_LOW();
		CP_2_HIGH();
		break;
	case CP_STEP11:
		CP_1_HIGH();
		CP_2_HIGH();
		break;
	case CP_STEP10:
		CP_1_HIGH();
		CP_2_LOW();
		break;
	default:
		break;
	}
}

void runCpStateMachine() {
	cpBlocF();
	cpBlocM();
	cpBlocG();
}


#endif /* CPSM_H_ */