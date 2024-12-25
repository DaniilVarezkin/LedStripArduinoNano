#include "Bluetooth.h"

AltSoftSerial BTserial;

void SendResponse(const char* response) {
    BTserial.print("<");
    BTserial.print(response);
    BTserial.print(">");
}

// void SendResponse(const char* responce){
//     BTserial.println(responce);

//     //Для логов
//     Serial.print("BTserial: ");
//     Serial.println(responce);
// }
