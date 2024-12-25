#ifndef __BLUETOOTH_H__
#define __BLUETOOTH_H__

#include <Arduino.h>
#include <AltSoftSerial.h>

extern AltSoftSerial BTserial;

void SendResponse(const char* responce);

#endif
