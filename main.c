#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "include/spi.h"

int main(void) {


	spi_init();

	while(1) {
		
		uint8_t i;
		for(i = 0; i < 100; i++) {
			spi_write_byte(0x00);
			spi_write_byte(0xFF);
			spi_write_byte(0x80);
		}
		_delay_ms(1);
	}


}