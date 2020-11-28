/*
 * Manometre.h
 *
 * Created: 21/04/2016
 * Author: Ludovic
 */

#ifndef MANOMETRE_H
#define MANOMETRE_H

#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/MoteurPasAPas.h"

#define NB_PAS 64


class Manometre {
	
private :
	MoteurPasAPas mpp ;
	float vitesse ; // en bar/ms
	float consigne ;

public :

	/* Constructeur */
	
	Manometre(MoteurPasAPas pMpp) {
		mpp = pMpp ;
	}
	
	/* Méthodes */
	
	void augmenter() {
		mpp.step(1) ;
	}
	
	void diminuer() {
		mpp.step(-1) ;
	}
} ;

#endif