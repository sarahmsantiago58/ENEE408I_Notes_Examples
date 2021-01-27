# Amazon Echo Control of Pololu Balboa Robot
Demonstrates control of a robot using an Amazon Echo Dot. Both devices can be on seperate local networks, connected to the open internet via NAT. This also works with Alexa smartphone app.

## Video demonstration with robot
[![ENEE 408I Spring 2020 Amazon Echo Balboa Demo](https://img.youtube.com/vi/Ffsx8L_rRIw/0.jpg)](https://www.youtube.com/watch?v=Ffsx8L_rRIw)

## Setup
### Dependencies
```bash
# Upgrade pip to fix segmentation fault when installing cryptography 2.1.4 for flask-ask
pip3 install --upgrade pip
# Get the latest version of flask-ask source
git clone https://github.com/johnwheeler/flask-ask.git
# Install it from the directory
pip3 install ./flask-ask

# Get the ngrok Linux ARM 64 bit binary (specifically for the Jetson)
wget https://bin.equinox.io/c/4VmDzA7iaHb/ngrok-stable-linux-arm64.tgz
tar -xzvf ngrok-stable-linux-arm64.tgz
# Get the Notes and Examples Repo if necessary (to get FlaskAskTest.py)
git clone https://github.com/UMD-ENEE408I/ENEE408I_Notes_Examples.git
```

### Setup Amazon Device
* Reset Amazon Echo/Show: [Link](https://www.amazon.com/gp/help/customer/display.html?nodeId=GD6UU5LZMGTZ5EF2)
* Associate Alex with your Amazon account: [Link](https://www.amazon.com/gp/help/customer/display.html?nodeId=G3BQ3JBVCELFGBEM)

### Setup Custom Amazon Skill (custom voice commands)
* Visit the [Alexa Developer Console](https://developer.amazon.com/alexa/console/ask) You may need to accept some agreements. At the end you should see a screen like this.
* Click "Create Skill"

![alt text](https://github.com/UMD-ENEE408I/ENEE408I_Notes_Examples/raw/main/examples/flask_ask/images/img1.png "img1")

* Enter "My Robot" in "Skill name".
* Choose "Custom" for the model.
* Choose "Provision your own" for hosting.
* Click "Create Skill" at the top right.

![alt text](https://github.com/UMD-ENEE408I/ENEE408I_Notes_Examples/raw/main/examples/flask_ask/images/img2.png "img2")

* Choose "Start from scratch" and click "Choose"

![alt text](https://github.com/UMD-ENEE408I/ENEE408I_Notes_Examples/raw/main/examples/flask_ask/images/img3.png "img3")

* Click "Invocation Name"
* Enter two words that will be the name of your robot
![alt text](https://github.com/UMD-ENEE408I/ENEE408I_Notes_Examples/raw/main/examples/flask_ask/images/img4.png "img4")

* Navigate to the "Intents Tab" under "Interaction Model"
* Click "Add Intent" Next to the intents list
* The intents are commands for the robot
![alt text](https://github.com/UMD-ENEE408I/ENEE408I_Notes_Examples/raw/main/examples/flask_ask/images/img5.png "img5")


* Make a new intent named "Dolphins"
* Enter "dolphin fact" as the sample utterance
* Click "Save Model" and "Build Model"
![alt text](https://github.com/UMD-ENEE408I/ENEE408I_Notes_Examples/raw/main/examples/flask_ask/images/img6.png "img6")

### Running Flask Ask on Jetson (must be done every startup)

* Open terminal on Jetson
* Run ngrok on port 5000: `./ngrok http 5000`
* Copy the https forwarding URL (mine was https://412094df.ngrok.io)

![alt text](https://github.com/UMD-ENEE408I/ENEE408I_Notes_Examples/raw/main/examples/flask_ask/images/img7.png "img7")

* Enter the information as shown into the "Endpoint" menu
* **Be sure to select "My development endpoint is a sub-domain of ..." or there will vague errors**
* Click "Save Endpoints"

![alt text](https://github.com/UMD-ENEE408I/ENEE408I_Notes_Examples/raw/main/examples/flask_ask/images/img8.png "img8")

* Navigate to the "Test" screen using the buttons at the top
* Select "Development" for the "Skill testing is enabled in" dropdown

![alt text](https://github.com/UMD-ENEE408I/ENEE408I_Notes_Examples/raw/main/examples/flask_ask/images/img9.png "img9")

* On the Jetson open a new terminal (there should be two now)
* Run `python3 ENEE408I_Notes_Examples/examples/flask_ask/FlaskAskTest.py`

* Type "ask my robot to say a dolphin fact" into the Alexa simulator and hit enter

* You can use a cell phone instead of an Amazon device, just install the app

## License
* The python source for communicating with the Alexa web service is derived from [flask-ask](https://github.com/johnwheeler/flask-ask) samples and is subject to Apache-2.0.

