#include "rgbhsv.h"

struct hsv_colour rgb2hsv(uint8_t red, uint8_t green, uint8_t blue) {
	return (struct hsv_colour) {0,0,0};
}

void inp_hsv2rgb(struct hsv_colour *in, struct rgb_colour *out) {
	*out = (struct rgb_colour) {0,0,0};

	if(in->saturation == 0) {
		out->red = out->green = out->blue = in->value;
	} else {
		uint16_t hi = (in->hue * 6) / 256,
		         f = (((in->hue * 6) % 256) / 6);
		uint16_t p = (in->value * (255 - in->saturation)) / 256,
		         q = (in->value * (((42 * 255) - in->saturation * f) / 42)) / 256,
		         t = (in->value * (((42 * 255) - in->saturation * (42 - f)) / 42)) / 256;
		switch(hi) {
			case 0: *out = (struct rgb_colour) {in->value, t, p}; break;
			case 1: *out = (struct rgb_colour) {q, in->value, p}; break;
			case 2: *out = (struct rgb_colour) {p, in->value, t}; break;
			case 3: *out = (struct rgb_colour) {p, q, in->value}; break;
			case 4: *out = (struct rgb_colour) {t, p, in->value}; break;
			case 5: *out = (struct rgb_colour) {in->value, p, q}; break;
		}
	}
}
struct rgb_colour hsv2rgb(uint8_t hue, uint8_t saturation, uint8_t value) {
	struct rgb_colour ret = {0,0,0};

	if(saturation == 0) {
		ret.red = ret.green = ret.blue = value;
	} else {
		uint16_t hi = (hue * 6) / 256,
		         f = (((hue * 6) % 256) / 6);
		uint16_t p = (value * (255 - saturation)) / 256,
		         q = (value * (((42 * 255) - saturation * f) / 42)) / 256,
		         t = (value * (((42 * 255) - saturation * (42 - f)) / 42)) / 256;
		switch(hi) {
			case 0: ret = (struct rgb_colour) {value, t, p}; break;
			case 1: ret = (struct rgb_colour) {q, value, p}; break;
			case 2: ret = (struct rgb_colour) {p, value, t}; break;
			case 3: ret = (struct rgb_colour) {p, q, value}; break;
			case 4: ret = (struct rgb_colour) {t, p, value}; break;
			case 5: ret = (struct rgb_colour) {value, p, q}; break;
		}
	}

	return ret;
}
