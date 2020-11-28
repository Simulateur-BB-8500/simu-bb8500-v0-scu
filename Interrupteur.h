/*
 * Interrupteur.h
 *
 * Created: 09/03/2016
 * Author: Ludovic
 */

#include "Pin.h"

#ifndef INTERRUPTEUR_H
#define INTERRUPTEUR_H

#define N true
#define I false

class Interrupteur {
	
private :
	Pin pin ;
	boolean logique ;
	// On considère qu'un interrupteur est câblé avec une resistance de pull-up (interne ou externe)
	
public :
	
	/* Constructeurs */
	
	// Constructeur sans argument
	Interrupteur() {
		pin.setPin(0, E, 0) ;
		logique = N ;
	}
	
	// Constructeur de recopie
	Interrupteur(const Interrupteur& modele) {
		pin = modele.pin ;
		logique = modele.logique ;
	}
	
	// Constructeur avec arguments
	Interrupteur(uint32_t pNum, boolean pLogique, uint32_t pTempo) {
		if (pLogique == I) {
			logique = I ;
		}
		else {
			logique = N ;
		}
		pin.setPin(pNum, E, pTempo) ;
	}
	
	/* Méthodes */
	
	// Initialisation de l'interrupteur
	void init() {
		pinMode(pin.getNumPin(), INPUT_PULLUP) ;
	}
	
	// Retourne true si l'interrupteur est sur marche, false sinon
	boolean marche() {
		boolean resultat = false ;
		if (logique == N) {
			resultat = (pin.read() <= TENSION_REF/2.0) ;
		}
		else {
			resultat = (pin.read() >= TENSION_REF/2.0) ;
		}
		return resultat ;
	}
	
	// Retourne true si l'interrupteur est sur arrêt, false sinon
	boolean arret() {
		return !(marche()) ;
	}
} ;

#endif