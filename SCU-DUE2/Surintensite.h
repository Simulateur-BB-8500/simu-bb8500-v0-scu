/*
 * Surintensite.h
 *
 * Created: 23/12/2016
 * Author: Ludovic
 *
 * Avancement : Classe enti�rement cod�e et comment�e, mais non test�e avec les amp�rem�tres r�els.
 */ 


#ifndef SURINTENSITE_H
#define SURINTENSITE_H


// Include
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Pin.h"


// Seuil de disjonction (exprim� sur 1023)
#define SEUIL_DISJONCTION 1000


class Surintensite {

private :

	Pin capteurCourant ;

public :

	/** 
	 * CONSTRUCTEUR DE LA CLASSE SURINTENSITE.
	 *
	 * @param pNumPin	Num�ro du pin analogique associ� au capteur de courant des amp�rem�tres moteurs.
	 * @return			Aucun.
	 */
	Surintensite(uint32_t pNumPin) {
		capteurCourant.setPin(pNumPin, E, 0) ;
	}


	/** 
	 * MAIN FUNCTION DU CAPTEUR DE SURINTENSITE.
	 *
	 * @param ptrDisjonction	Pointeur sur la variable globale indiquant si une surintensit� a �t� mesur�e sur les amp�rem�tres moteurs.
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