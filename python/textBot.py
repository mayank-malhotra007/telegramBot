from telegram import Bot

with open("/home/megatron/Documents/arduinoGigaBot_token.txt", "r") as f:
    telegram_token = f.read().strip()

bot = Bot(token=telegram_token)

# Use the chat ID you got from the step above
chat_id =  -4885874152
bot = Bot(token=telegram_token)
bot.send_message(chat_id=chat_id, text="Hello from Raspberry Pi!")

