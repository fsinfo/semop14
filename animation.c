#include "rgbhsv.h"

// ANIMATION:
void anim_frame(struct hsv_colour frame[], uint16_t length) {
	static uint8_t t = 0;
	
	uint8_t i = 0;
	for(i = 0; i < length; i++) {
		frame[i] = (struct hsv_colour) {t + i, 0xff, 0xff};
	}
	
	t++;
}
