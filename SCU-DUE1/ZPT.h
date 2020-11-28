/*
 * ZPT.h
 *
 * Created: 17/04/2016
 * Author: Ludovic
 */ 

#ifndef PANTOGRAPHE_H
#define PANTOGRAPHE_H

#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Selecteur4.h"
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Instructions.h"

// Pression CP minimale nécessaire pour monter les pantos
#define ZPT_PRESSION_MIN 5.0

class ZPT {
	
private :
	Pin voltmetreLigne ;
	Interrupteur reservoirSecours ;
	Selecteur4 zpt ;
	int state ; // -1 = levage panto impossible
				// 0 = pantos baissé 
				// 1 = panto arrière
				// 2 = pantos avant et arrière
				// 3 = panto avant
	
public :

	/* Constructeur */
	
	ZPT(uint32_t pNum, Interrupteur pReservoirSecours, Selecteur4 pZpt) {
		voltmetreLigne.setPin(pNum, S, 0) ;
		reservoirSecours = pReservoirSecours ;
		zpt = pZpt ;
		state = 0 ;
	}
	
	/* Méthodes */
	
	void init() {
		pinMode(voltmetreLigne.getNumPin(), OUTPUT) ;
		reservoirSecours.init() ;
		zpt.init() ;
	}
	
	boolean pantosBaisses() {
		return zpt.Neutre() ;
	}
	
	boolean pantoAR() {
		return zpt.P1() ;
	}
	
	boolean pantoARAV() {
		return zpt.P2() ;
	}
	
	boolean pantoAV() {
		return zpt.P3() ;
	}
	
	void update(boolean blDev, float pressionCP) {
		// On peut monter les pantos uniquement si la BL est déverouillée et qu'il y a suffisamment d'air (CP ou réservoir de secours)
		if ((blDev == true) && ((pressionCP >= ZPT_PRESSION_MIN) || (reservoirSecours.marche()))) {
			if (pantosBaisses()) {
				switch (state) {
				case 1 :
					// SerialUSB.println("Abaissement panto arriere") ;
					break ;
				case 2 :
					// SerialUSB.println("Abaissement panto avant") ;
					// SerialUSB.println("Abaissement panto arriere") ;
					break ;
				case 3 :
					// SerialUSB.println("Levage panto arriere") ;
					// SerialUSB.println("Abaissement panto avant") ;
					// SerialUSB.println("Abaissement panto arriere") ;
					break ;
				}
				voltmetreLigne.write(TENSION_REF) ;
				state = 0 ;
			}
			else {
				voltmetreLigne.write(GND) ;
				if (pantoAR()) {
					switch (state) {
					case -1 :
						// SerialUSB.println("Levage panto arriere") ;
						break ;
					case 0 :
						// SerialUSB.println("Levage panto arriere") ;
						break ;
					case 2 :
						// SerialUSB.println("Abaissement panto avant") ;
						break ;
					case 3 :
						// SerialUSB.println("Levage panto arriere") ;
						// SerialUSB.println("Abaissement panto avant") ;
						break ;
					}
					state = 1 ;
				}
				if (pantoARAV()) {
					switch (state) {
					case -1 :
						// SerialUSB.println("Levage panto arriere") ;
						// SerialUSB.println("Levage panto avant") ;
						break ;
					case 0 :
						// SerialUSB.println("Levage panto arriere") ;
						// SerialUSB.println("Levage panto avant") ;
						break ;
					case 1 :
						// SerialUSB.println("Levage panto avant") ;
						break ;
					case 3 :
						// SerialUSB.println("Levage panto arriere") ;
						break ;
					}
					state = 2 ;
				}
				if (pantoAV()) {
					switch (state) {
					case -1 :
						// SerialUSB.println("Levage panto avant") ;
						break ;
					case 0 :
						// SerialUSB.println("Levage panto arriere") ;
						// SerialUSB.println("Levage panto avant") ;
						// SerialUSB.println("Abaissement panto arriere") ;
						break ;
					case 1 :
						// SerialUSB.println("Levage panto avant") ;
						// SerialUSB.println("Abaissement panto arriere") ;
						break ;
					case 2 :
						// SerialUSB.println("Abaissement panto arriere") ;
						break ;
					}
					state = 3 ;
				}
			}
		}
		else {
			voltmetreLigne.write(TENSION_REF) ;
			if (state != -1) {
				// SerialUSB.println("Abaissement des pantos") ;
			}
			state = -1 ;
		}
	}
} ;

#endif