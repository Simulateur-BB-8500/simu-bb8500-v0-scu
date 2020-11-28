/*
 * OpenRails.h (Liste des raccourcis claviers utilisés dans OpenRails + fonction périodique de log)
 *
 * Created: 29/06/2016
 * Author: Ludovic
 */

#include "Arduino.h" 

#ifndef OPENRAILS_H
#define OPENRAILS_H

// Durée d'appui sur les raccourcis clavier en ms (entre Keyboard.press() et Keyboard.release()).
#define DUREE_KEYBOARD 50

// Pantographes
#define K_PANTO_AR 'q' // = 'A'
#define K_PANTO_AV 'b'

// Inverseur
#define K_INV_AV 'c'
#define K_INV_AR 'd'

// Manipulateur de traction
#define K_TRAC_P 'e'
#define K_TRAC_M 'f'
#define DUREE_KEYBOARD_TRACTION 300 // Durée d'appui des raccourcis clavier spécifique à la traction.
#define DUREE_KEYBOARD_CRAN_0 5000 // Durée plus longue pour être sûr de revenir à 0% de traction.

// Freinage
#define K_FPB_P 'g'
#define K_FPB_M 'h'
#define K_FD_P 'i'
#define K_FD_M 'j'
#define K_FRH_P 'k'
#define K_FRH_M 'l'
#define K_BPURG 'm'

// Auxiliaires
#define K_ESS_GLACES 'n'
#define K_SABLAGE 'o'

// Fanaux et projecteurs
#define K_ECLAIRAGE_ON 'p'
#define K_ECLAIRAGE_OFF 'q'
#define K_PROJECTEURS K_NOP

// Divers
#define K_MASK_CAB 'z' // = 'w'
#define K_CHANGE_CAB 'x'

// Log
#define K_LOG 'y'
#define PERIODE_LOG 500 // Période du log des données (en ms)

// Raccourci clavier n'ayant aucun effet
#define K_NOP 'w' // = 'z'


class OpenRails {

private :
	uint32_t n ;
	boolean inh ; // Le log clavier ne devient actif que lorsque la BL est déverouillée
	uint32_t debut ;

public :

	/* Constructeur */

	OpenRails() {
		n = 0 ;
		inh = true ;
		debut = 0 ;
	}
	
	/* Méthodes */
	
	void log(boolean blDev) {
		if (blDev) {
			if (inh = true) {
				debut = millis() ;
				n = 0 ;
				inh = false ;
			}
			if (millis() > (debut + n*PERIODE_LOG + DUREE_KEYBOARD)) {
				Keyboard.release(K_LOG) ;
				n++ ;
			}
			else {
				if (millis() > debut+n*PERIODE_LOG) {
					Keyboard.press(K_LOG) ;
				}
			}
		}
		else {
			Keyboard.release(K_LOG) ;
			inh = true ;
		}
	}
} ;


#endif