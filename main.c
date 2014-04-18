#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "include/spi.h"
#include "include/rgbhsv.h"
#include "include/animation.h"

struct hsv_colour source[100];
union rgb_buffer buffer1, buffer2;

// Output state:
// 0: Started, output buffer 1
// 1: Wait for renderer to be rendering
// 2: output buffer 2
// 3: Wait for renderer to be rendering
volatile uint8_t output_state = 1;
uint16_t output_pos = 0; // 0 to 299

void sleep_us(uint16_t timeout) {
	while(timeout > 0) {
		timeout--;
		_delay_us(1);
	}
}

void renderer(void) {
	uint16_t i = 0;

	//anim_frame(source, 100);

	while(true) {
		
		anim_frame(source, 100);
		
		for(i = 0; i < 100; i++)
			inp_hsv2rgb(source + i, buffer1.rgb + i);
		


		while(output_state != 1) {}
		sleep_us(500);
		output_state = 2;
		spi_start_frame();
		
		
		anim_frame(source, 100);
		
		for(i = 0; i < 100; i++)
			inp_hsv2rgb(source + i, buffer2.rgb + i);
		


		while(output_state != 3) {}
		sleep_us(500);
		output_state = 0;
		spi_start_frame();
	}
}

int main(void) {
	spi_init();
	
	sei();
	
	renderer();
	
	return 0;
}


