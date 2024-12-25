#include <Arduino.h>

#ifndef __UTILS_H__
#define __UTILS_H__

extern int __bss_end;
extern void *__brkval;

int memoryFree();
void printFreeMemory();

#endif