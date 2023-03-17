# Wifi UDP Example

Shows how to send data from a robot mouse to a Python script and back.

To use:
* Find out the local ip address of your laptop or Jetson (use `ipconfig` on windows, `ip addr` on the Jetson)
* Edit `main.cpp` to contain your laptop (or Jetson's) ip address. Make sure the wifi name/password are correct.
* Flash the robot mouse with this PlatformIO project
* Run the `udp_server.py` script in the root of this project. `python3 udp_server.py`.
* View the python script's output and the robot mouses serial console to see the messages going back and forth.
