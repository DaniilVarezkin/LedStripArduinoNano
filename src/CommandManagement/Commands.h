#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include <Arduino.h>

#include "CommandWords.h"
#include "Effects/EffectsParam.h"  
#include "Effects/EffectsManager.h"
#include "Bluetooth/Bluetooth.h"
#include "ColorUtils/ConvertColorFuns.h"

void handleMode(const char *value);
void handleBrightness(const char *value);
void handleGradColor0(const char *value);
void handleGradColor1(const char *value);

#endif