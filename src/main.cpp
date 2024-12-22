#include <Arduino.h>
#include "Effects/EffectsManager.h"
#include "CommandManagement/CommandManager.h"
#include "ColorFuns/ColorFuns.h"
extern int __bss_end;
extern void *__brkval;

int memoryFree()
{
   int freeValue;
   if((int)__brkval == 0)
      freeValue = ((int)&freeValue) - ((int)&__bss_end);
   else
      freeValue = ((int)&freeValue) - ((int)__brkval);
   return freeValue;
}



void setup() {
  Serial.begin(9600);


  change_mode(7); 

  LEDS.setBrightness(brightness);  
  LEDS.addLeds<WS2811, LED_DT, BRG>(leds, LED_COUNT);
  LEDS.show();                     
}

//long long timer = 0;

void loop() {

  // if(millis() - timer > 1000){
  //   timer = millis();
  //   Serial.print("Memory free: ");
  //   Serial.println(memoryFree());
  // }


  CheckCommands();

  update_leds();
}

