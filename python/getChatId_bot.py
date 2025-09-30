from telegram.ext import Updater, MessageHandler, Filters

def get_chat_id(update, context):
    chat_id = update.effective_chat.id
    print(f"Your chat ID is: {chat_id}")
    update.message.reply_text(f"Got it! Your chat ID is: {chat_id}")

with open("/home/megatron/Documents/arduinoGigaBot_token.txt", "r") as f:
    telegram_token = f.read().strip()

updater = Updater(token=telegram_token)
dispatcher = updater.dispatcher

dispatcher.add_handler(MessageHandler(Filters.text, get_chat_id))

print("Bot is listening... Send a message to your bot now.")
updater.start_polling()
updater.idle()

