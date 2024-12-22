#ifndef __COLOR_FUNS_H__
#define __COLOR_FUNS_H__

#include <FastLED.h>

CRGB hex2CRGB(const char* hex_color_s);
void CRGB2hex(const CRGB crgb_color, char* hex_color);

#endif