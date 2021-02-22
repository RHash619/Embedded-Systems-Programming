#include <asf.h>

#include <avr/io.h>

#include <avr/interrupt.h>

#include <avr/delay.h>

#define F_CPU	16000000

#define BAUD	9600

#define find_baud		(F_CPU/16/BAUD)-1 // Finds the correct BAUD for the USART



usart_transmit (unsigned char data){

	while (!(UCSR0A & (1<<UDRE0)));

	UDR0 = data;

}

//set to asyn

int main (void)

{

	UBRR0H = (find_baud >> 8);  //sets baud rate

	UBRR0L = find_baud;

	UCSR0B = (1<<RXEN0) | (1<<TXEN0);	// RXE=1 can receive data, TXE= 1 data read

	UCSR0C = (1<< USBS0) | (1<<UCSZ00) | (1<<UCSZ01);



	while(1){

		unsigned char input[10] = "817817176\n";	//write this register to transmit

		for (int i = 0; i<11;i++){

			usart_transmit(input[i]);

			_delay_ms(500);

		}



	}

}

