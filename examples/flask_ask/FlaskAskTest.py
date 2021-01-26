#!/usr/bin/env python3
# Derived from examples in the Flask-Ask repo: https://github.com/johnwheeler/flask-ask

from flask import Flask
from flask_ask import Ask, statement

app = Flask(__name__)
ask = Ask(app, '/')

@ask.intent('StandUp')
def stand_up():
    speech_text = 'Standing up'
    return statement(speech_text).simple_card('My Robot', speech_text)

@ask.intent('LayDown')
def law_down():
    speech_text = 'Laying down'
    return statement(speech_text).simple_card('My Robot', speech_text)

if __name__ == '__main__':
    app.run()
