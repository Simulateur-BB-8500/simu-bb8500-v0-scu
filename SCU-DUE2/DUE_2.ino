/*
 * DUE_2.ino
 *
 * Created: 08/07/2015
 * Author: Ludovic
 */


// Include commun
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Instructions.h"
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Sonnerie.h"

// Include
#include "NetlistDUE2.h"
#include "BPURG.h"
#include "ClocheDepart.h"
#include "KVB.h"
#include "LiaisonCOMTXRX.h"
#include "Surintensite.h"
#include "Tachro.h"



/*** ELEMENTS DU PUPITRE ***/

// Sectionneur batterie
Interrupteur zba(P_ZBA, N, 2000) ;

// Boîte à leviers
Interrupteur cleBL(P_BL_ZDV, N, T) ;

// Boutons poussoirs
Interrupteur bpval(P_KVB_BPVAL, N, T) ;
Interrupteur bpMv(P_KVB_BPVAL, N, T) ;
Interrupteur bpFc(P_KVB_BPVAL, N, T) ;
Interrupteur bpTest(P_KVB_BPVAL, N, T) ;
Interrupteur bpSf(P_KVB_BPSF, N, T) ;
Interrupteur acsf(P_ACSF, N, T) ;
// Lampes
Lampe lVal(P_KVB_LVAL) ;
Lampe lMv(P_KVB_LMV) ;
Lampe lFc(P_KVB_LFC) ;
Lampe lV(P_KVB_LV) ;
Lampe lFu(P_KVB_LFU) ;
Lampe lPSol(P_KVB_LPS) ;
Lampe lPEngin(P_KVB_LPE) ;
Lampe lssf(P_KVB_LSSF) ;
// Segments
Lampe zsa(P_KVB_ZSA) ;
Lampe zsb(P_KVB_ZSB) ;
Lampe zsc(P_KVB_ZSC) ;
Lampe zsd(P_KVB_ZSD) ;
Lampe zse(P_KVB_ZSE) ;
Lampe zsf(P_KVB_ZSF) ;
Lampe zsg(P_KVB_ZSG) ;
// Afficheurs 7 segments
Afficheur7Segments zjg(P_KVB_ZJG, zsa, zsb, zsc, zsd, zse, zsf, zsg) ;
Afficheur7Segments zjm(P_KVB_ZJC, zsa, zsb, zsc, zsd, zse, zsf, zsg) ;
Afficheur7Segments zjd(P_KVB_ZJD, zsa, zsb, zsc, zsd, zse, zsf, zsg) ;
Afficheur7Segments zvg(P_KVB_ZVG, zsa, zsb, zsc, zsd, zse, zsf, zsg) ;
Afficheur7Segments zvm(P_KVB_ZVC, zsa, zsb, zsc, zsd, zse, zsf, zsg) ;
Afficheur7Segments zvd(P_KVB_ZVD, zsa, zsb, zsc, zsd, zse, zsf, zsg) ;
// Son RS
Sonnerie sonRs(P_RS) ;
// KVB
KVB kvb(bpval, bpMv, bpFc, bpTest, bpSf, acsf, lVal, lMv, lFc, lV, lFu, lPSol, lPEngin, lssf, zjg, zjm, zjd, zvg, zvm, zvd, sonRs) ;

// Tachro
Tachro tachro(P_TCH_INH_A, P_TCH_PWM_A, P_TCH_INH_B, P_TCH_PWM_B, P_TCH_INH_C, P_TCH_PWM_C) ;

// BPURG
Interrupteur zurg(P_BPURG, N, T) ;
BPURG bpurg(zurg) ;

// Cloche départ
Interrupteur zct(P_ZCT, N, T) ;
Sonnerie cloche(P_DEP) ;
ClocheDepart clocheDepart(zct, cloche) ;

// Capteur des intensités moteurs
Surintensite surintensite(P_AM_CAPTEUR) ;

// Liaison série
LiaisonCOMTXRX liaisonCOMTXRX ;


/*** VARIABLES GLOBALES ***/

int vitesse = 0 ;
int limite = 0 ;
int etatSignal = 0 ;
boolean urgence = false ;
boolean disjonction = false ;


/*** SETUP ***/

void setup() {
	analogReadResolution(READ_RESOLUTION) ;
	analogWriteResolution(WRITE_RESOLUTION) ;
	// Initialisation des pins
	zba.init() ;
	cleBL.init() ;
	bpurg.init() ;
	clocheDepart.init() ;
	kvb.init() ;
	liaisonCOMTXRX.begin(BAUD_RATE) ;
	tachro.init() ;

	// Debug
	SerialUSB.begin(9600) ;
}


/*** BOUCLE PRINCIPALE ***/

void loop() {

	/*// Transfert de données
	liaisonCOMTXRX.run(&vitesse, &limite, &etatSignal, zba.marche(), urgence, disjonction) ;

	if (zba.marche()) {

		// Tachro
		tachro.run(vitesse) ;
	
		// KVB
		kvb.run(cleBL.marche(), vitesse, limite, etatSignal, &urgence) ;

		// BPURG
		bpurg.run(&urgence) ;

		// Cloche départ
		clocheDepart.run(vitesse) ;

		// Intensités moteurs
		surintensite.run(&disjonction) ;
	}*/

	vitesse = (int) ((((float)analogRead(A0))/1023.0)*140.0) ;
	SerialUSB.println(vitesse) ;
	tachro.run(vitesse) ;
}
