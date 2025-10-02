#include <tgbot/tgbot.h>
#include <iostream>
#include <fstream>
#include <string>

int main() {
    // Replace with your bot token
    std::ifstream f("/home/megatron/Documents/arduinoGigaBot_token.txt");
    if(!f.is_open())
    {
     std::cerr<<"failed to open file"<<std::endl;
    }
    else {
     std::cout<<"file opened"<<std::endl;
    }
    
    std::string token;
    
    std::getline(f,token);
    //std::cout<<"token: "<<token<<std::endl;

    int64_t chatId = -4885874152; // your chat ID
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

   // std::cout << "Bot is now listening for messages..." << std::endl;

    // Long-polling loop
    try {
        TgBot::TgLongPoll longPoll(bot);
        while (true) {
            longPoll.start();
	    std::cout<< "polling telegram"<<std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    f.close();
    return 0;
}

