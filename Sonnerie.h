/*
 * Sonnerie.h
 *
 * Created: 28/03/2016
 * Author: Ludovic
 */

#include "Pin.h"

#ifndef SONNERIE_H
#define SONNERIE_H

class Sonnerie {
	
private :
	Pin pin ;

public :

	/* Constructeur */
	
	// Constructeur sans argument
	Sonnerie() {
		pin.setPin(0, S, 0) ;
	}
	
	// Constructeur de recopie
	Sonnerie(const Sonnerie& modele) {
		pin = modele.pin ;
	}
	
	// Constructeur avec argument
	Sonnerie(uint32_t pNum) {
		pin.setPin(pNum, S, 0) ;
	}
	
	/* Méthodes */
	
	// Initialisation de l'élément sonore
	void init() {
		pinMode(pin.getNumPin(), OUTPUT) ;
		pin.write(GND) ;
	}
	
	// Allume la sonnerie
	void allumer() {
		pin.write(TENSION_REF) ;
	}
	
	// Eteint la sonnerie
	void eteindre() {
		pin.write(GND) ;
	}
} ;

#endif