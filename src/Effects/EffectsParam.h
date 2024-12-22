#ifndef __EFFECTS_PARAM_H__
#define __EFFECTS_PARAM_H__

#include <FastLED.h>
#include <stdint.h>

//  Константы настроек
#define LED_COUNT 40 
#define LED_DT 4   

extern struct CRGB leds[LED_COUNT];


//  Переменные настроек
extern uint8_t brightness;
extern int led_mode;

//  Служебные общие переменные 
extern uint8_t idex;
extern uint8_t ihue;
extern uint8_t isat;

//  Служебные переменные конкретного эффекта
extern uint8_t thishue;    //Оттенок эффекта
extern uint8_t thissat;    //Насыщеность
extern uint8_t thisstep;   //Шаг изменения цвета
extern uint8_t thisdelay;  //Задержка эффекта

//  Для эффекта камина
extern CHSV firecolor0;
extern CHSV firecolor1;

//  Просто для градиентов
extern CHSV gradcolor0;
extern CHSV gradcolor1;

#endif