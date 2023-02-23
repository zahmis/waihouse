from switchbot import SwitchBot
import os

# SwitchBot APIのトークンを設定します
TOKEN =os.environ['SWITCH_TOKEN']
SECRET=os.environ['SWITCH_SECRET']

client = SwitchBot(TOKEN, SECRET)

device_id = 'A848FAE383EE'
device = client.device(id=device_id)

device.command('turn_off')