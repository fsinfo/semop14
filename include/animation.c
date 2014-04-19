#include "animation.h"


// ANIMATION:
void anim_frame(struct hsv_colour frame[]) {
	static uint8_t t = 0;
	
	uint8_t i = 0;
	for(i = 0; i < LED_COUNT; i++) {
		frame[i] = (struct hsv_colour) {t + i, 0xff, 0xff};
	}
	
	t++;
}
