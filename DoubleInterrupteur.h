/*
 * DoubleInterrupteur.h
 *
 * Created: 28/03/2016
 * Author: Ludovic
 */

#include "Pin.h"

#ifndef DOUBLEINTERRUPTEUR_H
#define DOUBLEINTERRUPTEUR_H

// Tension moyenne entre les 4 états
#define diSeuil1 0.535
#define diSeuil2 1.28
#define diSeuil3 1.68

class DoubleInterrupteur {
	
private :
	Pin pin ;
	// On considère que les deux interrupteurs sont non-inverseurs
	
public :
	
	/* Constructeurs */
	
	// Constructeur sans argument
	DoubleInterrupteur() {
		pin.setPin(0, E, 0) ;
	}
	
	// Constructeur de recopie
	DoubleInterrupteur(const DoubleInterrupteur& modele) {
		pin = modele.pin ;
	}
	
	// Constructeur avec arguments
	DoubleInterrupteur(uint32_t pNum) {
		pin.setPin(pNum, E, 0) ;
	}
	
	/* Méthodes */
	
	void init() {
		pinMode(pin.getNumPin(), INPUT) ;
	}
	
	// Retourne true si les deux interrupteurs sont sur arrêt, false sinon
	boolean aucun() {
		return (pin.read() < diSeuil1) ;
	}
	
	// Retourne true si l'interrupteur Z1 (connecté à la 56k) est sur marche
	// et si l'interrupteur Z2 (connecté à la 33k) est sur arrêt, false sinon
	boolean z1Seul() {
		return ((pin.read() >= diSeuil1) && (pin.read() < diSeuil2)) ;
	}
	
	// Retourne true si l'interrupteur Z1 (connecté à la 56k) est sur marche
	// et si l'interrupteur Z2 (connecté à la 33k) est sur arrêt, false sinon
	boolean z2Seul() {
		return ((pin.read() >= diSeuil2) && (pin.read() < diSeuil3)) ;
	}
	
	// Retourne true si les deux interrupteurs sont sur marche, false sinon
	boolean tous() {
		return (pin.read() >= diSeuil3) ;
	}

	// Retourne true si Z1 est sur marche (quelque soit Z2).
	boolean z1() {
		return (z1Seul() || tous()) ; 
	}

	// Retourne true si Z2 est sur marche (quelque soit Z1).
	boolean z2() {
		return (z2Seul() || tous()) ;
	}
} ;

#endif