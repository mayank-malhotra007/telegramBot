#include <tgbot/tgbot.h>
#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

int main() {
    // Open serial port
    int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // Configure serial
    termios tty{};
    if (tcgetattr(fd, &tty) != 0) {
        perror("tcgetattr");
        close(fd);
        return 1;
    }

    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);
    cfmakeraw(&tty);

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("tcsetattr");
        close(fd);
        return 1;
    }

    // Telegram Bot
    
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
   
    TgBot::Bot bot(token);
    int64_t chatId = -4885874152; // your chat ID
    
    // Start message
    bot.getEvents().onCommand("start", [&bot](TgBot::Message::Ptr message) {
        bot.getApi().sendMessage(message->chat->id, "Hello! I'm listening on your Raspberry Pi!");
    });

    // Any incoming message
    bot.getEvents().onAnyMessage([&bot, fd](TgBot::Message::Ptr message) {
        std::cout << "Received message from "
                  << (message->chat->username.empty() ? "unknown" : message->chat->username)
                  << ": " << message->text << std::endl;

        if (message->text == "ON") {
            write(fd, "ON\n", strlen("ON\n"));
            bot.getApi().sendMessage(message->chat->id, "Turning ON");
        } else if (message->text == "OFF") {
            write(fd, "OFF\n", strlen("OFF\n"));
            bot.getApi().sendMessage(message->chat->id, "Turning OFF");
        }
    });

    // Long polling loop
    try {
        TgBot::TgLongPoll longPoll(bot);
        std::cout << "Bot started successfully!" << std::endl;
        while (true) {
            longPoll.start();
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    f.close();
    close(fd);
    return 0;
}

