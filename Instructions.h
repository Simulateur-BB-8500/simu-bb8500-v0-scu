/*
 * Instructions.h
 *
 * Created: 20/11/2015
 * Author: Ludovic
 */ 


#ifndef INSTRUCTION_H
#define INSTRUCTION_H


/*** INSTRUCTIONS BETWEEN DUE.1 AND SGCU ***/

// ZBA
#define I_ZBA_ON 0x01
#define I_ZBA_OFF 0x02

// KVB
#define I_KVB_ON 0x03
#define I_KVB_OFF 0x04

// Réservoir de secours
#define I_RSEC 0x05

// Pantographes
#define I_ZPT_BACK_UP 0x06
#define I_ZPT_BACK_DOWN 0x07
#define I_ZPT_FRONT_UP 0x08
#define I_ZPT_FRONT_DOWN 0x09

// Disjoncteur
#define I_ZEN_ON 0x0A
#define I_ZEN_OFF 0x0B
#define I_ZDJ_OPEN 0x0C

// Compresseurs
#define I_ZCAZCD_STATE0 0x0D
#define I_ZCAZCD_STATE1 0x0E
#define I_ZCAZCD_STATE2 0x0F
#define I_ZCAZCD_STATE3 0x10
#define I_ZCAZCD_STATE4 0x11

// Pression CP
#define CP_CODING_OFFSET 0x9A // Value = 10*pression between 154 and 254.
#define CP_SUPPLY_TIME 125000.0 // Must correspond to the length of 'regulationMax.wav' sound (in ms).
#define CP_HYSTERESIS_LOW 7.8
#define CP_HYSTERESIS_HIGH 9.0
#define CP_MAXIMUM_VALUE 9.5
#define CP_SUPPLY_SPEED (CP_HYSTERESIS_HIGH)/(CP_SUPPLY_TIME) // In bar/ms.

// MES FPB
#define I_FPB_SERVICE_ON 0x12
#define I_FPB_SERVICE_OFF 0x13
#define I_FPB_SHUT_DOWN 0x14

// Grand débit
#define I_BPGD 0x15

// Ventilateurs moteurs
#define I_ZVM_ON 0x16
#define I_ZVM_OFF 0x17

// Inverseur
#define I_INV_FORWARD 0x18
#define I_INV_NEUTRAL 0x19
#define I_INV_BACKWARD 0x1A
#define I_INV_RESET 0x1B

// Manipulateur de traction
#define I_MP_T 0x1C // T+, T-, F+ or F-.
#define I_MP_0 0x1D
#define I_MP_PR 0x1E
#define I_MP_P 0x1F
#define I_MP_RESET 0x20

// FPB
#define I_FPB_APPLY 0x21
#define I_FPB_RELEASE 0x22
#define I_FPB_NEUTRAL 0x23

// Frein direct
#define I_FD_APPLY 0x24
#define I_FD_RELEASE 0x25
#define I_FD_NEUTRAL 0x26

// Frein d'urgence
#define I_BPURG 0x27

// Avertisseur
#define I_S_HIGH_TONE_ON 0x28
#define I_S_HIGH_TONE_OFF 0x29
#define I_S_LOW_TONE_ON 0x2A
#define I_S_LOW_TONE_OFF 0x2B


/*** INSTRUCTIONS BETWEEN DUE.2 AND SGCU ***/

/*** COMMON ***/

// Vitesse de transmission
#define BAUD_RATE 9600
// Non opération
#define I_NOP 255

#endif
