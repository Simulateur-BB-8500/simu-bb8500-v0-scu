/*
 * BoiteALeviers.h
 *
 * Created: 18/04/2016
 * Author: Ludovic Lesur
 *
 * Avancement : D�verouillage de la bo�te � leviers et machine � �tats du disjoncteur cod�es mais non test�es.
				Suite du travail : coder la machine � �tats des ventilateurs moteurs.
 */


#ifndef BOITEALEVIERS_H
#define BOITEALEVIERS_H


// Include
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Interrupteur.h"
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/DoubleInterrupteur.h"
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Instructions.h"


// Etats de la MAE du disjoncteur
#define ETAT_DJ_OUVERT 0
#define ETAT_DJ_INACTIF 1
#define ETAT_DJ_FERME 2
#define ETAT_DJ_ATTENTE_ENCLENCHEMENT 3
#define ETAT_DJ_ATTENTE_INTERRUPTEUR 4
#define ETAT_DJ_ENCLENCHE 5

// Dur�e n�cessaire de maintien de ZEN en ms.
#define TEMPO_ENCLENCHEMENT 3000

// Etats de la MAE des fanaux
#define ETAT_FANAL_ETEINT 0
#define ETAT_FANAL_ALLUME_KEYBOARD 1
#define ETAT_FANAL_ALLUME 2
#define ETAT_FANAL_ETEINT_KEYBOARD 3

// Etats de la MAE des projecteurs
#define ETAT_PROJECTEURS_ETEINTS 0
#define ETAT_PROJECTEURS_ALLUMES 1


class BoiteALeviers {
	
private :

	Interrupteur cleBl ;
	Interrupteur ventilos ;

	// MAE du disjoncteur
	Interrupteur zdj ;
	Interrupteur encDj ;
	int etatDj ;
	int tempoEtat ;

	
public :

	/** 
	 * CONSTRUCTEUR DE LA CLASSE BOITEALEVIERS.
	 *
	 * @param pCleBL		Cl� de d�verouillage de la bo�te � leviers de type 'Interrupteur'.
	 * @param pZdj			Interrupteur de fermeture du disjoncteur ZDJ de type 'Interrupteur'.
	 * @param pEncDj		Interrupteur d'enclenchement du disjoncteur ZEN de type 'Interrupteur'.
	 * @param pVentilos		Interrupteur d'activation des ventilateurs moteurs de type 'Interrupteur'.
	 * @param pFanaux		Interrupteurs d'allumage des fanaux gauche et droit, de type 'DoubleInterrupteur'.
	 * @param pProjecteurs	Interrupteur d'allumage des projecteurs de type 'Interrupteur'.
	 * @return				Aucun.
	 */
	BoiteALeviers(Interrupteur pCleBl, Interrupteur pZdj, Interrupteur pEncDj, Interrupteur pVentilos) {
		cleBl = pCleBl ;
		ventilos = pVentilos ;
		// MAE du disjoncteur
		zdj = pZdj ;
		encDj = pEncDj ;
		etatDj = ETAT_DJ_OUVERT ;
		tempoEtat = 0 ;	
	}
	
	
	/** 
	 * INITIALISE LES INTERRUPTEURS DE LA BOITE A LEVIERS.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void init() {
		cleBl.init() ;
		zdj.init() ;
		encDj.init() ;
		ventilos.init() ;
	}
	

	/** 
	 * DETERMINE L'ETAT DE LA MACHINE A ETATS DU DISJONCTEUR.
	 *
	 * @param urgence		Bool�en indiquant si un freinage d'urgence a �t� d�clench� par le BPURG ou le KVB.
	 * @param disjonction	Bool�en indiquant si une surintensit� a �t� d�tect�e sur les amp�rem�tres moteurs.
	 * @return				Aucun.
	 */
	void calculerEtatDj(boolean urgence, boolean disjonction) {

		switch (etatDj) {

		case ETAT_DJ_OUVERT :
			if (zdj.marche()) {
				etatDj = ETAT_DJ_FERME ;
			}
			if (encDj.marche()) {
				etatDj = ETAT_DJ_INACTIF ;
			}
			break ;

		case ETAT_DJ_INACTIF :
			if (encDj.arret()) {
				etatDj = ETAT_DJ_OUVERT ;
			}
			break ;

		case ETAT_DJ_FERME :
			if (zdj.arret()) {
				etatDj = ETAT_DJ_OUVERT ;
			}
			if (encDj.marche()) {
				etatDj = ETAT_DJ_ATTENTE_ENCLENCHEMENT ;
				tempoEtat = millis() ; // D�clenchement timer ETAT_ATTENTE_ENCLENCHEMENT.
			}
			break ;

		case ETAT_DJ_ATTENTE_ENCLENCHEMENT :
			if (encDj.arret()) {
				etatDj = ETAT_DJ_FERME ;
			}
			else {
				if (millis() > tempoEtat+TEMPO_ENCLENCHEMENT) {
					etatDj = ETAT_DJ_ATTENTE_INTERRUPTEUR ;
				}
			}
			break ;

		case ETAT_DJ_ATTENTE_INTERRUPTEUR :
			if (encDj.arret()) {
				etatDj = ETAT_DJ_ENCLENCHE ;
			}
			break ;

		case ETAT_DJ_ENCLENCHE :
			if (zdj.arret()) {
				etatDj = ETAT_DJ_OUVERT ;
			}
			if (disjonction || urgence) {
				etatDj = ETAT_DJ_FERME ;
			}
			if (encDj.marche()) {
				etatDj = ETAT_DJ_ATTENTE_INTERRUPTEUR ;
			}
			break ;
		}
	}


	/** 
	 * MET A JOUR LES VARIABLES GLOBALES EN FONCTION DE L'ETAT DU DISJONCTEUR.
	 *
	 * @param ptrDjFer	Pointeur sur le variable globale indiquant si le disjoncteur est ferm�.
	 * @param ptrDjEnc	Pointeur sur la variable globale indiquant si le disjoncteur est enclench�.
	 * @return			Aucun.
	 */
	void calculerActionsDj(boolean* ptrDjFer, boolean* ptrDjEnc) {
		
		switch (etatDj) {

		case ETAT_DJ_OUVERT :
			(*ptrDjFer) = false ;
			(*ptrDjEnc) = false ;
			SerialUSB.write(I_Ouverture_DJ) ; // Lancement du son d'ouverture du disjoncteur.
			break ;

		case ETAT_DJ_INACTIF :
			(*ptrDjFer) = false ;
			(*ptrDjEnc) = false ;
			break ;

		case ETAT_DJ_FERME :
			(*ptrDjFer) = true ;
			(*ptrDjEnc) = false ;
			SerialUSB.write(I_Enclench_DJ_Off) ; // Arr�t du son de l'enclenchement si l'on vient de ETAT_ATTENTE_ENCLENCHEMENT.
			break ;

		case ETAT_DJ_ATTENTE_ENCLENCHEMENT :
			(*ptrDjFer) = true ;
			(*ptrDjEnc) = false ;
			SerialUSB.write(I_Enclench_DJ) ; // Lancement du son de l'enclenchement.
			break ;

		case ETAT_DJ_ATTENTE_INTERRUPTEUR :
			(*ptrDjFer) = true ;
			(*ptrDjEnc) = true ;
			break ;

		case ETAT_DJ_ENCLENCHE :
			(*ptrDjFer) = true ;
			(*ptrDjEnc) = true ;
			break ;
		}
	}


	/** 
	 * MAIN FUNCTION DE LA BOITE A LEVIERS.
	 *
	 * @param ptrDjFer		Pointeur sur le variable globale indiquant si le disjoncteur est ferm�.
	 * @param ptrDjEnc		Pointeur sur la variable globale indiquant si le disjoncteur est enclench�.
	 * @param urgence		Bool�en indiquant si un freinage d'urgence a �t� d�clench� par le BPURG ou le KVB.
	 * @param disjonction	Bool�en indiquant si une surintensit� a �t� d�tect�e sur les amp�rem�tres moteurs.
	 * @return				Aucun.
	 */
	void run(boolean* ptrBlDeverouillee, boolean* ptrDjFer, boolean* ptrDjEnc, boolean urgence, boolean disjonction) {
		
		// D�verouillage de la bo�te � leviers
		if (cleBl.marche()) {
			(*ptrBlDeverouillee) = true ;
		}
		else {
			(*ptrBlDeverouillee) = false ;
		}
		
		// Disjoncteur
		calculerEtatDj(urgence, disjonction) ;
		calculerActionsDj(ptrDjFer, ptrDjEnc) ;

		// Ventilateurs moteurs
		if ((ventilos.marche()) && ((*ptrDjEnc) == true)) {
			SerialUSB.write(I_Allumage_Ventilos) ;
		}
		else {
			SerialUSB.write(I_Extinction_Ventilos) ;
		}
	}
} ;


#endif