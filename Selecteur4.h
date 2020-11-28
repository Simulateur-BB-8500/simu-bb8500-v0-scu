/*
 * Selecteur4.h
 *
 * Created: 28/03/2016
 * Author: Ludovic
 */

#include "Pin.h"

#ifndef SELECTEUR4_H
#define SELECTEUR4_H

// Tension moyenne entre les 4 états
#define s4Seuil1 0.55
#define s4Seuil2 1.65
#define s4Seuil3 2.75

// Delais de filtrage de états (ms)
#define filtrageS4 1000

class Selecteur4 {
	
private :
	Pin pin ; // On considère que les trois interrupteurs sont non-inverseurs
	boolean neutre_ac ;
	boolean neutre_pr ;
	uint32_t t_neutre ;
	boolean p1_ac ;
	boolean p1_pr ;
	uint32_t t_p1 ;
	boolean p2_ac ;
	boolean p2_pr ;
	uint32_t t_p2 ;
	boolean p3_ac ;
	boolean p3_pr ;
	uint32_t t_p3 ;
	
	
public :
	
	/* Constructeurs */
	
	// Constructeur sans argument
	Selecteur4() {
		pin.setPin(0, E, 0) ;
		neutre_ac = 0 ;
		neutre_pr = 0 ;
		t_neutre = 0 ;
		p1_ac = 0 ;
		p1_pr = 0 ;
		t_p1 = 0 ;
		p2_ac = 0 ;
		p2_pr = 0 ;
		t_p2 = 0 ;
		p3_ac = 0 ;
		p3_pr = 0 ;
		t_p3 = 0 ;
	}
	
	// Constructeur de recopie
	Selecteur4(const Selecteur4& modele) {
		pin = modele.pin ;
		neutre_ac = modele.neutre_ac ;
		neutre_pr = modele.neutre_pr ;
		t_neutre = modele.t_neutre ;
		p1_ac = modele.p1_ac ;
		p1_pr = modele.p1_pr ;
		t_p1 = modele.t_p1 ;
		p2_ac = modele.p2_ac ;
		p2_pr = modele.p2_pr ;
		t_p2 = modele.t_p2;
		p3_ac = modele.p3_ac ;
		p3_pr = modele.p3_pr ;
		t_p3 = modele.t_p3 ;	
	}
	
	// Constructeur avec arguments
	Selecteur4(uint32_t pNum) {
		pin.setPin(pNum, E, 0) ;
		neutre_ac = 0 ;
		neutre_pr = 0 ;
		t_neutre = 0 ;
		p1_ac = 0 ;
		p1_pr = 0 ;
		t_p1 = 0 ;
		p2_ac = 0 ;
		p2_pr = 0 ;
		t_p2 = 0 ;
		p3_ac = 0 ;
		p3_pr = 0 ;
		t_p3 = 0 ;
	}
	
	/* Méthodes */
	
	// Initialisation du sélecteur
	void init() {
		pinMode(pin.getNumPin(), INPUT) ;
	}
	
	// Retourne true si le sélecteur est sur neutre, false sinon
	boolean Neutre() {
		boolean resultat ;
		if (pin.read() < s4Seuil1) {
			neutre_ac = true ;
		}
		else {
			neutre_ac = false ;
		}
		if (neutre_pr == false) {
			t_neutre = millis() ;
		}
		if ((neutre_ac == true) && (millis() > t_neutre+filtrageS4)) {
			resultat = true ;
		}
		else {
			resultat = false ;
		}
		neutre_pr = neutre_ac ;
		return resultat ;
	}
	
	// Retourne true si le sélecteur est sur la position 1, false sinon
	boolean P1() {
		boolean resultat ;
		if ((pin.read() >= s4Seuil1) && (pin.read() < s4Seuil2)) {
			p1_ac = true ;
		}
		else {
			p1_ac = false ;
		}
		if (p1_pr == false) {
			t_p1 = millis() ;
		}
		if ((p1_ac == true) && (millis() > t_p1+filtrageS4)) {
			resultat = true ;
		}
		else {
			resultat = false ;
		}
		p1_pr = p1_ac ;
		return resultat ;
	}
	
	// Retourne true si le sélecteur est sur la position 2, false sinon
	boolean P2() {
		boolean resultat ;
		if ((pin.read() >= s4Seuil2) && (pin.read() < s4Seuil3)) {
			p2_ac = true ;
		}
		else {
			p2_ac = false ;
		}
		if (p2_pr == false) {
			t_p2 = millis() ;
		}
		if ((p2_ac == true) && (millis() > t_p2+filtrageS4)) {
			resultat = true ;
		}
		else {
			resultat = false ;
		}
		p2_pr = p2_ac ;
		return resultat ;
	}
	
	// Retourne true si le sélecteur est sur la position 3, false sinon
	boolean P3() {
		boolean resultat ;
		if (pin.read() >= s4Seuil3) {
			p3_ac = true ;
		}
		else {
			p3_ac = false ;
		}
		if (p3_pr == false) {
			t_p3 = millis() ;
		}
		if ((p3_ac == true) && (millis() > t_p3+filtrageS4)) {
			resultat = true ;
		}
		else {
			resultat = false ;
		}
		p3_pr = p3_ac ;
		return resultat ;
	}
} ;

#endif