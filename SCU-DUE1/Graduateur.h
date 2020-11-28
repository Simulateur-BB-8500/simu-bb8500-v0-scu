/*
 * Graduateur.h
 *
 * Created: 17/04/2016
 * Author: Ludovic
 */ 

#include "Arduino.h"
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Instructions.h"

#ifndef GRADUATEUR_H
#define GRADUATEUR_H

#define NB_CRANS 24
#define PERIODE_CRAN 1000 // Fréquence de passage des crans en progression et régression rapides (en ms)

class Graduateur {
	
private :
	boolean regRapide ;
	boolean progRapide ;
	boolean prog_ac ;
	boolean prog_pr ;
	boolean reg_ac ;
	boolean reg_pr ;
	uint32_t timeKeyboard ;
	uint32_t timePeriodic ;
	int n ; // Compteur de secondes pour la progression et la régression rapides

public :

	/* Constructeur */
	
	Graduateur() {
		regRapide = false ;
		progRapide = false ;
		prog_ac = false ;
		prog_pr = false ;
		reg_ac = false ;
		reg_pr = false ;
		timeKeyboard = 0 ;
		timePeriodic = 0 ;
		n = 0 ;
	}
	
	/* Méthodes */
	
	void resetProg() {
		prog_ac = false ;
	}
	
	void resetProgRapide() {
		progRapide = false ;
	}
	
	void resetReg() {
		reg_ac = false ;
	}
	
	void resetRegRapide() {
		regRapide = false ;
	}
	
	void majState() {
		prog_pr = prog_ac ;
		reg_pr = reg_ac ;
	}
	
	void majKeyboard() {
		if (millis() > timeKeyboard + DUREE_KEYBOARD_TRACTION) {
			Keyboard.release(K_TRAC_P) ;
			Keyboard.release(K_TRAC_M) ;
		}
	}
	
	// Manip à 0
	void regressionRapide(int* ptrCran) {
		if (regRapide == false) {
			timePeriodic = millis() ;
			n = 0 ;
			regRapide = true ;
		}
		if (*ptrCran > 1) {
			regression(ptrCran) ;
			if ((millis() > (timePeriodic+n*PERIODE_CRAN)) && ((*ptrCran) > 0)) {
				n++ ;
				resetReg() ;
			}
		}
		// Si on arrive au premier cran, on appui plus longuement sur le raccourci de régression
		// pour être certain de revenir à 0% sur OpenRails
		else {
			if (millis() < (timePeriodic+(n-1)*1000+DUREE_KEYBOARD_CRAN_0)) {
				Keyboard.press(K_TRAC_M) ;
			}
			else {
				// Graduateur à 0
				Keyboard.release(K_TRAC_M) ;
				(*ptrCran) = 0 ;
			}
		}
	}
	
	// Traction + et Freinage rhéostatique +
	void progression(int* ptrCran) {
		prog_ac = true ;
		Keyboard.release(K_TRAC_M) ;
		if ((*ptrCran) < NB_CRANS) {
			if (prog_pr == false) {
				Keyboard.press(K_TRAC_P) ;
				timeKeyboard = millis() ;
				(*ptrCran)++ ;
			}
		}
	}
	
	// Traction - et Freinage rhéostatique -
	void regression(int* ptrCran) {
		reg_ac = true ;
		Keyboard.release(K_TRAC_P) ;
		if ((*ptrCran) > 0) {
			if (reg_pr == false) {
				Keyboard.press(K_TRAC_M) ;
				timeKeyboard = millis() ;
				(*ptrCran)-- ;
			}
		}
	}
	
	// Progression et Freinage rhéostatique rapides
	void progressionRapide(int* ptrCran) {
		if (progRapide == false) {
			timePeriodic = millis() ;
			n = 0 ;
			progRapide = true ;
		}
		progression(ptrCran) ;
		if (*ptrCran < NB_CRANS-1) {
			if ((millis() > (timePeriodic+n*1000)) && ((*ptrCran) < NB_CRANS)) {
				n++ ;
				resetProg() ;
			}
		}
	}
	
	// Préparation au freinage rhéostatique
	void preparation(int* ptrCran) {
		
	}
} ;


#endif