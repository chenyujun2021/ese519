/*
 * lab2_partd.c
 *
 * Created: 9/27/2021 9:13:41 PM
 * Author : cheny
 */ 


#define F_CPU 16000000UL
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "uart.h"


char String[25];
volatile long edge1=0;
volatile long period =0;
volatile int counter =0;


void Initalize()
{
	cli();
	DDRB &= ~(1<<DDB0);
	DDRB |=(0x20);
	
	TCCR1B |=(1<<CS10);
	TCCR1B &=~(1<<CS11);
	TCCR1B &=~(1<<CS12);
	
	TCCR1A &= ~(1<<WGM10);
	TCCR1A &= ~(1<<WGM11);
	TCCR1B &= ~(1<<WGM12);
	TCCR1B &= ~(1<<WGM13);
	
	TCCR1B &=~(1<<ICES1);
	
	TIFR1 |= (1<<ICF1);
	
	TIMSK1 |= (1<<ICIE1);
	
	TIMSK1 |=(1<< TOIE1);
	
	sei();
}


ISR(TIMER1_CAPT_vect)
{
	if(edge1==0)
	{
		edge1=counter*65536+TCNT1;
		if((edge1 > 6400000))
		{
			sprintf(String, "space \t \n");
			UART_putstring(String);
		}
	}
	else
	{
		//period=ICR1-edge1+counter*(2^16);
		period=counter*65536-edge1+TCNT1;
		//sprintf(String, "period is %ld \n ", period);
		//UART_putstring(String);
		if ((period>480000) && (period<3200000))
		{
			sprintf(String, "dot . \n");
			UART_putstring(String);
		}
		else if ((period>320000) && (period<6400000))
		{
			sprintf(String, "dash -\n");
			UART_putstring(String);
		}
		counter =0;
		edge1=0;
	}
	cli();
	TCCR1B^=(1<<ICES1);
	sei();
}

ISR(TIMER1_OVF_vect)
{
	
	counter++;
	
}

int main(void)
{
	UART_init(BAUD_PRESCALER);
	Initalize();
    while (1) 
    {
		
    }
}
		
	


