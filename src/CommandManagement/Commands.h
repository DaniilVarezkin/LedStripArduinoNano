#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include <Arduino.h>

#include "CommandWords.h"
#include "Effects/EffectsParam.h"  
#include "Effects/EffectsManager.h"
#include "Bluetooth/Bluetooth.h"

void handleMode(const char *value);
void handleBrightness(const char *value);

#endif