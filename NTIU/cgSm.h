/*
 * cgSm.h
 *
 * Ccgated: 13/06/2017.
 * Author: Ludovic.
 */

#ifndef CGSM_H
#define CGSM_H

#include <util/delay.h>
#include "gpio.h"

#define CG_STEP_DELAY 20 // Delay between each step in ms. 

// Buttons state global variables
unsigned char previousCgPlus, currentCgPlus;
unsigned char previousCgMoins, currentCgMoins;

// State enumeration and global variables
enum cgStep {CG_STEP00, CG_STEP01, CG_STEP11, CG_STEP10};
enum cgStep cgState;

void cgBlocF() {
	previousCgPlus = currentCgPlus;
	previousCgMoins = currentCgMoins;
	currentCgPlus = CG_PLUS_PRESSED();
	currentCgMoins = CG_MOINS_PRESSED();
}

void cgBlocM() {
	switch(cgState) {
	case CG_STEP00:
		#ifdef STEP_BY_STEP
			if ((currentCgPlus != 0) && (previousCgPlus == 0)) {
		#else
			if (currentCgPlus != 0) {
		#endif
			cgState = CG_STEP01;
			_delay_ms(CG_STEP_DELAY);
		}
		else {
			#ifdef STEP_BY_STEP
				if ((currentCgMoins != 0) && (previousCgMoins == 0)) {
			#else
				if (currentCgMoins != 0) {
			#endif
				cgState = CG_STEP10;
				_delay_ms(CG_STEP_DELAY);
			}
		}
		break;
	case CG_STEP01:
		#ifdef STEP_BY_STEP
			if ((currentCgPlus != 0) && (previousCgPlus == 0)) {
		#else
			if (currentCgPlus != 0) {
		#endif
			cgState = CG_STEP11;
			_delay_ms(CG_STEP_DELAY);
		}
		else {
			#ifdef STEP_BY_STEP
				if ((currentCgMoins != 0) && (previousCgMoins == 0)) {
			#else
				if (currentCgMoins != 0) {
			#endif
				cgState = CG_STEP00;
				_delay_ms(CG_STEP_DELAY);
			}
		}
		break;
	case CG_STEP11:
		#ifdef STEP_BY_STEP
			if ((currentCgPlus != 0) && (previousCgPlus == 0)) {
		#else
			if (currentCgPlus != 0) {
		#endif
			cgState = CG_STEP10;
			_delay_ms(CG_STEP_DELAY);
		}
		else {
			#ifdef STEP_BY_STEP
				if ((currentCgMoins != 0) && (previousCgMoins == 0)) {
			#else
				if (currentCgMoins != 0) {
			#endif
				cgState = CG_STEP01;
				_delay_ms(CG_STEP_DELAY);
			}
		}
		break;
	case CG_STEP10:
		#ifdef STEP_BY_STEP
			if ((currentCgPlus != 0) && (previousCgPlus == 0)) {
		#else
			if (currentCgPlus != 0) {
		#endif
			cgState = CG_STEP00;
			_delay_ms(CG_STEP_DELAY);
		}
		else {
			#ifdef STEP_BY_STEP
				if ((currentCgMoins != 0) && (previousCgMoins == 0)) {
			#else
				if (currentCgMoins != 0) {
			#endif
				cgState = CG_STEP11;
				_delay_ms(CG_STEP_DELAY);
			}
		}
		break;
	default:
		break;
	}
}

void cgBlocG() {
	switch(cgState) {
	case CG_STEP00:
		CG_1_LOW();
		CG_2_LOW();
		break;
	case CG_STEP01:
		CG_1_LOW();
		CG_2_HIGH();
		break;
	case CG_STEP11:
		CG_1_HIGH();
		CG_2_HIGH();
		break;
	case CG_STEP10:
		CG_1_HIGH();
		CG_2_LOW();
		break;
	default:
		break;
	}
}

void runCgStateMachine() {
	cgBlocF();
	cgBlocM();
	cgBlocG();
}


#endif /* CGSM_H_ */