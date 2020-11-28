/*
 * Lampe.h
 *
 * Created: 15/03/2016
 * Author: Ludovic
 */

#include "Pin.h"

#ifndef LAMPE_H
#define LAMPE_H

class Lampe {
	
private :
	Pin pin ;
	boolean allumee ;

public :

	/* Constructeur */
	
	// Constructeur sans argument
	Lampe() {
		pin.setPin(0, S, 0) ;
		allumee = false ;
	}
	
	// Constructeur de recopie
	Lampe(const Lampe& modele) {
		pin = modele.pin ;
		allumee = modele.allumee ;
	}
	
	// Constructeur avec argument
	Lampe(uint32_t pNum) {
		pin.setPin(pNum, S, 0) ;
		allumee = false ;
	}
	
	/* Méthodes */
	
	// Initialisation de l'indicateur lumineux
	void init() {
		pinMode(pin.getNumPin(), OUTPUT) ;
		pin.write(GND) ;
	}
	
	// Allume l'indicateur lumineux
	void allumer() {
		pin.write(TENSION_REF) ;
		allumee = true ;
	}
	
	// Allume l'indicateur lumineux avec une tension donnée en paramètre (cas des PWM)
	void graduer(float tension) {
		pin.write(tension) ;
		allumee = true ;
	}
	
	// Eteint l'indicateur lumineux
	void eteindre() {
		pin.write(GND) ;
		allumee = false ;
	}
	
	// Inverse l'état de la lampe
	void inverser() {
		if (allumee) {
			eteindre() ;
		}
		else {
			allumer() ;
		}
	}
} ;

#endif