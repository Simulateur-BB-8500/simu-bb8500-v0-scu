/*
 * ManipTraction.h
 *
 * Created: 16/04/2016
 * Author: Ludovic
 */

#ifndef MANIPTRACTION_H
#define MANIPTRACTION_H

#include "Graduateur.h"
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Interrupteur.h"

class ManipTraction {
	
private :
	Graduateur graduateur ;
	Interrupteur mpTr0 ; // Traction 0
	Interrupteur mpTrPlus ; // Traction +
	Interrupteur mpTrMoins ; // Traction -
	Interrupteur mpPr ; // Progression rapide
	Interrupteur mpFrPlus ; // Freinage +
	Interrupteur mpFrMoins ; // Freinage moins
	Interrupteur mpFr ; // Freinage rapide
	Interrupteur mpPrep ; // Préparation freinage rhéostatique
	
public :

	/* Constructeur */
	
	ManipTraction(Graduateur pGraduateur, Interrupteur pMpTr0, Interrupteur pMpTrPlus, Interrupteur pMpTrMoins, Interrupteur pMpPr, Interrupteur pMpFrPlus, Interrupteur pMpFrMoins, Interrupteur pMpFr, Interrupteur pMpPrep) {
		graduateur = pGraduateur ;
		mpTr0 = pMpTr0 ;
		mpTrPlus = pMpTrPlus ;
		mpTrMoins = pMpTrMoins ;
		mpPr = pMpPr ;
		mpFrPlus = pMpFrPlus ;
		mpFrMoins = pMpFrMoins ;
		mpFr = pMpFr ;
		mpPrep = pMpPrep ;
		// Graduateur
		
	}
	
	/* Méthodes */
	
	void init() {
		mpTr0.init() ;
		mpTrPlus.init() ;
		mpTrMoins.init() ;
		mpPr.init() ;
		mpFrPlus.init() ;
		mpFrMoins.init() ;
		mpFr.init() ;
		mpPrep.init() ;
	}
	
	void update(int* ptrCran, boolean* ptrRheostatique) {
		(*ptrRheostatique) = false ; // Placé à "false" par défaut pour factoriser du code
		// Le code des positions monostables doit être placé en premier
		
		// Traction +
		if (mpTrPlus.marche()) {
			graduateur.progression(ptrCran) ;
		}
		else {
			graduateur.resetProg() ;
		}
		
		// Traction -
		if (mpTrMoins.marche()) {
			graduateur.regression(ptrCran) ;
		}
		else {
			graduateur.resetReg() ;
		}
		
		// Freinage rhéostatique +
		
		// Freinage rhéostatique -
		
		// Manip à 0 = régression rapide (0)
		if (mpTr0.marche()) {
			graduateur.regressionRapide(ptrCran) ;
		}
		else {
			graduateur.resetRegRapide() ;
		}
		
		// Progression rapide (PR)
		if (mpPr.marche()) {
			graduateur.progressionRapide(ptrCran) ;
		}
		else {
			graduateur.resetProgRapide() ;
		}
		
		// Freinage rhéostatique rapide (FR)
		
		// Préparation au freinage (P)
		
		// Freinage +
		/*if (mpFrPlus.marche()) {
			(*ptrRheostatique) = true ;
			// Actualisation état
			mpTrPlus_ac = false ;
			mpTrMoins_ac = false ;
			mpFrPlus_ac = true ;
			mpFrMoins_ac = false ;
			if (mpFrPlus_pr == false) {
				graduateur.progression(ptrCran) ;
			}
		}
		else {
			mpFrPlus_ac = false ;
		}
		if (mpFrMoins.marche()) {
			(*ptrRheostatique) = true ;
			// Actualisation état
			mpTrPlus_ac = false ;
			mpTrMoins_ac = false ;
			mpFrPlus_ac = false ;
			mpFrMoins_ac = true ;
			if (mpFrMoins_pr == false) {
				graduateur.regression(ptrCran) ;
			}
		}
		else {
			mpFrMoins_ac = false ;
		}
		if (mpFr.marche()) {
			(*ptrRheostatique) = true ;
			// Actualisation état
			mpTrPlus_ac = false ;
			mpTrMoins_ac = false ;
			mpFrPlus_ac = false ;
			mpFrMoins_ac = false ;
			graduateur.progressionRapide(ptrCran) ;
		}
		if (mpPrep.marche()) {
			(*ptrRheostatique) = true ;
			// Actualisation état
			mpTrPlus_ac = false ;
			mpTrMoins_ac = false ;
			mpFrPlus_ac = false ;
			mpFrMoins_ac = false ;
			graduateur.preparation(ptrCran) ;
		}*/
		graduateur.majState() ;
		graduateur.majKeyboard() ;
	}
} ;

#endif