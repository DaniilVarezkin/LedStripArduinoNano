#include <Arduino.h>
#include "Effects/EffectsManager.h"
#include "CommandManagement/CommandManager.h"
#include "Bluetooth/Bluetooth.h"


#define BAUD_RATE 38400

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
   Serial.begin(BAUD_RATE);

   Serial.print("Sketch:   ");   Serial.println(__FILE__);
   Serial.print("Uploaded: ");   Serial.println(__DATE__);
   Serial.println(" ");

   BTserial.begin(BAUD_RATE);


   ChangeMode(7); 

   LEDS.setBrightness(brightness);  
   LEDS.addLeds<WS2811, LED_DT, BRG>(leds, LED_COUNT);
   LEDS.show();                     
}

//long long timer = 0;

void loop() {

//   if(millis() - timer > 1000){
//     timer = millis();
//     Serial.print("Memory free: ");
//     Serial.println(memoryFree());
//   }


  CheckCommands();

  UpdateLeds();
}

