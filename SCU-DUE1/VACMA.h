/*
 * VACMA.h
 *
 * Created: 16/04/2016
 * Author: Ludovic
 */

#ifndef VACMA_H
#define VACMA_H

#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Sonnerie.h"
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Interrupteur.h"

#define T_RELACHEMENT 3000 // Temps de relâchement autorisé avant sonnerie (ms)
#define T_MAINTIEN 55000 // Temps de maintien autorisé avant sonnerie (ms)
#define T_SONNERIE 5000 // Durée des sonneries avant freinage d'urgence (ms)


class VACMA {
	
private :
	Interrupteur essaiVa ;
	Interrupteur cerclot ;
	Sonnerie sonRelachement ;
	Sonnerie sonMaintien ;
	boolean state_ac ; // =1 si cerclot maintenu, 0 sinon
	boolean state_pr ;
	boolean essaiVa_ac ;
	boolean essaiVa_pr ;
	uint32_t debutRelachement ;
	uint32_t debutMaintien ;
	
public :

	/* Constructeur */
	
	VACMA(Interrupteur pEssaiVa, Interrupteur pCerclot, Sonnerie pSonRelachement, Sonnerie pSonMaintien) {
		essaiVa = pEssaiVa ;
		cerclot = pCerclot ;
		sonRelachement = pSonRelachement ;
		sonMaintien = pSonMaintien ;
		debutMaintien = 0 ;
		debutRelachement = 0 ;
	}
	
	/* Méthodes */
	
	void init() {
		essaiVa.init() ;
		cerclot.init() ;
		sonRelachement.init() ;
		sonMaintien.init() ;
	}
	
	void eteindre() {
		sonRelachement.eteindre() ;
		sonMaintien.eteindre() ;
	}
	
	void va(boolean* ptrFu) {
		// Chronomètre de maintien d'appui
		if (cerclot.marche()) {
			state_ac = true ;
			sonRelachement.eteindre() ;
			if ((state_pr == false) || (essaiVa_pr == false)) {
				debutMaintien = millis() ;
			}
			if (millis() > debutMaintien+T_MAINTIEN+T_SONNERIE) {
				// Expiration sonnerie -> freinage d'urgence
				sonMaintien.eteindre() ;
				(*ptrFu) = true ;
			}
			else {
				if (millis() > debutMaintien+T_MAINTIEN) {
					// VA maintenue trop longtemps -> Son maintien d'appui
					sonMaintien.allumer() ;
				}
			}
		}
		// Chronomètre de relâchement
		else {
			state_ac = false ;
			sonMaintien.eteindre() ;
			if ((state_pr == true) || (essaiVa_pr == false)) {
				debutRelachement = millis() ;
			}
			if (millis() > debutRelachement+T_RELACHEMENT+T_SONNERIE) {
				// Expiration sonnerie -> freinage d'urgence
				sonRelachement.eteindre() ;
				(*ptrFu) = true ;
			}
			else {
				if (millis() > debutRelachement+T_RELACHEMENT) {
					// VA relâchée trop longtemps -> Son relâchement
					sonRelachement.allumer() ;
				}
			}
		}
		state_pr = state_ac ;
	}
	
	void update(boolean* ptrFu, char vitesse) {
		if (essaiVa.marche()) {
			essaiVa_ac = true ;
		}
		else {
			essaiVa_ac = false ;
		}
		if ((vitesse != 0) || (essaiVa_ac == true)) {
			va(ptrFu) ;
		}
		else {
			eteindre() ;
		}
		essaiVa_pr = essaiVa_ac ;
	}
} ;

#endif