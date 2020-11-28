/*
 * LiaisonCOMTXRX.h
 *
 * Created: 27/06/2016
 * Author: Ludovic
 *
 * Avancement : Classe entièrement codée et commentée, mais non testée avec la DUE.1 et le programme en C++.
 */ 


#ifndef LIAISONCOMTXRX_H
#define LIAISONCOMTXRX_H


// Include
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Instructions.h"


// Etats de la MAE
#define ETAT_RXTX_DEMANDE_VITESSE 0
#define ETAT_RXTX_ATTENTE_VITESSE 1
#define ETAT_RXTX_DEMANDE_LIMITE 2
#define ETAT_RXTX_ATTENTE_LIMITE 3
#define ETAT_RXTX_DEMANDE_SIGNAL 4
#define ETAT_RXTX_ATTENTE_SIGNAL 5


class LiaisonCOMTXRX {
	
private :
	
	// MAE
	int etat ;
	
public :

	/** 
	 * CONSTRUCTEUR DE LA CLASSE LIAISONCOMTXRX.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	LiaisonCOMTXRX() {
		etat = ETAT_RXTX_DEMANDE_VITESSE ;
	}
		
	
	/** 
	 * INITIALISATION LES LIAISONS SERIES DE LA DUE.2.
	 *
	 * @param baudRate	Débit en baud/s.
	 * @return			Aucun.
	 */
	void begin(int baudRate) {
		Serial.begin(baudRate) ; // Communication avec le programme en C++.
		Serial1.begin(baudRate) ; // Etat ZBA -> DUE.1.
		Serial2.begin(baudRate) ; // Freinage d'urgence déclenché par KVB ou BPURG -> DUE.1.
		Serial3.begin(baudRate) ; // Disjonction surintensité -> DUE.1.
	}
	
	
	/** 
	 * TRANSMET L'ETAT DU ZBA A LA DUE.1.
	 *
	 * @param etatZba	Booléen indiquant l'ouverture ou la fermeture du ZBA.
	 * @return			Aucun.
	 */
	void sendZba(boolean etatZba) {
		Serial1.write(etatZba) ;
	}


	/** 
	 * TRANSMET L'ETAT DU FREINAGE D'URGENCE ET DU CAPTEUR DE SURINTENSITE A LA DUE.1.
	 *
	 * @param urgence			Booléen indiquant si un freinage d'urgence a été déclenché par le BPURG ou le KVB.
	 * @param disjonction		Booléen indiquant si une surintensité a été mesurée sur les ampèremètres moteurs.
	 * @return					Aucun.
	 */
	void sendUrgence(boolean urgence, boolean disjonction) {
		int code = urgence + (disjonction << 1) ;
		Serial2.write(code) ;
	}


	/** 
	 * TRANSMET LA VITESSE ACTUELLE DE LA LOCOMOTIVE A LA DUE.1.
	 *
	 * @param vitesse	Vitesse de la locomotive en km/h.
	 * @return			Aucun.
	 */
	void sendVitesse(int vitesse) {
		Serial3.write(vitesse) ;
	}
	

	/** 
	 * DETERMINE L'ETAT DE LA MACHINE A ETATS DU PORT COM ET MET A JOUR LES VARIABLES GLOBALES.
	 *
	 * @param ptrVitesse		Pointeur sur la variable globale contenant la vitesse actuelle de la locomotive en km/h.
	 * @param ptrVitesseLim		Pointeur sur la variable globale contenant la vitesse limite de la ligne en km/h.
	 * @param ptrSignal			Pointeur sur la variable globale contenant l'état du dernier signal franchi.
	 * @return					Aucun.
	 */
	void calculerEtat(int* ptrVitesse, int* ptrLimite, int* ptrEtatSignal) {
		
		switch(etat) {
			
		case ETAT_RXTX_DEMANDE_VITESSE :
			Serial.write(I_Vitesse) ;
			etat = ETAT_RXTX_ATTENTE_VITESSE ;
			break ;
			
		case ETAT_RXTX_ATTENTE_VITESSE :
			if (Serial.available()) {
				(*ptrVitesse) = Serial.read() ;
				etat = ETAT_RXTX_DEMANDE_LIMITE ;
			}
			break ;
			
		case ETAT_RXTX_DEMANDE_LIMITE :
			Serial.write(I_Limite) ;
			etat = ETAT_RXTX_ATTENTE_LIMITE ;
			break ;
			
		case ETAT_RXTX_ATTENTE_LIMITE :
			if (Serial.available()) {
				(*ptrLimite) = Serial.read() ;
				etat = ETAT_RXTX_DEMANDE_SIGNAL ;
			}
			break ;

		case ETAT_RXTX_DEMANDE_SIGNAL :
			Serial.write(I_Signal) ;
			etat = ETAT_RXTX_ATTENTE_LIMITE ;
			break ;

		case ETAT_RXTX_ATTENTE_SIGNAL :
			if (Serial.available()) {
				(*ptrEtatSignal) = Serial.read() ;
				etat = ETAT_RXTX_DEMANDE_VITESSE ;
			}
			break ;
		}
	}
	

	/** 
	 * MAIN FUNCTION DES LIAISONS SERIE DE LA DUE.2.
	 *
	 * @param ptrVitesse		Pointeur sur la variable globale contenant la vitesse actuelle de la locomotive en km/h.
	 * @param ptrVitesseLim		Pointeur sur la variable globale contenant la vitesse limite de la ligne en km/h.
	 * @param ptrSignal			Pointeur sur la variable globale contenant l'état du dernier signal franchi.
	 * @param etatZba			Booléen indiquant l'ouverture ou la fermeture du ZBA.
	 * @param urgence			Booléen indiquant si un freinage d'urgence a été déclenché par le BPURG ou le KVB.
	 * @param disjonction		Booléen indiquant si une surintensité a été mesurée sur les ampèremètres moteurs.
	 * @return					Aucun.
	 */
	void run(int* ptrVitesse, int* ptrLimite, int* ptrEtatSignal, boolean etatZba, boolean urgence, boolean disjonction) {
		calculerEtat(ptrVitesse, ptrLimite, ptrEtatSignal) ;
		sendZba(etatZba) ;
		sendUrgence(urgence, disjonction) ;
		sendVitesse(*ptrVitesse) ;
	}
} ;


#endif