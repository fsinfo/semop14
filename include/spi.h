#ifndef SPI_H
#define SPI_H

#include <avr/io.h>
#include <avr/interrupt.h>

#include "rgbhsv.h"
#include "animation.h"

union rgb_buffer {
	struct rgb_colour rgb[LED_COUNT];
	uint8_t data[LED_COUNT * 3];
};

enum output_state_t {
	OUTPUT_BUFFER1 = 0,
	FINISHED_BUFFER1 = 1,
	OUTPUT_BUFFER2 = 2,
	FINISHED_BUFFER2 = 3
};

extern volatile enum output_state_t output_state;
extern volatile uint16_t output_pos;
extern union rgb_buffer buffer1, buffer2;

void spi_init(void);
void spi_start_frame(void);


#endif