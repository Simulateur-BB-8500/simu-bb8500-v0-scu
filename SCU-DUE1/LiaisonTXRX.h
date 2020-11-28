/*
 * LiaisonTXRX.h
 *
 * Created: 27/06/2016
 * Author: Ludovic Lesur
 *
 * Avancement : Classe entièrement codée et commentée, mais non testée avec la DUE.2.
 */ 


#ifndef LIAISONTXRX_H
#define LIAISONTXRX_H


// Include
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Instructions.h"


// Masques pour la récupération des variables sur le canal Serial2
#define BIT_URGENCE 0b01
#define BIT_DISJONCTION 0b10


class LiaisonTXRX {
	
public :
	
	/** 
	 * CONSTRUCTEUR DE LA CLASSE LIAISONTXRX.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	LiaisonTXRX() {}
	
	
	/** 
	 * INITIALISE LES LIAISONS SERIE DE LA CARTE ARDUINO DUE.1.
	 *
	 * @param baudRate	Débit en baud/s.
	 * @return			Aucun.
	 */
	void begin(int baudRate) {
		Serial1.begin(baudRate) ; // DUE.2 -> Etat ZBA.
		Serial2.begin(baudRate) ; // DUE.2 -> Freinage d'urgence et disjonction surintensité.
		Serial3.begin(baudRate) ; // DUE.2 -> Vitesse.
	}
	

	/** 
	 * LIT L'ETAT DU ZBA ENVOYE PAR LA DUE.2.
	 *
	 * @param ptrZbaActif	Pointeur sur la variable globale indiquant l'état du ZBA.
	 * @return				Aucun.
	 */
	void lireZba(boolean* ptrZbaActif) {
		if (Serial1.available()) {
			(*ptrZbaActif) = Serial1.read() ;
		}
	}
	

	/** 
	 * LIT L'ETAT DU FREINAGE D'URGENCE ET DU CAPTEUR DE SURINTENSITE ENVOYE PAR LA DUE.2.
	 *
	 * @param ptrUrgence		Pointeur sur la variable globale indiquant si un freinage d'urgence a été déclenché par le BPURG ou le KVB.
	 * @param ptrDisjonction	Pointeur sur la variable globale indiquant si une surintensité a été mesurée sur les ampèremètres moteurs.
	 * @return					Aucun.
	 */
	void lireUrgence(boolean* ptrUrgence, boolean* ptrDisjonction) {
		if (Serial2.available()) {
			int code = Serial2.read() ;
			(*ptrUrgence) = code && BIT_URGENCE ;
			(*ptrDisjonction) = code && BIT_DISJONCTION ;
		}
	}


	/** 
	 * LIT LA VITESSE ACTUELLE DE LA LOCOMOTIVE ENVOYEE PAR LA DUE.2.
	 *
	 * @param ptrVitesse	Pointeur sur la variable globale contenant la vitesse de la locomotive en km/h.
	 * @return				Aucun.
	 */
	void lireVitesse(int* ptrVitesse) {
		if (Serial3.available()) {
			(*ptrVitesse) = Serial3.read() ;
		}
	}
	

	/** 
	 * MAIN FUNCTION DES LIAISONS SERIE DE LA DUE.1.
	 *
	 * @param ptrZbaActif		Pointeur sur la variable globale indiquant l'état du ZBA.
	 * @param ptrUrgence		Pointeur sur la variable globale indiquant si un freinage d'urgence a été déclenché par le BPURG ou le KVB.
	 * @param ptrDisjonction	Pointeur sur la variable globale indiquant si une surintensité a été mesurée sur les ampèremètres moteurs.
	 * @param ptrVitesse		Pointeur sur la variable globale contenant la vitesse de la locomotive en km/h.
	 * @return					Aucun.
	 */
	void run(boolean* ptrZbaActif, boolean* ptrUrgence, boolean* ptrDisjonction, int* ptrVitesse) {
		lireZba(ptrZbaActif) ;
		lireUrgence(ptrUrgence, ptrDisjonction) ;
		lireVitesse(ptrVitesse) ;
	}
} ;


#endif