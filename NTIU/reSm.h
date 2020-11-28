/*
 * reSm.h
 *
 * Created: 13/06/2017.
 * Author: Ludovic.
 */

#ifndef RESM_H
#define RESM_H

#include <util/delay.h>
#include "gpio.h"

#define RE_STEP_DELAY 20 // Delay between each step in ms. 

// Buttons state global variables
unsigned char previousRePlus, currentRePlus;
unsigned char previousReMoins, currentReMoins;

// State enumeration and global variables
enum reStep {RE_STEP00, RE_STEP01, RE_STEP11, RE_STEP10};
enum reStep reState;

void reBlocF() {
	previousRePlus = currentRePlus;
	previousReMoins = currentReMoins;
	currentRePlus = RE_PLUS_PRESSED();
	currentReMoins = RE_MOINS_PRESSED();
}

void reBlocM() {
	switch(reState) {
	case RE_STEP00:
		#ifdef STEP_BY_STEP
			if ((currentRePlus != 0) && (previousRePlus == 0)) {
		#else
			if (currentRePlus != 0) {
		#endif
			reState = RE_STEP01;
			_delay_ms(RE_STEP_DELAY);
		}
		else {
			#ifdef STEP_BY_STEP
				if ((currentReMoins != 0) && (previousReMoins == 0)) {
			#else
				if (currentReMoins != 0) {
			#endif
				reState = RE_STEP10;
				_delay_ms(RE_STEP_DELAY);
			}
		}
		break;
	case RE_STEP01:
		#ifdef STEP_BY_STEP
			if ((currentRePlus != 0) && (previousRePlus == 0)) {
		#else
			if (currentRePlus != 0) {
		#endif
			reState = RE_STEP11;
			_delay_ms(RE_STEP_DELAY);
		}
		else {
			#ifdef STEP_BY_STEP
				if ((currentReMoins != 0) && (previousReMoins == 0)) {
			#else
				if (currentReMoins != 0) {
			#endif
				reState = RE_STEP00;
				_delay_ms(RE_STEP_DELAY);
			}
		}
		break;
	case RE_STEP11:
		#ifdef STEP_BY_STEP
			if ((currentRePlus != 0) && (previousRePlus == 0)) {
		#else
			if (currentRePlus != 0) {
		#endif
			reState = RE_STEP10;
			_delay_ms(RE_STEP_DELAY);
		}
		else {
			#ifdef STEP_BY_STEP
				if ((currentReMoins != 0) && (previousReMoins == 0)) {
			#else
				if (currentReMoins != 0) {
			#endif
				reState = RE_STEP01;
				_delay_ms(RE_STEP_DELAY);
			}
		}
		break;
	case RE_STEP10:
		#ifdef STEP_BY_STEP
			if ((currentRePlus != 0) && (previousRePlus == 0)) {
		#else
			if (currentRePlus != 0) {
		#endif
			reState = RE_STEP00;
			_delay_ms(RE_STEP_DELAY);
		}
		else {
			#ifdef STEP_BY_STEP
				if ((currentReMoins != 0) && (previousReMoins == 0)) {
			#else
				if (currentReMoins != 0) {
			#endif
				reState = RE_STEP11;
				_delay_ms(RE_STEP_DELAY);
			}
		}
		break;
	default:
		break;
	}
}

void reBlocG() {
	switch(reState) {
	case RE_STEP00:
		RE_1_LOW();
		RE_2_LOW();
		break;
	case RE_STEP01:
		RE_1_LOW();
		RE_2_HIGH();
		break;
	case RE_STEP11:
		RE_1_HIGH();
		RE_2_HIGH();
		break;
	case RE_STEP10:
		RE_1_HIGH();
		RE_2_LOW();
		break;
	default:
		break;
	}
}

void runReStateMachine() {
	reBlocF();
	reBlocM();
	reBlocG();
}


#endif /* RESM_H_ */