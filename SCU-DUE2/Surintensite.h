/*
 * Surintensite.h
 *
 * Created: 23/12/2016
 * Author: Ludovic
 *
 * Avancement : Classe entièrement codée et commentée, mais non testée avec les ampèremètres réels.
 */ 


#ifndef SURINTENSITE_H
#define SURINTENSITE_H


// Include
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Pin.h"


// Seuil de disjonction (exprimé sur 1023)
#define SEUIL_DISJONCTION 1000


class Surintensite {

private :

	Pin capteurCourant ;

public :

	/** 
	 * CONSTRUCTEUR DE LA CLASSE SURINTENSITE.
	 *
	 * @param pNumPin	Numéro du pin analogique associé au capteur de courant des ampèremètres moteurs.
	 * @return			Aucun.
	 */
	Surintensite(uint32_t pNumPin) {
		capteurCourant.setPin(pNumPin, E, 0) ;
	}


	/** 
	 * MAIN FUNCTION DU CAPTEUR DE SURINTENSITE.
	 *
	 * @param ptrDisjonction	Pointeur sur la variable globale indiquant si une surintensité a été mesurée sur les ampèremètres moteurs.
	 * @return					Aucun.
	 */
	void run(boolean* ptrSurintensite) {
		if (capteurCourant.read() > SEUIL_DISJONCTION) {
			(*ptrSurintensite) = true ;
		}
		else {
			(*ptrSurintensite) = false ;
		}
	}
} ;


#endif