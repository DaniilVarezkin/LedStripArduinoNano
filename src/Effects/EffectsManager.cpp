#include "EffectsManager.h"

struct CRGB leds[LED_COUNT];


//  Переменные настроек

uint8_t brightness = 128;


//  Служебные общие переменные 
int led_mode = 0;
uint8_t idex = 0;
uint8_t ihue = 0;
uint8_t isat = 255;

Perlin::Perlin2D perlin;
long long ledUpdateTimer = 0;




//  Служебные переменные конкретного эффекта
uint8_t thishue;    //Оттенок эффекта
uint8_t thissat;    //Насыщеность
uint8_t thisstep;   //Шаг изменения цвета
uint8_t thisdelay;  //Задержка эффекта

//  Для эффекта камина
CHSV firecolor0 = CHSV(0, 255, 240);
CHSV firecolor1 = CHSV(24, 220, 255);

//  Просто для градиентов
CHSV gradcolor0 = CHSV(167, 255, 255);
CHSV gradcolor1 = CHSV(90, 255, 255);


void ChangeMode(int newmode){
    thissat = 255;
    switch (newmode) //Настройка переменных конкретного эффекта
    {
        case 0: FillColor(0, 0, 0); LEDS.show();          break;          // Пауза, залить всё черным
        case 1: FillColor(255, 255, 255); LEDS.show();    break;          // Всё белым
        case 2: FillGradient(gradcolor0, gradcolor1); LEDS.show(); break; // Заливка градиентом
        
        case 5: thisdelay = FPS_TO_DELAY_MS(25);    break; // RainBowFade
        case 6: thisdelay = FPS_TO_DELAY_MS(25);    break; // RainBowSmooth
        case 7: thisdelay = FPS_TO_DELAY_MS(25);    break; // Fireplace
        
        default: break;
    }
    led_mode = newmode;
}



void UpdateLeds(){
  if((millis() - ledUpdateTimer) > thisdelay)
  {
    switch (led_mode)
    {
        case 5: RainBowFade();  break;
        case 6: RainBowSmooth();  break;
        case 7: Fireplace();  break;

        default: break;
    }
  }
}
void FillColor(uint8_t cred, uint8_t cgreen, uint8_t cblue){
  for (int i = 0 ; i < LED_COUNT; i++ ) {
    leds[i].setRGB( cred, cgreen, cblue);
  }
}

void FillGradient(CHSV color0, CHSV color1){
  for(int idex = 0; idex < LED_COUNT; idex++){
    leds[idex] = ColorInGradient(color0, color1, (float)idex / LED_COUNT);
  }
}

void RainBowFade(){
    ihue++;
    for(int idex = 0; idex < LED_COUNT; idex++){
        leds[idex] = CHSV(ihue, thissat, 255);
    }
    LEDS.show();
}


void RainBowSmooth(){

    byte *c;
    uint16_t i;
    static uint16_t j;

    if(j < 256 * 5){
        j++;
        for (i = 0; i < LED_COUNT; i++) {
            c = Wheel(((i * 256 / LED_COUNT) + j) & 255);
            setPixel(i, *c, *(c + 1), *(c + 2));
        }
    } else j = 0;
    FastLED.show();
}

char charByX(float x) {
    static String alf = " .~+=#O$%";
    
    // Проверим на крайние значения
    if (x < 0) return alf[0];
    if (x > 255) return alf[alf.length() - 1];
    
    // Нормализуем значение x в диапазон от 0 до 9 (индексы строки alf)
    int index = (x * (alf.length() - 1)) / 255;
    return alf[index];
}

void Fireplace(){
  static float y = 0;
  y += 0.15;
  for (int x = 0; x < LED_COUNT; x++){
    float t = perlin.fNoise(x*0.15, y);
    float normalized_t = (t + 1) /2.0;  // Нормализуем в диапазон от 0 до 1

    //Serial.print(charByX(255.0 * normalized_t)); 

    leds[x] = ColorInGradient(firecolor0, firecolor1, normalized_t);
  }
  //Serial.println();
  LEDS.show();
}


// Служебные функции

CHSV ColorInGradient(CHSV color0, CHSV color1, float t){
  if(t < 0.0) t = 0.0;
  else if (t > 1.0) t = 1.0;

  return CHSV(
    color1.h * t + color0.h * (1 - t),
    color1.s * t + color0.s * (1 - t),
    color1.v * t + color0.v * (1 - t)
  );
}


void setPixel(int Pixel, byte red, byte green, byte blue) {
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
}

byte * Wheel(byte WheelPos) {
  static byte c[3];

  if (WheelPos < 85) {
    c[0] = WheelPos * 3;
    c[1] = 255 - WheelPos * 3;
    c[2] = 0;
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    c[0] = 255 - WheelPos * 3;
    c[1] = 0;
    c[2] = WheelPos * 3;
  } else {
    WheelPos -= 170;
    c[0] = 0;
    c[1] = WheelPos * 3;
    c[2] = 255 - WheelPos * 3;
  }

  return c;
}