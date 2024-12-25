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
    Serial.println("handleMode end");
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

        char hex_color[7];
        CRGB2hex(CRGB(gradcolor0), hex_color);

        sprintf(response, "%s=%s", CMD_GRADCOLOR0, hex_color);
        SendResponse(response);
    } else {
        gradcolor0 = rgb2hsv_approximate(hex2CRGB(value));
        change_mode(led_mode);
        SendResponse("OK");
    }
}

void handleGradColor1(const char *value) {
    if (strcmp(value, CMD_GET) == 0) {
        char response[16];

        char hex_color[7];
        CRGB2hex(CRGB(gradcolor1), hex_color);

        sprintf(response, "%s=%s", CMD_GRADCOLOR1, hex_color);
        SendResponse(response);
    } else {
        gradcolor1 = rgb2hsv_approximate(hex2CRGB(value));
        change_mode(led_mode);
        SendResponse("OK");
    }
}

