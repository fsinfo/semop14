#include "spi.h"


void spi_init(void) {
	// Set MOSI and SCK output, all others input
	DDRB = (1<<PB3) | (1<<PB5) | (1<<PB2);
	// Enable SPI, Enable Interrupt, Clockspeed fck/16, Master
	SPCR = (1<<SPE) | (1 << SPIE) | (1<<SPR0) | (1<<MSTR);
	// double spi speed for fck/8
	SPSR |= (1 << SPI2X);
}

void spi_start_frame(void) {
	if(output_state == 0 || output_state == 2) {
		switch(output_state) {
		case 0:
			SPDR = buffer1.data[0];
			break;
		case 2:
			SPDR = buffer2.data[0];
			break;
		default:
			break;
		}
		output_pos = 1;
	}
}


ISR(SPI_STC_vect) {
	if(output_state == 0 || output_state == 2) {
		if(output_pos < LED_COUNT*3) {
			switch(output_state) {
			case 0:
				SPDR = buffer1.data[output_pos];
				break;
			case 2:
				SPDR = buffer2.data[output_pos];
				break;
			default:
				break;
			}
			output_pos++;
		}
		else {
			output_state++;
		}
	}
}