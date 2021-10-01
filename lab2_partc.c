/*
 * lab2_partc.c
 *
 * Created: 9/24/2021 11:08:00 AM
 * Author : cheny
 */ 


#define F_CPU 16000000UL
#define BAUD_RATE 9600
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

volatile int edge1=0;
volatile int edge2=0;
volatile int period =0;
volatile int flag =0;


void Initalize()
{
	cli();
	DDRB &= ~(1<<DDB0);
	DDRB |=(DDRB<<0x5);
	
	
	TCCR1B &=~ (1<<CS10);
	TCCR1B |= (1<<CS11);
	TCCR1B &=~ (1<<CS12);
	
	TCCR1A &= ~(1<<WGM10);
	TCCR1A &= ~(1<<WGM11);
	TCCR1B &= ~(1<<WGM12);
	TCCR1B &= ~(1<<WGM13);
	
	TCCR1B |= (1<<ICES1);
	
	TIFR1 |= (1<<ICF1);
	
	TIMSK1 |= (1<<ICIE1);
	
	
	sei();
}


ISR(TIMER1_CAPT_vect)
{
	period=ICR1-edge2;
	
	if(flag ==1)
	{
		PORTB&=~(0x20);
	}
	else
	{
		PORTB |=(0x20);
	}
	//PORTB ^=(0x20);
	
	flag^=1;
	TCCR1B^=(1<<ICES1);
	edge1=ICR1;	
	
}

int main(void)
{
	
	Initalize();
    while (1) 
    {
		}
}
