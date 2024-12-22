#include "Commands.h"




void handleMode(const char *value) {
    if (strcmp(value, CMD_GET) == 0) {
        char response[16];
        sprintf(response, "%s=%d", CMD_MODE, led_mode);
        SendResponse(response);
    } else {
        change_mode(atoi(value));
        SendResponse("OK");
    }
}

void handleBrightness(const char *value) {
    if (strcmp(value, CMD_GET) == 0) {
        char response[16];
        sprintf(response, "%s=%d", CMD_BRIGHTNESS, brightness);
        SendResponse(response);
    } else {
        int new_brightness = atoi(value);
        new_brightness = constrain(new_brightness, 0, 255);
        brightness = new_brightness;
        SendResponse("OK");
    }
}

void handleGradColor0(const char *value) {
    if (strcmp(value, CMD_GET) == 0) {
        char response[16];
        sprintf(response, "%s=%d", CMD_GRADCOLOR0, brightness);
        SendResponse(response);
    } else {
        int new_brightness = atoi(value);
        new_brightness = constrain(new_brightness, 0, 255);
        brightness = new_brightness;
        SendResponse("OK");
    }
}

