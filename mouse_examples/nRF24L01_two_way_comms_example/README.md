# nRF24L01+ comms between mouse and Jetson

`nRF24L01_two_way_mouse` should be flashed to the mouse. You can open a serial terminal to see the output.

`nRF24L01_two_way_jetson` should be flashed to the nano connected to the jetson. You should keep the serial terminal closed unless debugging.

`two_way_jetson.py` should be run on the Jetson. It will print the results. It requires the `pyserial` module. `pip3 install pyserial`.