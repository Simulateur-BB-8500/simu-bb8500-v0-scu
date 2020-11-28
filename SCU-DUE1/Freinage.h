/*
 * Freinage.h
 *
 * Created: 05/07/2016
 * Author: Ludovic
 */ 

#ifndef FREINAGE_H
#define FREINAGE_H

#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Interrupteur.h"
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Selecteur3.h"
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Selecteur4.h"

class Freinage {
	
private :
	Selecteur4 pbl2 ;
	Interrupteur grandDebit ;
	Selecteur3 fpb ;
	Selecteur3 freinDirect ;
	
public :

	/* Constructeur */
	
	Freinage(Selecteur4 pPbl2, Interrupteur pGrandDebit, Selecteur3 pFpb, Selecteur3 pFreinDirect) {
		pbl2 = pPbl2 ;
		grandDebit = pGrandDebit ;
		fpb = pFpb ;
		freinDirect = pFreinDirect ;
	}
	
	/* Méthodes */
	
	void update(float* ptrCP, float* ptrRE, float* ptrCG, float* ptrCF1, float* ptrCF2, boolean compresseurActif) {
		// L'alimentation de la CP par le compresseur est prioritaire sur sa vidange par le freinage
	}
};



#endif