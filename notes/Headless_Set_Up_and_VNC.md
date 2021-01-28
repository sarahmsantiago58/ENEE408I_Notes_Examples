# Set up Jetson Xavier NX without a Monitor on a Mac
Here's a [link](https://desertbot.io/blog/jetson-xavier-nx-headless-wifi-setup) that helps with setting up the Jetson Xavier NX without a monitor.
Make sure to connect to WiFi in when configuring the settings: "Step 10. Fill in the config info -> Network configuration" in the [link](https://desertbot.io/blog/jetson-xavier-nx-headless-wifi-setup). 
This will give a good way to access the Jetson Xavier NX filesystem through terminal however it's not very user friendly when it comes to writing code. 
Therefore, if you want to view the GUI you need to install x11vnc.

# Installing x11vnc: 
### It's always good to make sure everythings updated
`sudo apt-get update`

### Step 1: Change from the display manager from gnome display to lightdm: 
`sudo apt-get install lightdm`
### Step 2: Reboot the system: 
`sudo reboot`
### Step 3: Install x11vnc: 
`sudo apt-get install x11vnc`
### Step 4: Get the IP address, it's the numbers after "inet ..." (for example: "inet 10.142.06.942") Note down the IP address.
`ip address show`


Inorder to view the Jetson Xavier NX or the GUI on your Mac you need to download VNC Viewer [here](https://www.realvnc.com/en/connect/download/viewer/macos/). 

### First launch x11vnc on the terminal by: 
command: `x11vnc`

### Launch VNC Viewer on Mac: 
Make a new connection: Enter IP Address from Step 4 above. 

Give it a "Friendly Name" and OK 

Under Options make sure to uncheck "View-only" so you can actually interact with the virtual desktop setting. 

Once you are in the Jetson, the default screen resolution is very low. 

To increase the resoltions so you can see everything simply open up terminal and type the follow command: 
`xrandr --fb WxH`

A good size for WxH can be 1080x675, 1400x875, or 1920x1200, this depends on your Mac resolution options. 

### Turn On and Off
Turn on: 
`ls -ls /dev/cu.*` to find the device that says something along the line of "/dev/cu.usbmode..." 

Then do: `screen /dev/cu.usbmode* 115200 -L` (this just an example your device might have a number, write it exactly as it's show) 

Launch x11vnc: `x11vnc` and launch it from VNC Viewer on Mac 

Turn Off: `sudo shutdown -h now` in terminal on Mac 





