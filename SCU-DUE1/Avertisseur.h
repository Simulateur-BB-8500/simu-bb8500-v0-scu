/*
 * Avertisseur.h
 *
 * Created: 20/04/2016
 * Author: Ludovic
 */ 

#ifndef AVERTISSEUR_H
#define AVERTISSEUR_H

#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Selecteur3.h"
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Instructions.h"


class Avertisseur {
	
private :
	boolean ton ; // Indique le dernier ton utilisé : =0 si bas ; =1 si haut
	Selecteur3 sifflet ;
	
public :

	/* Constructeur */
	
	Avertisseur(Selecteur3 pSifflet) {
		sifflet = pSifflet ;
	}
	
	/* Méthodes */
	
	void init() {
		sifflet.init() ;
	}
	
	void update() {
		if (sifflet.neutre()) {
			if (ton == 0) {
				SerialUSB.write(I_S_Bas_Off) ;
			}
			else {
				SerialUSB.write(I_S_Haut_Off) ;
			}
		}
		if (sifflet.P1()) {
			SerialUSB.write(I_S_Haut_On) ;
			ton = 1 ;		
		}
		if (sifflet.P2()) {
			SerialUSB.write(I_S_Bas_On) ;
			ton = 0 ;
		}
	}
} ;

#endif