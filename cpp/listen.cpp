#include <tgbot/tgbot.h>
#include <iostream>

int main() {
    // Replace with your bot token
    std::string token = "YOUR_BOT_TOKEN_HERE";
    TgBot::Bot bot(token);

    // Handler for /start command
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hello! I'm listening on your Raspberry Pi!");
    });

    // Handler for any incoming message
    bot.getEvents().onAnyMessage([&bot](TgBot::Message::Ptr message) {
        std::cout << "Received message from " 
                  << (message->chat->username.empty() ? "unknown" : message->chat->username) 
                  << ": " << message->text << std::endl;

        // Optional: auto-reply
        bot.getApi().sendMessage(message->chat->id, "Message received: " + message->text);
    });

    std::cout << "Bot is now listening for messages..." << std::endl;

    // Long-polling loop
    try {
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            longPoll.start();
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

