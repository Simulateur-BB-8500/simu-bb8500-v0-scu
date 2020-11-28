/*
 * Tachro.h
 *
 * Created: 26/06/2016
 * Author: Ludovic Lesur
 *
 * Avancement : Classe entièrement codée, commentée et fonctionnelle (testée sur le Tachro le 30/01/2017).
 */ 


#ifndef TACHRO_H
#define TACHRO_H


// Include
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Pin.h"


// Etats de la MAE
#define ETAT_TACHRO_ETEINT 0
#define ETAT_TACHRO_PHASE1 1
#define ETAT_TACHRO_PHASE2 2
#define ETAT_TACHRO_PHASE3 3
#define ETAT_TACHRO_PHASE4 4
#define ETAT_TACHRO_PHASE5 5
#define ETAT_TACHRO_PHASE6 6

// Coefficients de l'équation affine du Tachro
#define TACHRO_A 10700000.0
#define TACHRO_B -0.4667

// Vitesse minimale (km/h) en dessous de laquelle le Tachro est desactivé (car non suffisamment précis).
#define TACHRO_VITESSE_MIN 5


class Tachro {
	
private :

	// Phase A du moteur triphasé
	Pin inhA ;
	Pin pwmA ;
	// Phase B du moteur triphasé
	Pin inhB ;
	Pin pwmB ;
	// Phase C du moteur triphasé
	Pin inhC ;
	Pin pwmC ;

	// MAE
	int etat ;
	uint32_t delai ; // Durée entre deux changements de phase (= période du signal / 6).
	uint32_t tempoEtat ;
	

	/** 
	 * APPLIQUE A UNE PHASE LE SIGNAL PWM DE CONTROLE (ACTIVATION DU IR2104).
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void phaseOn(Pin inh) {
		inh.write(TENSION_REF) ;
	}


	/** 
	 * MET UNE PHASE EN HAUTE-IMPEDANCE (INHIBATION DU IR2104).
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void phaseOff(Pin inh) {
		inh.write(GND) ;
	}
	
public :

	/** 
	 * CONSTRUCTEUR DE LA CLASSE TACHRO.
	 *
	 * @param pNumInhA	Numéro de pin de la DUE.2 connecté à l'entrée INH du IR2104 contrôlant la phase A du moteur.
	 * @param pNumPwmA	Numéro de pin de la DUE.2 connecté à l'entrée PWM du IR2104 contrôlant la phase A du moteur.
	 * @param pNumInhB	Numéro de pin de la DUE.2 connecté à l'entrée INH du IR2104 contrôlant la phase B du moteur.
	 * @param pNumPwmB	Numéro de pin de la DUE.2 connecté à l'entrée PWM du IR2104 contrôlant la phase B du moteur.
	 * @param pNumInhC	Numéro de pin de la DUE.2 connecté à l'entrée INH du IR2104 contrôlant la phase C du moteur.
	 * @param pNumPwmC	Numéro de pin de la DUE.2 connecté à l'entrée PWM du IR2104 contrôlant la phase C du moteur.
	 * @return	Aucun.
	 */
	Tachro(uint32_t pNumInhA, uint32_t pNumPwmA, uint32_t pNumInhB, uint32_t pNumPwmB, uint32_t pNumInhC, uint32_t pNumPwmC) {
		// Phase A du moteur triphasé
		inhA.setPin(pNumInhA, S, 0) ;
		pwmA.setPin(pNumPwmA, S, 0) ;
		// Phase B du moteur triphasé
		inhB.setPin(pNumInhB, S, 0) ;
		pwmB.setPin(pNumPwmB, S, 0) ;
		// Phase C du moteur triphasé
		inhC.setPin(pNumInhC, S, 0) ;
		pwmC.setPin(pNumPwmC, S, 0) ;
		// MAE
		etat = ETAT_TACHRO_ETEINT ;
		delai = 0 ;
		tempoEtat = 0 ;
	}
	
	
	/** 
	 * INITIALISE LES PINS DE COMMANDE DU MOTEUR TRIPHASE DU TACHRO.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void init() {
		pinMode(inhA.getNumPin(), OUTPUT) ;
		inhA.write(GND) ;
		pwmA.write(GND) ;
		pinMode(inhB.getNumPin(), OUTPUT) ;
		inhB.write(GND) ;
		pwmB.write(GND) ;
		pinMode(inhC.getNumPin(), OUTPUT) ;
		inhC.write(GND) ;
		pwmC.write(GND) ;
	}
	

	/** 
	 * DETERMINE L'ETAT DE LA MACHINE A ETATS DU TACHRO.
	 *
	 * @param vitesse	Vitesse actuelle de la locomotive en km/h.
	 * @return			Aucun.
	 */
	void calculerEtat(int vitesse) {

		// Calcul du délai entre chaque changement de séquence
		delai = floor((TACHRO_A)/(6.0*((float)vitesse+TACHRO_B))) ;

		switch (etat) {

		case ETAT_TACHRO_ETEINT :
			if (vitesse >= TACHRO_VITESSE_MIN) {
				etat = ETAT_TACHRO_PHASE1 ;
				tempoEtat = micros() ; // Déclenchement timer ETAT_PHASE1.
			}
			break ;

		case ETAT_TACHRO_PHASE1 :
			if (vitesse < TACHRO_VITESSE_MIN) {
				etat = ETAT_TACHRO_ETEINT ;
			}
			else {
				if (micros() > tempoEtat + delai) {
					etat = ETAT_TACHRO_PHASE2 ;
					tempoEtat = micros() ; // Déclenchement timer ETAT_PHASE2.
				}
			}
			break ;

		case ETAT_TACHRO_PHASE2 :
			if (vitesse < TACHRO_VITESSE_MIN) {
				etat = ETAT_TACHRO_ETEINT ;
			}
			else {
				if (micros() > tempoEtat + delai) {
					etat = ETAT_TACHRO_PHASE3 ;
					tempoEtat = micros() ; // Déclenchement timer ETAT_PHASE3.
				}
			}
			break ;

		case ETAT_TACHRO_PHASE3 :
			if (vitesse < TACHRO_VITESSE_MIN) {
				etat = ETAT_TACHRO_ETEINT ;
			}
			else {
				if (micros() > tempoEtat + delai) {
					etat = ETAT_TACHRO_PHASE4 ;
					tempoEtat = micros() ; // Déclenchement timer ETAT_PHASE4.
				}
			}
			break ;

		case ETAT_TACHRO_PHASE4 :
			if (vitesse < TACHRO_VITESSE_MIN) {
				etat = ETAT_TACHRO_ETEINT ;
			}
			else {
				if (micros() > tempoEtat + delai) {
					etat = ETAT_TACHRO_PHASE5 ;
					tempoEtat = micros() ; // Déclenchement timer ETAT_PHASE5.
				}
			}
			break ;

		case ETAT_TACHRO_PHASE5 :
			if (vitesse < TACHRO_VITESSE_MIN) {
				etat = ETAT_TACHRO_ETEINT ;
			}
			else {
				if (micros() > tempoEtat + delai) {
					etat = ETAT_TACHRO_PHASE6 ;
					tempoEtat = micros() ; // Déclenchement timer ETAT_PHASE6.
				}
			}
			break ;

		case ETAT_TACHRO_PHASE6 :
			if (vitesse < TACHRO_VITESSE_MIN) {
				etat = ETAT_TACHRO_ETEINT ;
			}
			else {
				if (micros() > tempoEtat + delai) {
					etat = ETAT_TACHRO_PHASE1 ;
					tempoEtat = micros() ; // Déclenchement timer ETAT_PHASE1.
				}
			}
			break ;
		}
	}


	/** 
	 * COMMANDE LE CIRCUIT IR2104 EN FONCTION DE L'ETAT ACTUEL DE LA MACHINE A ETATS.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void calculerActions() {

		switch(etat) {

		case ETAT_TACHRO_ETEINT :
			phaseOff(inhA) ;
			phaseOff(inhB) ;
			phaseOff(inhC) ;
			pwmA.write(GND) ;
			pwmB.write(GND) ;
			pwmC.write(GND) ;
			break ;

		case ETAT_TACHRO_PHASE1 :
			phaseOn(inhA) ;
			phaseOn(inhB) ;
			phaseOff(inhC) ;
			pwmA.write(TENSION_REF) ;
			pwmB.write(GND) ;
			break ;

		case ETAT_TACHRO_PHASE2 :
			phaseOn(inhA) ;
			phaseOff(inhB) ;
			phaseOn(inhC) ;
			pwmA.write(TENSION_REF) ;
			pwmC.write(GND) ;
			break ;

		case ETAT_TACHRO_PHASE3 :
			phaseOff(inhA) ;
			phaseOn(inhB) ;
			phaseOn(inhC) ;
			pwmB.write(TENSION_REF) ;
			pwmC.write(GND) ;
			break ;

		case ETAT_TACHRO_PHASE4 :
			phaseOn(inhA) ;
			phaseOn(inhB) ;
			phaseOff(inhC) ;
			pwmB.write(TENSION_REF) ;
			pwmA.write(GND) ;
			break ;

		case ETAT_TACHRO_PHASE5 :
			phaseOn(inhA) ;
			phaseOff(inhB) ;
			phaseOn(inhC) ;
			pwmC.write(TENSION_REF) ;
			pwmA.write(GND) ;
			break ;

		case ETAT_TACHRO_PHASE6 :
			phaseOff(inhA) ;
			phaseOn(inhB) ;
			phaseOn(inhC) ;
			pwmC.write(TENSION_REF) ;
			pwmB.write(GND) ;
			break ;
		}
	}


	/** 
	 * REINITIALISE LA TEMPO D'ETAT LORS D'UN OVERFLOW DE LA FONCTION MICROS().
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void overflowMicros() {
		if (micros() < 10000) {
			tempoEtat = micros() ;
		}
	}


	/** 
	 * MAIN FUNCTION DU TACHRO.
	 *
	 * @param vitesse	Vitesse courante de la locomotive en km/h.
	 * @return			Aucun.
	 */
	void run(int vitesse) {
		calculerEtat(vitesse) ;
		calculerActions() ;
		overflowMicros() ;
	}
} ;


#endif