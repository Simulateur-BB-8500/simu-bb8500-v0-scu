/*
 * Compresseur.h
 *
 * Created: 18/04/2016
 * Author: Ludovic
 */ 

#ifndef COMPRESSEUR_H
#define COMPRESSEUR_H

#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Interrupteur.h"
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Instructions.h"

class Compresseur {
	
private :
	Interrupteur zca ;
	Interrupteur zcd ;
	char state_ac ;
	char state_pr ;
	float memCP ;
	uint32_t t_CP ;
	
public :
	
	/* Constructeur */
	
	Compresseur(Interrupteur pZca, Interrupteur pZcd) {
		zca = pZca ;
		zcd = pZcd ;
		state_ac = 0 ;
		state_pr = 0 ;
		memCP = 0.0 ;
		t_CP = 0 ;
	}
	
	/* Méthodes */
	
	void init() {
		zca.init() ;
		zcd.init() ;
	}
	
	// Codage de la machine à états
	void machineEtats(boolean djEnclenche, float pressionCP) {
		// Polling nécessaire à l'actualisation des interrupteurs
		zcd.marche() ;
		zca.marche() ;
		// Machine à états
		switch (state_pr) {
		case 0 :
			//SerialUSB.println("Etat0") ;
			SerialUSB.write(I_etatComp0) ;
			if (djEnclenche) {
				if (zcd.marche()) {
					state_ac = 3 ;
				}
				else {
					if (zca.marche()) {
						if (pressionCP >= CP_REG_INF) {
							state_ac = 1 ;
						}
						else {
							state_ac = 2 ;
						}
					}
				}
			}
			else {
				state_ac = 0 ;
			}
			break ;
		case 1 :
			//SerialUSB.println("Etat1") ;
			SerialUSB.write(I_etatComp1) ;
			if (djEnclenche) {
				if (zca.arret()) {
					state_ac = 0 ;
				}
				else {
					if (zcd.marche()) {
						state_ac = 4 ;
					}
					else {
						if (pressionCP <= CP_REG_INF) {
							state_ac = 2 ;
						}
					}
				}
			}
			else {
				state_ac = 0 ;
			}
			break ;
		case 2 :
			//SerialUSB.println("Etat2") ;
			SerialUSB.write(I_etatComp2) ;
			if (djEnclenche) {
				if (zca.arret()) {
					state_ac = 0 ;
				}
				else {
					if (zcd.marche()) {
						state_ac = 4 ;
					}
					else {
						if (pressionCP >= CP_REG_SUP) {
							state_ac = 1 ;
						}
					}
				}
			}
			else {
				state_ac = 0 ;
			}
			break ;
		case 3 :
			//SerialUSB.println("Etat3") ;
			SerialUSB.write(I_etatComp3) ;
			if (djEnclenche) {
				if (zcd.arret()) {
					state_ac = 0 ;
				}
				else {
					if (zca.marche()) {
						state_ac = 4 ;
					}
				}
			}
			else {
				state_ac = 0 ;
			}
			break ;
		case 4 :
			//SerialUSB.println("Etat4") ;
			SerialUSB.write(I_etatComp4) ;
			if (djEnclenche) {
				if (zca.arret()) {
					state_ac = 3 ;
				}
				else {
					if (zcd.arret()) {
						if (pressionCP >= CP_REG_INF) {
							state_ac = 1 ;
						}
						else {
							state_ac = 2 ;
						}
					}
				}
			}
			else {
				state_ac = 0 ;
			}
			break ;
		default :
			//SerialUSB.println("default") ;
			SerialUSB.write(I_etatComp0) ;
			state_ac = 0 ;
			break ;
		}
		// Lors du changement d'état, on actualise l'instant initial et la pression CP initiale
		if (state_ac != state_pr) {
			t_CP = millis() ;
			memCP = pressionCP ;
		}
		state_pr = state_ac ;
	}
	
	void calculerCP(float* ptrPressionCP) {
		if ((*ptrPressionCP) < CP_MAX) {
			if ((state_ac == 2) || (state_ac == 3) || (state_ac == 4)) {
				(*ptrPressionCP) = memCP +	VITESSE_ALIM_CP*(float(millis())-float(t_CP)) ;
			}
		}
	}
	
	
	void sendCP(float pressionCP) {
		// Conversion pression -> instruction
		int data = floor(OFFSET_CODAGE_CP+10.0*pressionCP) ;
		//SerialUSB.println(pressionCP) ;
		SerialUSB.write(data) ;
	}
	
	void update(boolean* ptrCompresseurActif, boolean djEnclenche, float* ptrPressionCP) {
		machineEtats(djEnclenche, (*ptrPressionCP)) ;
		calculerCP(ptrPressionCP) ;
		sendCP(*ptrPressionCP) ;
		if ((state_ac == 0) || (state_ac == 1)) {
			*ptrCompresseurActif = false ;
		}
		else {
			*ptrCompresseurActif = true ;
		}
	}
} ;


#endif