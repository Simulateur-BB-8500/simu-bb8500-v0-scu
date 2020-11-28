/*
 * DUE_1.ino
 *
 * Created: 31/10/2014
 * Author: Ludovic Lesur
 */


// Include commun
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Instructions.h"
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Lampe.h"

// Include
#include "OpenRails.h"
#include "NetlistDUE1.h"
#include "Amperemetre.h"
#include "Avertisseur.h"
#include "BoiteALeviers.h"
#include "Compresseur.h"
#include "Freinage.h"
#include "Graduateur.h"
#include "Inverseur.h"
#include "LiaisonTXRX.h"
#include "ManipTraction.h"
#include "Manometre.h"
#include "VACMA.h"
#include "ZPT.h"


/*** ELEMENTS DU PUPITRE ***/

// Boîte à leviers
Interrupteur cleBL(P_BL_ZDV, N, T) ;
Interrupteur zdj(P_BL_ZDJ, I, T) ;
Interrupteur encDj(P_BL_ZEN, I, T) ;
Interrupteur ventilos(P_BL_ZVM, N, T) ;
BoiteALeviers bl(cleBL, zdj, encDj, ventilos) ;

// Compresseur
Interrupteur compAuto(P_BL_ZCA, I, T) ;
Interrupteur compDirect(P_BL_ZCD, N, T) ;
Compresseur compresseur(compAuto, compDirect) ;

// Eclairage
DoubleInterrupteur fanaux(P_BL_ZFG_ZFD) ;
Interrupteur projecteurs(P_BL_ZPR, N, T) ;

// Sélecteur pantographes
Interrupteur secours(P_RSEC, N, T) ;
Selecteur4 zPantos(P_ZPT) ;
ZPT zpt(P_VLG, secours, zPantos) ;

// Freinage
Selecteur4 pbl2(P_PBL2) ;
Interrupteur grandDebit(P_BPGD, N, T) ;
Selecteur3 fpb(P_FPB) ;
Selecteur3 freinDirect(P_FD) ;
Freinage freinage(pbl2, grandDebit, fpb, freinDirect) ;

// Surcharge
Interrupteur zsur(P_ZSUR, I, T) ;
Lampe lsur(P_LSUR) ;

// Inverseur
Selecteur3 manette(P_MP_INV) ;
Inverseur inverseur(manette) ;

// Manipulateur de traction
Graduateur graduateur ;
Interrupteur mpTr0(P_MP_0, I, T) ;
Interrupteur mpTrPlus(P_MP_TP, I, T) ;
Interrupteur mpTrMoins(P_MP_TM, I, T) ;
Interrupteur mpPr(P_MP_PR, I, T) ;
Interrupteur mpFrPlus(P_MP_FP, I, T) ;
Interrupteur mpFrMoins(P_MP_FM, I, T) ;
Interrupteur mpFr(P_MP_FR, I, T) ;
Interrupteur mpPrep(P_MP_P, I, T) ;
ManipTraction manipTraction(graduateur, mpTr0, mpTrPlus, mpTrMoins, mpPr, mpFrPlus, mpFrMoins, mpFr, mpPrep) ;

// Veille automatique
Interrupteur essaiVA(P_BL_ZVA, N, T) ;
Interrupteur cerclot(P_MP_VA, N, T) ;
Sonnerie sonRelachement(P_VA_R) ;
Sonnerie sonMaintien(P_VA_M) ;
VACMA vacma(essaiVA, cerclot, sonRelachement, sonMaintien) ;

// Avertisseur sonore
Selecteur3 sifflet(P_S) ;
Avertisseur avertisseur(sifflet) ;

// Ampèremètres moteurs
Interrupteur mpSp(P_MP_SP, N, T) ;
Amperemetre ampMoteur(P_AM1_AM2) ;

// Indicateurs lumineux
Lampe lsdj(P_LSDJ) ;
Lampe lsgr(P_LSGR) ;
Lampe lss(P_LSS) ;
Lampe lscb(P_LSCB) ;
Lampe lsp(P_LSP) ;
Lampe lspat(P_LSPAT) ;
Lampe lsba(P_LSBA) ;
Lampe lspi(P_LSPI) ;
Lampe lsrh(P_LSRH) ;

// Auxiliaires
DoubleInterrupteur sablage(P_BPSAB) ;
Interrupteur essuiesGlace(P_BPEV, N, T) ;
DoubleInterrupteur feuxRouges(P_ZLFR) ;

// Liaison série
LiaisonTXRX liaisonTXRX ;

// Log du simulateur
OpenRails openRails ;


/*** VARIABLES GLOBALES ***/


// Vitesse
int vitesse ;
// Sectionneur batterie
boolean zbaActif = false ;
// Boîte à leviers
boolean blDeverouillee = false ;
// Disjoncteur
boolean djFerme = false ;
boolean djEnclenche = false ;
boolean disjonction = false ;
// Traction
int cran = 0 ;
boolean rheostatique ;
// Manomètres
float pressionCP = 0.0 ;
float pressionRE = 0.0 ;
float pressionCG = 0.0 ;
float pressionCF1 = 0.0 ;
float pressionCF2 = 0.0 ;
boolean urgence = false ;
boolean compresseurActif = false ;


/*** SETUP ***/

void setup() {
	SerialUSB.begin(BAUD_RATE) ;
	liaisonTXRX.begin(BAUD_RATE) ;
	Keyboard.begin() ;
	analogReadResolution(READ_RESOLUTION) ;
	analogWriteResolution(WRITE_RESOLUTION) ;
	// Initialisation des pins
	avertisseur.init() ;
	bl.init() ;
	compresseur.init() ;
	inverseur.init() ;
	manipTraction.init() ;
	vacma.init() ;
	zpt.init() ;
}


/*** BOUCLE PRINCIPALE ***/

void loop() {

	liaisonTXRX.run(&zbaActif, &urgence, &disjonction, &vitesse) ;

	if (zbaActif) {
		bl.run(&blDeverouillee, &djFerme, &djEnclenche, urgence, disjonction) ;
		compresseur.update(&compresseurActif, djEnclenche, &pressionCP) ;
		//freinage.update(&pressionCP, &pressionRE, &pressionCG, &pressionCF1, &pressionCF2, compresseurActif) ;
		//manipTraction.update(&cran, &rheostatique) ;
		//inverseur.update() ;
		//vacma.update(&urgence, vitesse) ;
		//avertisseur.update() ;
		//openRails.log(blDev) ;
		//zpt.update(blDev, pressionCP) ;
	}
	else {
		// Mise à 0 de toutes les sorties.
	}
}