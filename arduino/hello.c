#include <stdio.h>
#include <avr/io.h>
#define F_CPU 16000000UL
#define BAUD 9600

#include <util/setbaud.h>

void uart_putchar(char c, FILE *stream)
{
    // bit of translation
    if (c == '\n')
    {
        uart_putchar('\r', stream);
    }
    // check that register is waiting on data
    loop_until_bit_is_set(UCSR0A, UDRE0);
    // UDR0 is the register where the next data byte goes
    UDR0 = c;
}

char uart_getchar(char c, FILE *stream)
{
    // Block until UDR0 has data
    loop_until_bit_is_set(UCSR0A, RXC0);
    // UDR0 is the register where the next data byte goes
    return UDR0;
}

FILE uart_out = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_in = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

void uart_init(void)
{
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;

    #if USE_2X
    UCSR0A |= _BV(U2X0);
    #else
    UCSR0A &= ~(_BV(U2X0));
    #endif

    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */


    stdin = &uart_in;
    stdout = &uart_out;
}




int main(void)
{
    uart_init();
    
	printf("test\n");
    int foo;
    scanf("%d\n", &foo);
    printf("%d is a number probably?\n");
	return 0;
}
