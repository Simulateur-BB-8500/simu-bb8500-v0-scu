/*
 * MoteurPasAPas.h (sur la base de Stepper.h adapté uniquement pour les moteurs unipolaires avec montage à deux pins de commande)
 *
 * Created: 21/04/2016
 * Author: Ludovic
 */

#ifndef MOTEURPASAPAS_H
#define MOTEURPASAPAS_H

#define NB_PAS 64

class MoteurPasAPas {

private :
	int direction ; // Direction of rotation
	int speed ; // Speed in RPMs
	unsigned long step_delay ; // Delay between steps, in ms, based on speed
	int number_of_steps ; // Total number of steps this motor can take
	int step_number ; // Which step the motor is on
	int motor_pin_1 ;
	int motor_pin_2 ;
	unsigned long last_step_time ; // Time stamp in us of when the last step was taken

	void stepMotor(int thisStep) {
		switch (thisStep) {
		case 0 : // 01
			digitalWrite(motor_pin_1, LOW) ;
			digitalWrite(motor_pin_2, HIGH) ;
			break ;
		case 1 : // 11
			digitalWrite(motor_pin_1, HIGH) ;
			digitalWrite(motor_pin_2, HIGH) ;
			break ;
		case 2 : // 10
			digitalWrite(motor_pin_1, HIGH) ;
			digitalWrite(motor_pin_2, LOW) ;
			break ;
		case 3 : // 00
			digitalWrite(motor_pin_1, LOW) ;
			digitalWrite(motor_pin_2, LOW) ;
			break ;
		}
	}

public :

	/* Constructeurs */

    // Constructeur sans argument
	MoteurPasAPas() {
		speed = 0 ;
		direction = 0 ;
		step_number = 0 ;
		last_step_time = 0 ;
		motor_pin_1 = 0 ;
		motor_pin_2 = 0 ;
		number_of_steps = 0 ;
	}

	// Constructeur avec numéros des pins de commande
    MoteurPasAPas(int pNumber_of_steps, int pMotor_pin_1, int pMotor_pin_2) {
		speed = 0 ;
		direction = 0 ;
		step_number = 0 ;
		last_step_time = 0 ;
		number_of_steps = pNumber_of_steps ;
		motor_pin_1 = pMotor_pin_1 ;
		motor_pin_2 = pMotor_pin_2 ;
	}

	/* Méthodes */

	// Initialisation des pins de commande
	void init() {
		pinMode(motor_pin_1, OUTPUT) ;
		pinMode(motor_pin_2, OUTPUT) ;
	}

    // Speed setter method
    void setSpeed(long whatSpeed) {
		step_delay = 60L * 1000L * 1000L / number_of_steps / whatSpeed ;
	}

    // Mover method
    void step(int steps_to_move) {
		// How many steps to take
		int steps_left = abs(steps_to_move) ;

		// Determine direction based on whether steps_to_mode is + or -
		if (steps_to_move > 0) {
			direction = 1 ;
		}
		if (steps_to_move < 0) {
			direction = 0 ;
		}

		// Decrement the number of steps, moving one step each time
		while (steps_left > 0) {
			unsigned long now = micros() ;
			// Move only if the appropriate delay has passed
			if (now - last_step_time >= step_delay) {
				// Get the timeStamp of when you stepped
				last_step_time = now ;
				// Increment or decrement the step number, depending on direction:
				if (direction == 1) {
					step_number++ ;
					if (step_number == number_of_steps) {
						step_number = 0 ;
					}
				}
				else {
					if (step_number == 0) {
						step_number = number_of_steps ;
					}
					step_number-- ;
				}
				// Decrement the steps left
				steps_left-- ;
				stepMotor(step_number % 4);
			}
		}
	}
} ;

#endif

