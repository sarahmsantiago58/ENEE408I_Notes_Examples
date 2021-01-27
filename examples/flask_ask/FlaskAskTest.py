#!/usr/bin/env python3
# Derived from examples in the Flask-Ask repo: https://github.com/johnwheeler/flask-ask

from flask import Flask
from flask_ask import Ask, statement

app = Flask(__name__)
ask = Ask(app, '/')

@ask.intent('Dolphins')
def dolphin_fact():
    speech_text = 'The last ever dolphin message was "So long and thanks for all the fish"'
    return statement(speech_text).simple_card('My Robot', speech_text)

if __name__ == '__main__':
    app.run()
