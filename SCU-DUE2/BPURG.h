/*
 * BPURG.h
 *
 * Created: 23/12/2016
 * Author: Ludovic Lesur
 *
 * Avancement : Classe entièrement codée et commentée, mais non testée sur le BPURG.
 */ 


#ifndef BPURG_H
#define BPURG_H


// Include
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Interrupteur.h"


class BPURG {

private :

	Interrupteur bpurg ;

public :

	/** 
	 * CONSTRUCTEUR DE LA CLASSE BPURG.
	 *
	 * @param pBpurg	Bouton poussoir BPURG de type 'Interrupteur'.
	 * @return			Aucun.
	 */
	BPURG(Interrupteur pBpurg) {
		bpurg = pBpurg ;
	}


	/** 
	 * INITIALISE LE BPURG.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void init() {
		bpurg.init() ;
	}


	/** 
	 * MAIN FUNCTION DU BPURG.
	 *
	 * @param ptrUrgence	Pointeur sur la variable globale 'urgence' indiquant si un freinage d'urgence a été déclenché.
	 * @return				Aucun.
	 */
	void run(boolean* ptrUrgence) {
		if (bpurg.marche()) {
			(*ptrUrgence) = true ;
		}
		else {
			(*ptrUrgence) = false ;
		}
	}
} ;


#endif