#include "stm32l1xx_conf.h"
#include "stm32l1xx.h"


void delay(int a);


int main(void) {
	RCC->AHBENR |= ( 3 << 0 );		// clock GPIOA & GPIOB
	GPIOB->MODER  |= ( 0x00005000 );	// Pin 6 & Pin 7 output
	GPIOB->ODR = ( 1 << 7 );		// Pin 7 = 1

	while (1) {
		// port output
		if ( GPIOA->IDR & 1 ) {		// USER switch pressed
			GPIOB->ODR ^= ( 3 << 6 ); // toggle both LEDs
			delay( 10000 );
		}
	}
}


void delay( int a ) {
	volatile int i, j;
	for ( i = 0; i < a; i++ ) {
		++j;
	}
}
