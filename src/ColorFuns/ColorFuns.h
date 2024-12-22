#ifndef __COLOR_FUNS_H__
#define __COLOR_FUNS_H__

#include <FastLED.h>

CRGB hex2CRGB(const char* hex_color_s) {
    CRGB color = CRGB::Black; // Значение по умолчанию (черный)
    if (strlen(hex_color_s) == 6) {
        // Преобразуем строку в шестнадцатеричное число
        uint32_t hex_color = strtol(hex_color_s, NULL, 16);

        // Извлекаем компоненты R, G, B
        color.r = (hex_color >> 16) & 0xFF; // Старшие 8 бит
        color.g = (hex_color >> 8) & 0xFF;  // Средние 8 бит
        color.b = hex_color & 0xFF;         // Младшие 8 бит
    }
    return color;
}

void CRGB2hex(const CRGB crgb_color, char* hex_color) {
    // Формируем строку в формате RRGGBB
    sprintf(hex_color, "%02X%02X%02X", crgb_color.r, crgb_color.g, crgb_color.b);
}

#endif