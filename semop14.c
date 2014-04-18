#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "rgbhsv.h"
#include "animation.h"

struct hsv_colour source[100];
struct rgb_colour buffer1[100], buffer2[100];

// Output state:
// 0: Started, output buffer 1
// 1: Wait for renderer to be rendering
// 2: output buffer 2
// 3: Wait for renderer to be rendering
volatile uint8_t output_state = 0;
uint16_t output_pos = 0; // 0 to 299

void renderer(void) {
	uint8_t i = 0;
	
	while(true) {
		anim_frame(source, 100);
		
		for(i = 0; i < 100; i++)
			inp_hsv2rgb(source + i, buffer2 + i);
		
		while(output_state != 1) {}
		// todo: inter-frame pause for LEDs
		output_state = 2;
		// todo: start output of buffer2
		
		anim_frame(source, 100);
		
		for(i = 0; i < 100; i++)
			inp_hsv2rgb(source + i, buffer1 + i);
		
		while(output_state != 3) {}
		// todo: inter-frame pause for LEDs
		output_state = 0;
		// todo: start output of buffer1
	}
}

int main(void) {
	//setup();
	
	//sei();
	
	renderer();
	
	return 0;
}


