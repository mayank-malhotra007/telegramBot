#include <tgbot/tgbot.h>
#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

int arduinoPortSetup(const char* terminal_path)
{

    int fd = open(terminal_path, O_RDWR | O_NOCTTY);
    if(fd<0){
    
    // Open serial port
        perror("open");
        return -1;
    }

    // Configure serial
    termios tty{};
    if (tcgetattr(fd, &tty) != 0) {
        perror("tcgetattr");
        close(fd);
        return -1;
    }

    cfsetospeed(&tty, B9600);
    cfsetispeed(&tty, B9600);
    cfmakeraw(&tty);

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("tcsetattr");
        close(fd);
        return- 1;
    }

    //upon success, return fd
    return fd;
}


// ----- Telegram Token Fetch ------
std::string getTelegramToken(std::string path)
{
    //open the file
    std::ifstream f(path);
   
    if(!f.is_open())
    {
     std::cerr<<"failed to open file"<<std::endl;
    }
    else {
     std::cout<<"file opened"<<std::endl;
    }
    
    std::string token;
    std::getline(f,token);
   
    //close the file
    f.close();
    return token;

}



// **** MAIN ****** 
int main() {
   
    //Open the serial port at arduino
    const char* terminal_path = "/dev/ttyACM0";
    int fd = arduinoPortSetup(terminal_path);
   
    if(fd){
    	std::cout<<"raspi arduino port connected"<<std::endl;
    }else {
        std::cout <<"port not connected"<<std::endl;
    }


    //Fetch telegram token
    std::string path_to_token = "/home/megatron/Documents/arduinoGigaBot_token.txt";
    std::string tk = getTelegramToken(path_to_token);
    std::cout<<"token: "<<tk<<std::endl;

    // pass token to bot object, constructor call
    TgBot::Bot bot(tk);

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


    // poll the telegram API for messages
    try {
        TgBot::TgLongPoll longPoll(bot);
        std::cout << "Bot started successfully!" << std::endl;
        while (true) {
            longPoll.start();
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

   
    close(fd);
    return 0;
}

