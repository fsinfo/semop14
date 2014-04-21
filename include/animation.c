
#include <stdlib.h>

#include "animation.h"

// Number of Animation
// 0: Simple moving colour spectrum
// 1: colour and brightness wave specifically built for banner LED layout
#define ANIMATION 1

#if ANIMATION == 0
// Simple HSV HUE Wave
void anim_frame(struct hsv_colour frame[]) {
	static uint8_t t = 0;
	
	uint8_t i = 0;
	for(i = 0; i < LED_COUNT; i++) {
		frame[i] = (struct hsv_colour) {t + i, 0xff, 0xff};
	}
	
	t++;
}
#endif

#if ANIMATION == 1
// Sweeep

// larger -> slower
#define anim_speed 5

// Macros for hue and value(brightness) depending on the time(t) and position(i)
#define h(t, i) ((t / 32)-i)
//#define v(t, i) (126 + abs(((uint8_t) (t - (i * 3))) - 127))

/*
#define v(t, i) \
((abs((t % (128 * anim_speed)) - (64 * anim_speed))) / (anim_speed * 5)) == i / 5 \
? 0xff \
: 0
*/

uint8_t v(uint16_t t, uint8_t i) {
	uint8_t lightpos = (t / anim_speed)  % 64;
	uint8_t dist = abs(i - lightpos);
	if(dist > 3) {
		return 0x00;
	}
	return  0xff;
}




// LED colour depending on time and pos.
#define c(t, i) (struct hsv_colour) {h(t, i), 0xff, v(t, i)}

void anim_frame(struct hsv_colour frame[]) {
	static uint16_t t = 0; // time ticks
	
	frame[0] = c(t, 5);
	
	frame[1] = c(t, 2);
	
	frame[2] =
	frame[3] =
	frame[4] =
	frame[5] = c(t, 0);
	
	frame[6] = c(t, 3);

	frame[49] =
	frame[48] =
	frame[50] =
	frame[51] =
	frame[52] = 
	frame[7]  = c(t, 6);

	frame[47] =
	frame[53] =
	frame[8]  = c(t, 9);

	frame[46] =
	frame[54] =
	frame[9]  = c(t, 12);

	frame[45] =
	frame[55] =
	frame[10] = c(t, 15);

	frame[44] =
	frame[56] =
	frame[11] = c(t, 18);

	frame[43] =
	frame[57] =
	frame[12] = c(t, 21);
	
	frame[42] =
	frame[58] =
	frame[13] = c(t, 24);

	frame[41] =
	frame[59] =
	frame[14] = c(t, 27);

	frame[40] =
	frame[60] =
	frame[15] = c(t, 30);

	frame[39] =
	frame[61] =
	frame[16] = c(t, 33);

	frame[38] =
	frame[62] =
	frame[17] = c(t, 36);

	frame[37] =
	frame[63] =
	frame[18] = c(t, 39);

	frame[36] =
	frame[64] =
	frame[19] = c(t, 42);

	frame[35] =
	frame[65] =
	frame[20] = c(t, 45);

	frame[34] =
	frame[66] =
	frame[21] = c(t, 48);

	frame[33] =
	frame[67] =
	frame[22] = c(t, 51);

	frame[32] =
	frame[68] =
	frame[69] =
	frame[23] = c(t, 54);

	frame[31] =
	frame[70] =
	frame[71] =
	frame[24] = c(t, 57);

	frame[30] =
	frame[25] = c(t, 60);

	frame[26] =
	frame[27] =
	frame[28] =
	frame[29] = c(t, 63);

	//Leds used to spell the date should not blink
	uint8_t k;
	for(k = 72; k < 100; k++) {
		frame[k] = (struct hsv_colour) {h(t, 63), 0xff, 0x80};
	}	
	



	t = (t + 1) % 8192;
}
#endif

