#ifndef SPI_H
#define SPI_H

#include <avr/io.h>
#include <avr/interrupt.h>

#include "rgbhsv.h"

union rgb_buffer {
	struct rgb_colour rgb[100];
	uint8_t data[300];
};

extern volatile uint8_t output_state;
extern uint16_t output_pos;
extern union rgb_buffer buffer1, buffer2;
extern uint8_t output_color;

void spi_init(void);
void spi_start_frame(void);


#endif