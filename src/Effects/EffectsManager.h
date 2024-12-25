#ifndef EFFECT_MANAGER_H
#define EFFECT_MANAGER_H
#include <FastLED.h>
#include <Perlin/Perlin2D.h>
#include <stdint.h>

#include "EffectsParam.h"   

#define FPS_TO_DELAY_MS(x) {1000/x}

void ChangeMode(int newmode);
void UpdateLeds();

//  Прототипы эффектов
void FillColor(uint8_t cred, uint8_t cgreen, uint8_t cblue);
void FillGradient(CHSV color0, CHSV color1);
void RainBowFade();
void RainBowSmooth();
void Fireplace();

// Служебные функции
CHSV ColorInGradient(CHSV color0, CHSV color1, float t);
void setPixel(int Pixel, byte red, byte green, byte blue);
byte * Wheel(byte WheelPos) ;


#endif // EFFECT_MANAGER_H