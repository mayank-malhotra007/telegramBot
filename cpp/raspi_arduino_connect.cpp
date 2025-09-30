
#include<iostream>
#include<termios.h>
#include<fcntl.h>
#include<unistd.h>
#include<cstring>
#include<csignal>
#include<tgbot/tgbot.h>
#include<fstream>

int main()
{

 int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
 if(fd<0)
 {
  perror("open");
  return -1;
 }

 termios tty{};
 tcgetattr(fd, &tty);
 cfsetospeed(&tty, B9600);
 cfsetispeed(&tty, B9600);
 cfmakeraw(&tty);
 tcsetattr(fd, TCSANOW, &tty);


 std::cout<<"connected with arduino gigaR1"<<std::endl;
 
 //logic to send a msg via telegram
 std::ifstream f("/home/megatron/Documents/arduinoGigaBot_token.txt");
 std::string token;
 std::getline(f, token);

 TgBot::Bot bot(token);
 
 int64_t chatId = -4885874152;

 bot.getApi().sendMessage(chatId, "Raspi connected with Arduino GigaR1 via Serial");
 std::cout<<"msg sent"<<std::endl;



 close(fd);
 return 0;
}


