#include "CommandManager.h"



char cmd_buf[32];

// Таблица обработки команд
const Command commands[] = {
    {CMD_MODE, handleMode},
    {CMD_BRIGHTNESS, handleBrightness},
    {CMD_GRADCOLOR0, handleGradColor0},
    {CMD_GRADCOLOR1, handleGradColor1},
};

// Проверка сообщения на корректность формата
bool validateMessage(const char* message) {
    size_t length = strlen(message);

    // Проверка, что сообщение начинается с '<' и заканчивается на '>'
    if (length < 2 || message[0] != '<' || message[length - 1] != '>') {
        Serial.println("отсутствие скобок или слишком короткое сообщение");
        return false; // Некорректный формат: отсутствие скобок или слишком короткое сообщение
    }

    // Проверка наличия разделителя внутри скобок
    const char* delimiter = strchr(message, KEY_VALUE_DELIMITER);
    if (delimiter == NULL || delimiter <= message + 1 || delimiter >= message + length - 1) {
        Serial.println("Разделитель отсутствует");
        return false; // Разделитель отсутствует или находится вне диапазона
    }

    return true;
}


// Обработка команды
void processCommand(const char* command) {
    Serial.print("Command Received: ");
    Serial.println(command);

    // Проверка корректности формата команды
    if (!validateMessage(command)) {
        SendResponse(ERROR_MESSAGE);
        return;
    }

    // Убираем начальную и конечную скобки для дальнейшей обработки
    char cleanCommand[32];
    strncpy(cleanCommand, command + 1, strlen(command) - 2);
    cleanCommand[strlen(command) - 2] = '\0';

    char key[16];
    char value[16];


    // Разделение ключа и значения
    const char* delimiter = strchr(cleanCommand, KEY_VALUE_DELIMITER);
    size_t keyLength = delimiter - cleanCommand;
    strncpy(key, cleanCommand, keyLength);
    key[keyLength] = '\0';
    strcpy(value, delimiter + 1);

    Serial.print("Key:   ");Serial.println(key);
    Serial.print("Value: ");Serial.println(value);

    // Поиск и выполнение соответствующего обработчика
    for (size_t i = 0; i < sizeof(commands) / sizeof(commands[0]); ++i) {
        if (strcmp(key, commands[i].key) == 0) {
            commands[i].handler(value);
            SendResponse(SUCCESFULL_MESSAGE);
            return;
        }
    }

    // Если команда не найдена
    SendResponse(ERROR_MESSAGE);
}

// Чтение и обработка команд из Bluetooth
void CheckCommands() {
    while (BTserial.available()) {
        memset(cmd_buf, 0, sizeof(cmd_buf));
        size_t bytesRead = BTserial.readBytesUntil(CMD_DELIMITER, cmd_buf, sizeof(cmd_buf) - 1);

        // Если команда слишком длинная
        if (bytesRead >= sizeof(cmd_buf) - 1) {
            SendResponse(ERROR_MESSAGE);
            while ((BTserial.read() != CMD_DELIMITER) && BTserial.available()); // Очистка буфера
            continue;
        }

        cmd_buf[bytesRead] = '\0'; // Завершающий нуль для строки
        processCommand(cmd_buf);
        memset(cmd_buf, 0, sizeof(cmd_buf));
    }
    delay(50);
}