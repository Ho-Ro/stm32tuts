#include "stm32l1xx_conf.h"
#include <stdio.h>

void delay(int a);

int main(void) {
	GPIO_InitTypeDef gpio;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	GPIO_StructInit(&gpio);
	gpio.GPIO_Mode = GPIO_Mode_OUT;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_UP;

	gpio.GPIO_Pin = GPIO_Pin_7;	// green led
	GPIO_Init(GPIOB, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_6;	// blue led
	GPIO_Init(GPIOB, &gpio);

	gpio.GPIO_Mode = GPIO_Mode_IN;
	gpio.GPIO_Speed = GPIO_Speed_2MHz;
	gpio.GPIO_PuPd = GPIO_PuPd_DOWN;
	gpio.GPIO_Pin = GPIO_Pin_0;	// USER switch
	GPIO_Init(GPIOA, &gpio);

	static int led_state=0;

	while (1) {
		// port output - alternate between green and blue
		if ( GPIO_ReadInputDataBit( GPIOA, GPIO_Pin_0 ) ) // USER switch pressed
			led_state = !led_state;
		GPIO_WriteBit(GPIOB, GPIO_Pin_6, led_state ? Bit_SET : Bit_RESET);
		GPIO_WriteBit(GPIOB, GPIO_Pin_7, led_state ? Bit_RESET : Bit_SET );
		delay(10000);
	}
}


void delay( int a ) {
	volatile int i, j;

	for ( i = 0; i < a; i++ ) {
		j++;
	}
}
