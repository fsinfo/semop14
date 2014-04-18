#include "spi.h"


void spi_init(void) {
	// Set MOSI and SCK output, all others input
	DDRB = (1<<PB3) | (1<<PB5) | (1<<PB2);
	// Enable SPI, Master, Clockrate fck/4, LSB first
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<CPOL) | (1<<SPR0)| (1 << DORD);
	// double spi speed for fck/2
	SPSR |= (1 << SPI2X);
}


void spi_write_byte(uint8_t data) {
	SPDR = data;
	while(!(SPSR & (1<<SPIF)));
}