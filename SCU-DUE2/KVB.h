/*
 * KVB.h
 *
 * Created: 19/04/2016
 * Author: Ludovic Lesur
 *
 * Avancement : Classe fonctionnelle. La machine à états est opérationnelle, testée avec le KVB réel et les circuits imprimés associés (22/12/2016).
 *				Seule l'initialisation est codée (du déverouillage de la BL à la validation des paramètres).
 *				Suite du travail : ajouter des états et des transitions pour simuler le fonctionnement nominal du KVB.
 */


#ifndef KVB_H
#define KVB_H


// Include
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Afficheur7Segments.h"
#include "C:/Users/Ludovic/Documents/Atmel Studio/7.0/Simulateur_BB8500/Interrupteur.h"


// Etats de la MAE du KVB
#define ETAT_KVB_ETEINT 0
#define ETAT_KVB_INIT_PA400 1
#define ETAT_KVB_INIT_LPE 2
#define ETAT_KVB_INIT_UC512 3
#define ETAT_KVB_INIT_888 4
#define ETAT_KVB_ATTENTE_VAL_SF 5
#define ETAT_KVB_ATTENTE_SF 6
#define ETAT_KVB_ATTENTE_VAL 7
#define ETAT_KVB_PRET 8

// Durée d'affichage des écrans d'initialisation (ms)
#define TEMPS_INIT_PA400 2500
#define TEMPS_INIT_LPE 2000
#define TEMPS_INIT_UC512 2000
#define TEMPS_INIT_888 3000

// Fréquence de clignottement des lampes
#define PERIODE_LSSF 400 // ms
#define FREQ_LVAL 0.001 // kHz
#define PI 3.14159265


class KVB {
	
private :

	// Boutons poussoirs
	Interrupteur bpval ;
	Interrupteur bpmv ;
	Interrupteur bpfc ;
	Interrupteur bptest ;
	Interrupteur bpsf ;
	Interrupteur acsf ;
	
	// Lampes
	Lampe lval ;
	Lampe lmv ;
	Lampe lfc ;
	Lampe lv ;
	Lampe lfu ;
	Lampe lps ;
	Lampe lpe ;
	Lampe lssf ;
	
	// Afficheurs 7 segments
	Afficheur7Segments jauneG ;
	Afficheur7Segments jauneM ;
	Afficheur7Segments jauneD ;
	Afficheur7Segments vertG ;
	Afficheur7Segments vertM ;
	Afficheur7Segments vertD ;

	// Son RS
	Sonnerie sonRs ;
	
	// MAE
	int etat ;
	uint32_t tempoEtat ;
	float intensiteVal ;
	uint32_t tempoLSSF ;
	
public :
	
	/** 
	 * CONSTRUCTEUR DE LA CLASSE KVB.
	 *
	 * @param pBpval	Bouton poussoir BPVAL de type 'Interrupteur'.
	 * @param pBpmv		Bouton poussoir BPMV de type 'Interrupteur'.
	 * @param pBpfc		Bouton poussoir BPFC de type 'Interrupteur'.
	 * @param pBptest	Bouton poussoir BPTST de type 'Interrupteur'.
	 * @param pBpsf		Bouton poussoir BPSF de type 'Interrupteur'.
	 * @param pAcsf		Bouton poussoir ACSF de type 'Interrupteur'.
	 * @param pLval		Lampe LVAL de type 'Lampe'.
	 * @param pLmv		Lampe LMV de type 'Lampe'.
	 * @param pLfc		Lampe LFC de type 'Lampe'.
	 * @param pLv		Lampe LV de type 'Lampe'.
	 * @param pLfu		Lampe LFU de type 'Lampe'.
	 * @param pLps		Lampe LPS de type 'Lampe'.
	 * @param pLpe		Lampe LPE de type 'Lampe'.
	 * @param pLssf		Lampe LSSF de type 'Lampe'.
	 * @param pJauneG	Afficheur 7 segments jaune gauche de type 'Afficheur7Segments'.
	 * @param pJauneM	Afficheur 7 segments jaune milieu de type 'Afficheur7Segments'.
	 * @param pJauneD	Afficheur 7 segments jaune droit de type 'Afficheur7Segments'.
	 * @param pVertG	Afficheur 7 segments vert gauche de type 'Afficheur7Segments'.
	 * @param pVertM	Afficheur 7 segments vert milieu de type 'Afficheur7Segments'.
	 * @param pVertD	Afficheur 7 segments vert droit de type 'Afficheur7Segments'.
	 * @param pSonRs	Sonnerie de répétition des signaux de type 'Sonnerie'.
	 * @return			Aucun.
	 */
	KVB(Interrupteur pBpval, Interrupteur pBpmv, Interrupteur pBpfc, Interrupteur pBptest, Interrupteur pBpsf, Interrupteur pAcsf,
		Lampe pLval, Lampe pLmv, Lampe pLfc, Lampe pLv, Lampe pLfu, Lampe pLps, Lampe pLpe, Lampe pLssf,
		Afficheur7Segments pJauneG, Afficheur7Segments pJauneM, Afficheur7Segments pJauneD,
		Afficheur7Segments pVertG, Afficheur7Segments pVertM, Afficheur7Segments pVertD, Sonnerie pSonRs) {
		// Boutons poussoirs
		bpval = pBpval ;
		bpmv = pBpmv ;
		bpfc = pBpfc ;
		bptest = pBptest ;
		bpsf = pBpsf ;
		acsf = pAcsf ;
		// Lampes
		lval = pLval ;
		lmv = pLmv ;
		lfc = pLfc ;
		lv = pLv ;
		lfu = pLfu ;
		lps = pLps ;
		lpe = pLpe ;
		lssf = pLssf ;
		// Afficheurs 7 segments
		jauneG = pJauneG ;
		jauneM = pJauneM ;
		jauneD = pJauneD ;
		vertG = pVertG ;
		vertM = pVertM ;
		vertD = pVertD ;
		// Son RS
		sonRs = pSonRs ;
		// Initialisation des variables
		etat = ETAT_KVB_ETEINT ;
		intensiteVal = 0.0 ;
		tempoLSSF = 0 ;
	}
	
	
	/** 
	 * INITIALISE LES BOUTONS POUSSOIRS ET INDICATEURS LUMINEUX DU KVB.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void init() {
		// Boutons poussoirs
		bpval.init() ;
		bpmv.init() ;
		bpfc.init() ;
		bptest.init() ;
		bpsf.init() ;
		acsf.init() ;
		// Lampes
		lval.init() ;
		lmv.init() ;
		lfc.init() ;
		lv.init() ;
		lfu.init() ;
		lps.init() ;
		lpe.init() ;
		lssf.init() ;
		// Afficheurs 7 segments
		jauneG.init() ;
		jauneM.init() ;
		jauneD.init() ;
		vertG.init() ;
		vertM.init() ;
		vertD.init() ;
	}
	

	/** 
	 * AFFICHE 'PA 400' SUR LES AFFICHEURS 7 SEGMENTS DU KVB.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void PA400() {
		eteindreAfficheurs() ;
		jauneG.aff_P(true) ;
		jauneM.aff_A(true) ;
		vertG.aff_4(true) ;
		vertM.aff_0(true) ;
		vertD.aff_0(true) ;
	}
	

	/** 
	 * AFFICHE 'UC 512' SUR LES AFFICHEURS 7 SEGMENTS DU KVB.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void UC512() {
		eteindreAfficheurs() ;
		jauneG.aff_U(true) ;
		jauneM.aff_C(true) ;
		vertG.aff_5(true) ;
		vertM.aff_1(true) ;
		vertD.aff_2(true) ;
	}
	

	/** 
	 * AFFICHE 'bb8 614' SUR LES AFFICHEURS 7 SEGMENTS DU KVB.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void bb8614() {
		eteindreAfficheurs() ;
		jauneG.aff_b(true) ;
		jauneM.aff_b(true) ;
		jauneD.aff_8(true) ;
		vertG.aff_6(true) ;
		vertM.aff_1(true) ;
		vertD.aff_4(true) ;
	}
	

	/** 
	 * AFFICHE '888 888' SUR LES AFFICHEURS 7 SEGMENTS DU KVB.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void double888() {
		jauneG.aff_8(false) ;
		jauneM.aff_8(false) ;
		jauneD.aff_8(false) ;
		vertG.aff_8(false) ;
		vertM.aff_8(false) ;
		vertD.aff_8(false) ;
	}
	

	/** 
	 * AFFICHE '--- ---' SUR LES AFFICHEURS 7 SEGMENTS DU KVB.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void tirets() {
		jauneG.aff_tiret(false) ;
		jauneM.aff_tiret(false) ;
		jauneD.aff_tiret(false) ;
		vertG.aff_tiret(false) ;
		vertM.aff_tiret(false) ;
		vertD.aff_tiret(false) ;
	}
	

	/** 
	 * AFFICHE 'b' VERT SUR LES AFFICHEURS 7 SEGMENTS DU KVB.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void bVert() {
		eteindreAfficheurs() ;
		vertM.aff_b(false) ;
	}
	

	/** 
	 * AFFICHE '00' VERT SUR LES AFFICHEURS 7 SEGMENTS DU KVB.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void double0Vert() {
		eteindreAfficheurs() ;
		vertM.aff_0(false) ;
		vertD.aff_0(false) ;
	}
	

	/** 
	 * AFFICHE '00' JAUNE SUR LES AFFICHEURS 7 SEGMENTS DU KVB.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void double0Jaune() {
		eteindreAfficheurs() ;
		jauneM.aff_0(false) ;
		jauneD.aff_0(false) ;
	}
	

	/** 
	 * ETEINT TOUS LES AFFICHEURS 7 SEGMENTS DU KVB.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void eteindreAfficheurs() {
		jauneG.eteindre() ;
		jauneM.eteindre() ;
		jauneD.eteindre() ;
		vertG.eteindre() ;
		vertM.eteindre() ;
		vertD.eteindre() ;
	}
	

	/** 
	 * FAIT CLIGNOTER LA LAMPE LSSF.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void clignoterLssf() {
		if (millis()-tempoLSSF > PERIODE_LSSF) {
			lssf.inverser() ;
			tempoLSSF = millis() ;
		}
	}
	

	/** 
	 * FAIT CLIGNOTER LA LAMPE LVAL.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void graduerLval() {
		intensiteVal = (TENSION_REF/2.0)*(1+sin(2.0*PI*FREQ_LVAL*(millis()))) ;
		lval.graduer(intensiteVal) ;
	}
	

	/** 
	 * ETEINT TOUTES LES LAMPES DU KVB.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void eteindreToutesLampes() {
		lval.eteindre() ;
		lmv.eteindre() ;
		lfc.eteindre() ;
		lv.eteindre() ;
		lfu.eteindre() ;
		lps.eteindre() ;
		lpe.eteindre() ;
		lssf.eteindre() ;
	}
	
	
	/** 
	 * DETERMINE L'ETAT DE LA MACHINE A ETATS DU KVB.
	 *
	 * @param blDeverouillee	Booléen indiquant si la boîte à leviers est déverouillée.
	 * @param vitesse			Vitesse courante de la locomotive en km/h.
	 * @param vitesseLim		Vitesse limite de la ligne actuellement parcourue en km/h.
	 * @param dernierSignal		Etat du dernier signal franchi.
	 * @param urgence			Pointeur sur la variable globale 'urgence' indiquant si un freinage d'urgence a été déclenché.
	 * @return					Aucun.
	 */
	void calculerEtat(boolean blDeverouillee, int vitesse, int vitesseLim, int dernierSignal, boolean* ptrUrgence) {

		switch(etat) {

		case ETAT_KVB_ETEINT :
			if (blDeverouillee) {
				etat = ETAT_KVB_INIT_PA400 ;
				tempoEtat = millis() ; // Déclenchement timer ETAT_INIT_PA400.
			}
			break ;

		case ETAT_KVB_INIT_PA400 :
			if (blDeverouillee == false) {
				etat = ETAT_KVB_ETEINT ;
			}
			else {
				if (millis()-tempoEtat > TEMPS_INIT_PA400) {
					etat = ETAT_KVB_INIT_LPE ;
					tempoEtat = millis() ; // Déclenchement timer ETAT_INIT_LPE.
				}
			}
			break ;

		case ETAT_KVB_INIT_LPE :
			if (blDeverouillee == false) {
				etat = ETAT_KVB_ETEINT ;
			}
			else {
				if (millis()-tempoEtat > TEMPS_INIT_LPE) {
					etat = ETAT_KVB_INIT_UC512 ;
					tempoEtat = millis() ; // Déclenchement timer ETAT_INIT_UC512.
				}
			}
			break ;

		case ETAT_KVB_INIT_UC512 :
			if (blDeverouillee == false) {
				etat = ETAT_KVB_ETEINT ;
			}
			else {
				if (millis()-tempoEtat > TEMPS_INIT_UC512) {
					etat = ETAT_KVB_INIT_888 ;
					tempoEtat = millis() ; // Déclenchement timer ETAT_INIT_888.
				}
			}
			break ;

		case ETAT_KVB_INIT_888 :
			if (blDeverouillee == false) {
				etat = ETAT_KVB_ETEINT ;
			}
			else {
				if (millis()-tempoEtat > TEMPS_INIT_888) {
					etat = ETAT_KVB_ATTENTE_VAL_SF ;
				}
			}
			break ;

		case ETAT_KVB_ATTENTE_VAL_SF :
			if (blDeverouillee == false) {
				etat = ETAT_KVB_ETEINT ;
			}
			else {
				if (acsf.marche() || bpsf.marche()) {
					etat = ETAT_KVB_ATTENTE_VAL ;
				}
				else {
					if (bpval.marche()) {
						etat = ETAT_KVB_ATTENTE_SF ;
					}
				}
			}
			break ;

		case ETAT_KVB_ATTENTE_VAL :
			if (blDeverouillee == false) {
				etat = ETAT_KVB_ETEINT ;
			}
			else {
				if (bpval.marche()) {
					etat = ETAT_KVB_PRET ;
				}
			}
			break ;

		case ETAT_KVB_ATTENTE_SF :
			if (blDeverouillee == false) {
				etat = ETAT_KVB_ETEINT ;
			}
			else {
				if (acsf.marche() || bpsf.marche()) {
					etat = ETAT_KVB_PRET ;
				}
			}
			break ;

		case ETAT_KVB_PRET :
			if (blDeverouillee == false) {
				etat = ETAT_KVB_ETEINT ;
			}
			break ;
		}
	}
	
	
	/** 
	 * ALLUME LES INDICATEURS DU KVB EN FONCTION DE L'ETAT ACTUEL DE LA MACHINE A ETATS.
	 *
	 * @param	Aucun.
	 * @return	Aucun.
	 */
	void calculerActions() {

		switch(etat) {

		case ETAT_KVB_ETEINT :
			Serial.write(I_Extinction_KVB) ;
			eteindreAfficheurs() ;
			eteindreToutesLampes() ;
			break ;

		case ETAT_KVB_INIT_PA400 :
			Serial.write(I_Allumage_KVB) ; // Instruction du son d'allumage envoyée durant le premier état d'initialisation.
			PA400() ;
			clignoterLssf() ;
			break ;

		case ETAT_KVB_INIT_LPE :
			eteindreAfficheurs() ;
			lpe.allumer() ;
			clignoterLssf() ;
			break ;

		case ETAT_KVB_INIT_UC512 :
			UC512() ;
			lpe.eteindre() ;
			clignoterLssf() ;
			break ;

		case ETAT_KVB_INIT_888 :
			double888() ;
			lmv.allumer() ;
			lfc.allumer() ;
			clignoterLssf() ;
			graduerLval() ;
			break ;

		case ETAT_KVB_ATTENTE_VAL_SF :
			eteindreAfficheurs() ;
			lmv.eteindre() ;
			lfc.eteindre() ;
			clignoterLssf() ;
			graduerLval() ;
			break ;

		case ETAT_KVB_ATTENTE_SF :
			clignoterLssf() ;
			lval.eteindre() ;
			break ;

		case ETAT_KVB_ATTENTE_VAL :
			lssf.eteindre() ;
			graduerLval() ;
			break ;

		case ETAT_KVB_PRET :
			tirets() ;
			lssf.eteindre() ;
			lval.eteindre() ;
			break ;

		default :
			eteindreAfficheurs() ;
			eteindreToutesLampes() ;
			break ;
		}
	}
	

	/** 
	 * MAIN FUNCTION DU KVB.
	 *
	 * @param blDeverouillee	Booléen indiquant si la boîte à leviers est déverouillée.
	 * @param vitesse			Vitesse courante de la locomotive en km/h.
	 * @param vitesseLim		Vitesse limite de la ligne actuellement parcourue en km/h.
	 * @param dernierSignal		Etat du dernier signal franchi.
	 * @param ptrUrgence		Pointeur sur la variable globale 'urgence' indiquant si un freinage d'urgence a été déclenché.
	 * @return					Aucun.
	 */
	void run(boolean blDeverouillee, int vitesse, int vitesseLim, int etatSignal, boolean* ptrUrgence) {
		calculerEtat(blDeverouillee, vitesse, vitesseLim, etatSignal, ptrUrgence) ;
		calculerActions() ;
	}
} ;


#endif