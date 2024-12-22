#ifndef __COMMAND_MANAGER_H__
#define __COMMAND_MANAGER_H__

#include "CommandWords.h"
#include "Commands.h"

#include "Effects/EffectsParam.h"  
#include "Effects/EffectsManager.h"

typedef struct {
    const char *key;
    void (*handler)(const char *value);
} Command;
void CheckCommands();


#endif