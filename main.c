#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "include/spi.h"
#include "include/rgbhsv.h"
#include "include/animation.h"

struct hsv_colour source[LED_COUNT];
union rgb_buffer buffer1, buffer2;

volatile enum output_state_t output_state = FINISHED_BUFFER1;
volatile uint16_t output_pos = 0; // 0 to 299

void sleep_us(uint16_t timeout) {
	while(timeout > 0) {
		timeout--;
		_delay_us(1);
	}
}

void renderer(void) {
	uint16_t i = 0;

	while(true) {
		
		anim_frame(source);
		
		for(i = 0; i < LED_COUNT; i++)
			inp_hsv2rgb(source + i, buffer2.rgb + i);
		

		while(output_state != FINISHED_BUFFER1) {}
		//Output buffer2, render into buffer1
		sleep_us(500);
		output_state = OUTPUT_BUFFER2;
		spi_start_frame();
		
		
		anim_frame(source);
		
		for(i = 0; i < LED_COUNT; i++)
			inp_hsv2rgb(source + i, buffer1.rgb + i);
		

		while(output_state != FINISHED_BUFFER2) {}
		//Output buffer1, render into buffer2
		sleep_us(500);
		output_state = OUTPUT_BUFFER1;
		spi_start_frame();
	}
}

int main(void) {
	spi_init();
	
	sei();
	
	renderer();
	
	return 0;
}


