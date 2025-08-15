/*
 * Amperemetre.h
 *
 * Created: 28/03/2016
 * Author: Ludovic
 */

#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Pin.h"

#ifndef AMPEREMETRE_H
#define AMPEREMETRE_H


class Amperemetre {
	
private :
	Pin pinAmp ;

public :

	/* Constructeur */
	
	Amperemetre(uint32_t pNumAmp) {
		pinAmp.setPin(pNumAmp, S, 0) ;
	}
	
	/* M�thodes */
	
	// Initialisation de l'amp�rem�tre
	void init() {
		pinMode(pinAmp.getNumPin(), OUTPUT) ;
		pinAmp.write(GND) ;
	}
	
	// Affiche une intensit� sur l'amp�rem�tre
	void setIntensite() {
	}
} ;

#endif