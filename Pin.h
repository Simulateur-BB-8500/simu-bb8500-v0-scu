/*
 * Pin.h
 *
 * Created: 15/03/2016
 * Author: Ludovic
 */ 

#include "Arduino.h"

#ifndef PIN_H
#define PIN_H

// Tensions de référence
#define TENSION_REF 3.3
#define GND 0.0

// Nombre de bits d'échantillonage des pins analogiques
#define READ_RESOLUTION 12
#define WRITE_RESOLUTION 12

// Pleine échelle des pins analogiques
#define READ_PE pow(2, READ_RESOLUTION)-1
#define WRITE_PE pow(2, WRITE_RESOLUTION)-1

// Delai de filtrage des commutation (ms)
#define T 100

#define ERREUR -1

// Types
#define MLI 0
#define NUM 1
#define ANA 2

// Modes
#define E false
#define S true

class Pin {
	
private :
	uint32_t numPin ;
	uint32_t type ; // PWM, NUM ou ANA
	boolean mode ; // E ou S
	
	// Pins numériques
	uint32_t ac ; // LOW ou HIGH
	uint32_t pr ; // LOW ou HIGH
	uint32_t etat ; // LOW ou HIGH
	uint32_t tOn ; // Instant de passage de 0 à 1
	uint32_t tOff ; // Instant de passage de 1 à 0
	uint32_t tempo ;
	
public :

	/* Constructeurs */
	
	// Constructeur sans argument
	Pin() {
		numPin = ERREUR ;
		type = ERREUR ;
		mode = ERREUR ;
		ac = HIGH ;
		pr = HIGH ;
		etat = HIGH ;
		tOn = 0 ;
		tOff = 0 ;
		tempo = 0 ;
	}
	
	// Constructeur avec arguments
	void setPin(uint32_t pNumPin, boolean pMode, uint32_t pTempo) {
		switch (getType(pNumPin)) {
		case MLI :
			numPin = pNumPin ;
			type = MLI ;
			break ;
		case NUM :
			numPin = pNumPin ;
			type = NUM ;
			break ;
		case ANA :
			numPin = pNumPin ;
			type = ANA ;
			break ;
		default :
			numPin = ERREUR ;
			type = ERREUR ;
			break ;
		}
		mode = pMode ;
		tempo = pTempo ;
	}
	
	/* Méthodes */
	
	// Accès au numéro de pin
	uint32_t getNumPin() {
		return numPin ;
	}
	
	// Renvoie le type de pin en fonction de son numéro (propre à la carte Arduino Due)
	int getType(uint32_t n) {
		int resultat = ERREUR ;
		if ((n >= 2) && (n <= 13)) {
			resultat = MLI ;
		}
		if ((n >= 22) && (n <= 53)) {
			resultat = NUM ;
		}
		if ((n >= A0) && (n <= A11)) {
			resultat = ANA ;
		}
		return resultat ;
	}
	
	// Retourne la tension lue sur le pin (valeur en Volts)
	float read() {
		float mesure = ERREUR ;
		if (mode == E) {
			switch(type) {
			case NUM :
				antiRebonds() ;
				mesure = TENSION_REF*etat ;
				break ;
			case ANA :
				mesure = (TENSION_REF*analogRead(numPin))/(READ_PE) ;
				break ;
			}
		}
		return mesure ;
	}
	
	// Génère un tension sur le pin (valeur en Volts)
	void write(float tension) {
		if (mode == S) {
			switch(type) {
			case MLI :
				analogWrite(numPin, int((tension*WRITE_PE)/(TENSION_REF))) ;
				break ;
			case NUM :
				if (tension >= (TENSION_REF/2.0)) {
					digitalWrite(numPin, HIGH) ;
				}
				else {
					digitalWrite(numPin, LOW) ;
				}
				break ;
			}
		}
	}
	
	// Filtre les rebonds lors d'une commutation sur pin numérique
	// Un changement d'état n'est pris en compte que s'il est stable depuis (tempo) ms.
	void antiRebonds() {
		if (digitalRead(numPin) == LOW) {
			ac = LOW ;
			if (pr == HIGH) {
				tOff = millis() ;
			}
			if (millis() > tOff+tempo) {
				etat = LOW ;
			}
		}
		else {
			ac = HIGH ;
			if (pr == LOW) {
				tOn = millis() ;
			}
			if (millis() > tOn+tempo) {
				etat = HIGH ;
			}
		}
		pr = ac ;
	}	
} ;

#endif