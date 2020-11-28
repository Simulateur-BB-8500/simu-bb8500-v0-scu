/*
 * Inverseurh.h
 *
 * Created: 20/04/2016
 * Author: Ludovic
 */ 

#ifndef INVERSEURH_H
#define INVERSEURH_H

#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Selecteur3.h"
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Instructions.h"

class Inverseur {
	
private :
	Selecteur3 manette ;
	boolean neutre ;
	boolean avant ;
	uint32_t timeOffset ;
	
public :
	
	/* Constructeur */
	
	Inverseur(Selecteur3 pManette) {
		manette = pManette ;
		neutre = true ;
		avant = false ;
		timeOffset = 0 ;
	}
	
	/* Méthodes */
	
	void init() {
		manette.init() ;
	}
	
	void majKeyboard() {
		if (millis() > timeOffset + DUREE_KEYBOARD) {
			Keyboard.release(K_INV_AV) ;
			Keyboard.release(K_INV_AR) ;
		}
	}
	
	void update() {
		if (manette.neutre()) {
			SerialUSB.write(I_Inverseur_Neutre) ;
			if (neutre == false) {
				neutre = true ;
				timeOffset = millis() ;
				// Keyboard inverseur neutre
				if (avant == true) {
					Keyboard.press(K_INV_AR) ;
					timeOffset = millis() ;
				}
				else {
					Keyboard.press(K_INV_AV) ;
					timeOffset = millis() ;
				}
			}
		}
		else {
			SerialUSB.write(I_Inverseur_AR_AV) ;
			if ((manette.P2()) && (neutre == true)) {
				// Inverseur avant
				Keyboard.press(K_INV_AV) ;
				timeOffset = millis() ;
				neutre = false ; // A conserver à l'intérieur des "if" à cause des transitions électriques
				avant = true ;
			}
			if ((manette.P1()) && (neutre == true)) {
				// Inverseur arrière
				Keyboard.press(K_INV_AR) ;
				timeOffset = millis() ;
				neutre = false ;
				avant = false ;
			}
		}
		majKeyboard() ;
	}
} ;

#endif