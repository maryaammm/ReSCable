import serial
from serial import Serial
import numpy as np
import requests


def telegram_bot_sendtext(bot_message):     #function to send message to telegram bot
    bot_token = '1739812273:AAGGBISpsBXKUPnPqIGXY4ZunJYHBq9KJpU'
    bot_chatID = '1419723957'
    send_text = 'https://api.telegram.org/bot' + bot_token + '/sendMessage?chat_id=' + bot_chatID + '&parse_mode=Markdown&text=' + bot_message

    response = requests.get(send_text)

    return response.json()

arduino_port = "COM9"        #serial port of Arduino
baud = 9600                  #arduino uno runs at 9600 baud
ser = serial.Serial(arduino_port, baudrate=baud)
print("Connected to Arduino port:" + arduino_port)

while(True):
    getData=str(ser.readline())      #to fetch data from arduino
    #print(getData)
    data=getData[2:-5]
    if(data=='a'):
        test = telegram_bot_sendtext("Hey, I turned your light OFF!!")
    if(data=='A'):
        test = telegram_bot_sendtext("Your heater is ON, Have a Good Day")

    print(data)


