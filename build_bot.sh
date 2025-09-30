#!/bin/bash

# Paths
TGCPP_INCLUDE=~/tgbot-cpp/include
TGCPP_LIB=~/tgbot-cpp/build

# Output binary
OUTPUT=bot

# Source file
SRC=/home/megatron/TelegramBot/cpp/send_msg.cpp

# Compile
g++ $SRC -o $OUTPUT \
    -I $TGCPP_INCLUDE \
    -L $TGCPP_LIB \
    -lTgBot -lcurl -lssl -lcrypto -lboost_system -lboost_thread \
    -std=c++17 -pthread

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful! Run './$OUTPUT' to start the bot."
else
    echo "Compilation failed."
fi

