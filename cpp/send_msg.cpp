#include <tgbot/tgbot.h>
#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Read token from file
    std::ifstream f("/home/megatron/Documents/arduinoGigaBot_token.txt");
    std::string token;
    std::getline(f, token);

    TgBot::Bot bot(token);

    // Example: send a message
    int64_t chatId = -4885874152; // your chat ID
    bot.getApi().sendMessage(chatId, "Hello from Raspberry Pi C++ bot!");

    std::cout << "Message sent!" << std::endl;
}

