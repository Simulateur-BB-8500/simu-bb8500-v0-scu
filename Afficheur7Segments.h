/*
 * Afficheur7Segments.h
 *
 * Created: 19/04/2016
 * Author: Ludovic
 */

#include "Lampe.h"

#ifndef AFFICHEUR7SEGMENTS_H
#define AFFICHEUR7SEGMENTS_H

// Délai de multuplexage temporel des afficheurs 7 segments (ms)
#define MUX_AFF 3

class Afficheur7Segments {
	
private :
	// Pin de commande
	Pin commande ;
	// Segments
	Lampe segmentA ;
	Lampe segmentB ;
	Lampe segmentC ;
	Lampe segmentD ;
	Lampe segmentE ;
	Lampe segmentF ;
	Lampe segmentG ;
	
public :
	
	/* Constructeurs */
	
	// Constructeur sans argument
	Afficheur7Segments() {}
	
	// Constructeur avec arguments
	Afficheur7Segments(uint32_t num, Lampe pSegmentA, Lampe pSegmentB, Lampe pSegmentC, Lampe pSegmentD, Lampe pSegmentE, Lampe pSegmentF, Lampe pSegmentG) {
		commande.setPin(num, S, 0) ;
		segmentA = pSegmentA ;
		segmentB = pSegmentB ;
		segmentC = pSegmentC ;
		segmentD = pSegmentD ;
		segmentE = pSegmentE ;
		segmentF = pSegmentF ;
		segmentG = pSegmentG ;
	}
	
	/* Méthodes */
	
	// Initialisation de l'afficheur
	void init() {
		pinMode(commande.getNumPin(), OUTPUT) ;
		commande.write(GND) ;
		segmentA.init() ;
		segmentB.init() ;
		segmentC.init() ;
		segmentD.init() ;
		segmentE.init() ;
		segmentF.init() ;
		segmentG.init() ;
	}
	
	// Active l'afficheur
	void allumer() {
		commande.write(TENSION_REF) ;
	}
	
	// Eteint l'afficheur
	void eteindre() {
		commande.write(GND) ;
	}
	
	// Caractères du KVB
	void aff_P(boolean mux) {
		allumer() ;
		segmentA.allumer() ;
		segmentB.allumer() ;
		segmentC.eteindre() ;
		segmentD.eteindre() ;
		segmentE.allumer() ;
		segmentF.allumer() ;
		segmentG.allumer() ;
		if (mux == true) {
			delay(MUX_AFF) ;
			eteindre() ;
		}
	}
	
	void aff_A(boolean mux) {
		allumer() ;
		segmentA.allumer() ;
		segmentB.allumer() ;
		segmentC.allumer() ;
		segmentD.eteindre() ;
		segmentE.allumer() ;
		segmentF.allumer() ;
		segmentG.allumer() ;
		if (mux == true) {
			delay(MUX_AFF) ;
			eteindre() ;
		}
	}
	
	void aff_4(boolean mux) {
		allumer() ;
		segmentA.eteindre() ;
		segmentB.allumer() ;
		segmentC.allumer() ;
		segmentD.eteindre() ;
		segmentE.eteindre() ;
		segmentF.allumer() ;
		segmentG.allumer() ;
		if (mux == true) {
			delay(MUX_AFF) ;
			eteindre() ;
		}
	}
	
	void aff_0(boolean mux) {
		allumer() ;
		segmentA.allumer() ;
		segmentB.allumer() ;
		segmentC.allumer() ;
		segmentD.allumer() ;
		segmentE.allumer() ;
		segmentF.allumer() ;
		segmentG.eteindre() ;
		if (mux == true) {
			delay(MUX_AFF) ;
			eteindre() ;
		}
	}
	
	void aff_U(boolean mux) {
		allumer() ;
		segmentA.eteindre() ;
		segmentB.allumer() ;
		segmentC.allumer() ;
		segmentD.allumer() ;
		segmentE.allumer() ;
		segmentF.allumer() ;
		segmentG.eteindre() ;
		if (mux == true) {
			delay(MUX_AFF) ;
			eteindre() ;
		}
	}
	
	void aff_C(boolean mux) {
		allumer() ;
		segmentA.allumer() ;
		segmentB.eteindre() ;
		segmentC.eteindre() ;
		segmentD.allumer() ;
		segmentE.allumer() ;
		segmentF.allumer() ;
		segmentG.eteindre() ;
		if (mux == true) {
			delay(MUX_AFF) ;
			eteindre() ;
		}
	}
	
	void aff_5(boolean mux) {
		allumer() ;
		segmentA.allumer() ;
		segmentB.eteindre() ;
		segmentC.allumer() ;
		segmentD.allumer() ;
		segmentE.eteindre() ;
		segmentF.allumer() ;
		segmentG.allumer() ;
		if (mux == true) {
			delay(MUX_AFF) ;
			eteindre() ;
		}
	}
	
	void aff_1(boolean mux) {
		allumer() ;
		segmentA.eteindre() ;
		segmentB.allumer() ;
		segmentC.allumer() ;
		segmentD.eteindre() ;
		segmentE.eteindre() ;
		segmentF.eteindre() ;
		segmentG.eteindre() ;
		if (mux == true) {
			delay(MUX_AFF) ;
			eteindre() ;
		}
	}
	
	void aff_2(boolean mux) {
		allumer() ;
		segmentA.allumer() ;
		segmentB.allumer() ;
		segmentC.eteindre() ;
		segmentD.allumer() ;
		segmentE.allumer() ;
		segmentF.eteindre() ;
		segmentG.allumer() ;
		if (mux == true) {
			delay(MUX_AFF) ;
			eteindre() ;
		}
	}
	
	void aff_8(boolean mux) {
		allumer() ;
		segmentA.allumer() ;
		segmentB.allumer() ;
		segmentC.allumer() ;
		segmentD.allumer() ;
		segmentE.allumer() ;
		segmentF.allumer() ;
		segmentG.allumer() ;
		if (mux == true) {
			delay(MUX_AFF) ;
			eteindre() ;
		}
	}
	
	void aff_6(boolean mux) {
		allumer() ;
		segmentA.allumer() ;
		segmentB.eteindre() ;
		segmentC.allumer() ;
		segmentD.allumer() ;
		segmentE.allumer() ;
		segmentF.allumer() ;
		segmentG.allumer() ;
		if (mux == true) {
			delay(MUX_AFF) ;
			eteindre() ;
		}
	}
	
	void aff_tiret(boolean mux) {
		allumer() ;
		segmentA.eteindre() ;
		segmentB.eteindre() ;
		segmentC.eteindre() ;
		segmentD.eteindre() ;
		segmentE.eteindre() ;
		segmentF.eteindre() ;
		segmentG.allumer() ;
		if (mux == true) {
			delay(MUX_AFF) ;
			eteindre() ;
		}
	}
	
	void aff_b(boolean mux) {
		allumer() ;
		segmentA.eteindre() ;
		segmentB.eteindre() ;
		segmentC.allumer() ;
		segmentD.allumer() ;
		segmentE.allumer() ;
		segmentF.allumer() ;
		segmentG.allumer() ;
		if (mux == true) {
			delay(MUX_AFF) ;
			eteindre() ;
		}
	}
} ;

#endif