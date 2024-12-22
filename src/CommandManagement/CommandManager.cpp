#include "CommandManager.h"

char cmd_buf[32];

// Таблица обработки команд
Command commands[] = {
    {CMD_MODE, handleMode},
    {CMD_BRIGHTNESS, handleBrightness},
};

void processCommand(const char* command){
    Serial.print("Command Recived: ");
    Serial.println(command);

    char key[16];
    char value[16];

    const char* delimiter = strchr(command, KEY_VALUE_DELIMITER);
    if(delimiter == NULL){
        SendResponse("ERROR: delimiter not found");
        return;
    }

    size_t keyLength = delimiter - command;
    strncpy(key, command, keyLength);
    strcpy(value, delimiter + 1);
    key[keyLength] = '\0';

    //  Анализ ключей и значений
    

    // Поиск и выполнение соответствующего обработчика
    for (size_t i = 0; i < sizeof(commands) / sizeof(commands[0]); ++i) {
        if (strcmp(key, commands[i].key) == 0) {
            commands[i].handler(value);
            return;
        }
    }

    // Если команда не найдена
    SendResponse("Unknown Command");

}

void CheckCommands(){
    while (Serial.available())
    {
        memset(cmd_buf, 0, sizeof(cmd_buf));
        Serial.readBytesUntil(CMD_DELIMITER, cmd_buf, sizeof(cmd_buf));
        processCommand(cmd_buf);
    }
}