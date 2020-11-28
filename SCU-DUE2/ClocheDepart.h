/*
 * ClocheDepart.h
 *
 * Created: 23/12/2016
 * Author: Ludovic Lesur
 *
 * Avancement : Classe entièrement codée, commentée et fonctionnelle avec la cloche réelle (29/12/2016).
 */ 


#ifndef CLOCHEDEPART_H
#define CLOCHEDEPART_H


// Include
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Interrupteur.h"
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Sonnerie.h"


// Etats de la MAE
#define ETAT_CLOCHE_PRETE 0
#define ETAT_CLOCHE_DING1 1
#define ETAT_CLOCHE_ETEINDRE1 2
#define ETAT_CLOCHE_DING2 3
#define ETAT_CLOCHE_ETEINDRE2 4
#define ETAT_CLOCHE_TEMPO 5

// Durée d'une impulsion créant le ding de la cloche (ms)
#define DUREE_DING 100
// Durée entre les deux dings de la cloche (ms)
#define DUREE_ENTRE_DINGS 500
// Temporisation après activation (ms)
#define DUREE_TEMPO 60000


class ClocheDepart {

private :

	// ZCT
	Interrupteur zct ;

	// Cloche
	Sonnerie cloche ;

	// MAE
	int etat ;
	uint32_t tempoEtat ;
	boolean zct_ac ;
	boolean zct_pr ;

public :

	/** 
	 * CONSTRUCTEUR DE LA CLASSE CLOCHEDEPART.
	 *
	 * @param pZct		Interrupteur chef de train de type 'Interrupteur'.
	 * @param pCloche	Cloche départ de type 'Sonnerie'.
	 * @return			Aucun.
	 */
	ClocheDepart(Interrupteur pZct, Sonnerie pCloche) {
		zct = pZct ;
		cloche  = pCloche ;
		etat = ETAT_CLOCHE_PRETE ;
		tempoEtat = 0 ;
		zct_ac = false ;
		zct_pr = false ;
	}


	/** 
	 * INITIALISE L'INTERRUPTEUR ET LA CLOCHE DEPART.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void init() {
		zct.init() ;
		cloche.init() ;
	}


	/** 
	 * MET A JOUR L'ETAT DE L'INTERRUPTEUR.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void calculerEntrees() {
		zct_pr = zct_ac ;
		if (zct.marche()) {
			zct_ac = true ;
		}
		else {
			zct_ac = false ;
		}
	}


	/** 
	 * CALCULE L'ETAT DE LA MACHINE A ETAT DE LA CLOCHE DEPART.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void calculerEtat(int vitesse) {

		switch(etat) {

		case ETAT_CLOCHE_PRETE :
			if ((zct_ac == true) && (zct_pr == false) && (vitesse == 0)) {
				etat =	ETAT_CLOCHE_DING1 ;
				tempoEtat = millis() ; // Déclenchement timer ETAT_DING1.
			}
			break ;

		case ETAT_CLOCHE_DING1 :
			if (millis() > tempoEtat + DUREE_DING) {
				etat = ETAT_CLOCHE_ETEINDRE1 ;
				tempoEtat = millis() ; // Déclenchement timer ETAT_ETEINDRE1.
			}
			break ;

		case ETAT_CLOCHE_ETEINDRE1 :
			if (millis() > tempoEtat + (DUREE_ENTRE_DINGS-DUREE_DING)) {
				etat = ETAT_CLOCHE_DING2 ;
				tempoEtat = millis() ; // Déclenchement timer ETAT_DING2.
			}
			break ;

		case ETAT_CLOCHE_DING2 :
			if (millis() > tempoEtat + DUREE_DING) {
				etat = ETAT_CLOCHE_ETEINDRE2 ;
				tempoEtat = millis() ; // Déclenchement timer ETAT_ETEINDRE2.
			}
			break ;

		case ETAT_CLOCHE_ETEINDRE2 :
			if (millis() > tempoEtat + (DUREE_ENTRE_DINGS-DUREE_DING)) {
				etat = ETAT_CLOCHE_TEMPO ;
				tempoEtat = millis() ; // Déclenchement timer ETAT_TEMPO.
			}
			break ;

		case ETAT_CLOCHE_TEMPO :
			if (millis() > tempoEtat + (DUREE_TEMPO)) {
				etat = ETAT_CLOCHE_PRETE ;
			}
			break ;
		}
	}


	/** 
	 * FAIT RETENTIR LA CLOCHE EN FONCTION DE L'ETAT ACTUEL DE LA MACHINE A ETATS.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void calculerActions() {

		switch (etat) {

		case ETAT_CLOCHE_PRETE :
			cloche.eteindre() ;
			break ;

		case ETAT_CLOCHE_DING1 :
			cloche.allumer() ;
			break ;

		case ETAT_CLOCHE_ETEINDRE1 :
			cloche.eteindre() ;
			break ;

		case ETAT_CLOCHE_DING2 :
			cloche.allumer() ;
			break ;

		case ETAT_CLOCHE_ETEINDRE2 :
			cloche.eteindre() ;
			break ;

		case ETAT_CLOCHE_TEMPO :
			cloche.eteindre() ;
			break ;
		}
	}


	/** 
	 * MAIN FUNCTION DE LA CLOCHE DEPART.
	 *
	 * @param vitesse	Vitesse actuelle de la locomotive en km/h.
	 * @return	Aucun.
	 */
	void run(int vitesse) {
		calculerEntrees() ;
		calculerEtat(vitesse) ;
		calculerActions() ;
	}
} ;


#endif