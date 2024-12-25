#include "Commands.h"

void handleMode(const char *value) {
    if (strcmp(value, CMD_GET) == 0) {
        char response[16];
        sprintf(response, "%s=%d", CMD_MODE, led_mode);
        SendResponse(response);
    } else {
        ChangeMode(atoi(value));
        delay(10);
        SendResponse("OK");
        
    }
}

void handleBrightness(const char *value) {
    if (strcmp(value, CMD_GET) == 0) {
        char response[16];
        int brightness = FastLED.getBrightness();
        sprintf(response, "%s=%d", CMD_BRIGHTNESS, brightness);
        SendResponse(response);
    } else {
        int new_brightness = atoi(value);
        new_brightness = constrain(new_brightness, 0, 255);
        FastLED.setBrightness(new_brightness);
        delay(10);
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
        ChangeMode(led_mode);
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
        ChangeMode(led_mode);
        SendResponse("OK");
    }
}

