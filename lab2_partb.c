/*
 * lab2_partb.c
 *
 * Created: 9/24/2021 12:00:45 AM
 * Author : cheny
 */ 
/*
#include <avr/io.h>

void  Initalize()
{
	DDRB &=~(0x01);
	DDRB |= 0x20;
}

int main(void)
{
	Initalize();
    /* Replace with your application code */
/*    while (1) 
    {
		if (PINB&(1<<PINB0))
		{
				PORTB|=(0x20);
		} 
		else
		{
			PORTB  &=~(0x20);
		}
		
    }
}*/

#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

/*--------------------Libraries---------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "inc/uart.h"

/*--------------------Variables---------------------------*/
char String[25];

/*-----------------------------------------------------------*/

int main(void)
{
	UART_init(BAUD_PRESCALER);

	while(1)
	{
		sprintf(String,"Hello world! \n");
		UART_putstring(String);
		_delay_ms(1000);

		sprintf(String,"The year is %u\n", 2020);
		UART_putstring(String);
		_delay_ms(1000);
	}
}
	

