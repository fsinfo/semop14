#ifndef RGBHSV_H
#define RGBHSV_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


struct rgb_colour {uint8_t red, green, blue;};
struct hsv_colour {uint8_t hue, saturation, value;};

struct hsv_colour rgb2hsv(uint8_t red, uint8_t green, uint8_t blue);
struct rgb_colour hsv2rgb(uint8_t hue, uint8_t saturation, uint8_t value);

// in-place version
void inp_hsv2rgb(struct hsv_colour *in, struct rgb_colour *out);

#endif /* RGBHSV_H */
