/*
 * gpio.h
 *
 * Created: 05/06/2017.
 * Author: Ludovic.
 */ 


#ifndef GPIO_H
#define GPIO_H

#include <avr/io.h>

// CP.1 on PC3
#define CP_1_CONFIG() {DDRC |= (1 << DDC3);}
#define CP_1_HIGH() {PORTC |= (1 << PORTC3);}
#define CP_1_LOW() {PORTC &= ~(1 << PORTC3);}

// CP.2 on PC0
#define CP_2_CONFIG() {DDRC |= (1 << DDC0);}
#define CP_2_HIGH() {PORTC |= (1 << PORTC0);}
#define CP_2_LOW() {PORTC &= ~(1 << PORTC0);}

// CP.+ on PB0
#define CP_PLUS_CONFIG() {DDRB &= ~(1 << DDB0); PORTB |= (1 << PORTB0);}
#define CP_PLUS_PRESSED() ((PINB & (1 << PB0)) == 0)
// CP.- on PD7
#define CP_MOINS_CONFIG() {DDRD &= ~(1 << DDD7); PORTD |= (1 << PORTD7);}
#define CP_MOINS_PRESSED() ((PIND & (1 << PD7)) == 0)

// RE.1 on PC2
#define RE_1_CONFIG() {DDRC |= (1 << DDC2);}
#define RE_1_HIGH() {PORTC |= (1 << PORTC2);}
#define RE_1_LOW() {PORTC &= ~(1 << PORTC2);}

// RE.2 on PC1
#define RE_2_CONFIG() {DDRC |= (1 << DDC1);}
#define RE_2_HIGH() {PORTC |= (1 << PORTC1);}
#define RE_2_LOW() {PORTC &= ~(1 << PORTC1);}

// RE.+ on PB1
#define RE_PLUS_CONFIG() {DDRB &= ~(1 << DDB1); PORTB |= (1 << PORTB1);}
#define RE_PLUS_PRESSED() ((PINB & (1 << PB1)) == 0)

// RE.- on PD6
#define RE_MOINS_CONFIG() {DDRD &= ~(1 << DDD6); PORTD |= (1 << PORTD6);}
#define RE_MOINS_PRESSED() ((PIND & (1 << PD6)) == 0)

// CG.1 on PC4
#define CG_1_CONFIG() {DDRC |= (1 << DDC4);}
#define CG_1_HIGH() {PORTC |= (1 << PORTC4);}
#define CG_1_LOW() {PORTC &= ~(1 << PORTC4);}

// CG.2 on PC5
#define CG_2_CONFIG() {DDRC |= (1 << DDC5);}
#define CG_2_HIGH() {PORTC |= (1 << PORTC5);}
#define CG_2_LOW() {PORTC &= ~(1 << PORTC5);}

// CG.+ on PB2
#define CG_PLUS_CONFIG() {DDRB &= ~(1 << DDB2); PORTB |= (1 << PORTB2);}
#define CG_PLUS_PRESSED() ((PINB & (1 << PB2)) == 0)

// CG.- on PD5
#define CG_MOINS_CONFIG() {DDRD &= ~(1 << DDD5); PORTD |= (1 << PORTD5);}
#define CG_MOINS_PRESSED() ((PIND & (1 << PD5)) == 0)

// CF1.1 on PC7
#define CF1_1_CONFIG() {DDRC |= (1 << DDC7);}
#define CF1_1_HIGH() {PORTC |= (1 << PORTC7);}
#define CF1_1_LOW() {PORTC &= ~(1 << PORTC7);}

// CF1.2 on PC6
#define CF1_2_CONFIG() {DDRC |= (1 << DDC6);}
#define CF1_2_HIGH() {PORTC |= (1 << PORTC6);}
#define CF1_2_LOW() {PORTC &= ~(1 << PORTC6);}

// CF1.+ on PB3
#define CF1_PLUS_CONFIG() {DDRB &= ~(1 << DDB3); PORTB |= (1 << PORTB3);}
#define CF1_PLUS_PRESSED() ((PINB & (1 << PB3)) == 0)

// CF1.- on PD4
#define CF1_MOINS_CONFIG() {DDRD &= ~(1 << DDD4); PORTD |= (1 << PORTD4);}
#define CF1_MOINS_PRESSED() ((PIND & (1 << PD4)) == 0)

// CF2.1 on PD1
#define CF2_1_CONFIG() {DDRD |= (1 << DDD1);}
#define CF2_1_HIGH() {PORTD |= (1 << PORTD1);}
#define CF2_1_LOW() {PORTD &= ~(1 << PORTD1);}

// CF2.2 on PD2
#define CF2_2_CONFIG() {DDRD |= (1 << DDD2);}
#define CF2_2_HIGH() {PORTD |= (1 << PORTD2);}
#define CF2_2_LOW() {PORTD &= ~(1 << PORTD2);}

// CF2.+ on PB4
#define CF2_PLUS_CONFIG() {DDRB &= ~(1 << DDB4); PORTB |= (1 << PORTB4);}
#define CF2_PLUS_PRESSED() ((PINB & (1 << PB4)) == 0)

// CF2.- on PD3
#define CF2_MOINS_CONFIG() {DDRD &= ~(1 << DDD3); PORTD |= (1 << PORTD3);}
#define CF2_MOINS_PRESSED() ((PIND & (1 << PD3)) == 0)

// Pin initialisation.
void gpioInit() {
	// Disable JTAG (for PC2 to PC5)
	MCUCR |= (1 << JTD);
	// CP
	CP_1_CONFIG();
	CP_1_LOW();
	CP_2_CONFIG();
	CP_2_LOW();
	CP_PLUS_CONFIG();
	CP_MOINS_CONFIG();
	// RE
	RE_1_CONFIG();
	RE_1_LOW();
	RE_2_CONFIG();
	RE_2_LOW();
	RE_PLUS_CONFIG();
	RE_MOINS_CONFIG();
	// CG
	CG_1_CONFIG();
	CG_1_LOW();
	CG_2_CONFIG();
	CG_2_LOW();
	CG_PLUS_CONFIG();
	CG_MOINS_CONFIG();
	// CF1
	CF1_1_CONFIG();
	CF1_1_LOW();
	CF1_2_CONFIG();
	CF1_2_LOW();
	CF1_PLUS_CONFIG();
	CF1_MOINS_CONFIG();
	// CF2
	CF2_1_CONFIG();
	CF2_1_LOW();
	CF2_2_CONFIG();
	CF2_2_LOW();
	CF2_PLUS_CONFIG();
	CF2_MOINS_CONFIG();
}

#endif /* GPIO_H */