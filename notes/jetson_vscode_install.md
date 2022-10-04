# Installing VSCode on your Jetson Xavier NX

### Before Proceeding:

This guide assumes that your Jetson has been flashed to Jetpack 5.0.2, see [here](https://developer.nvidia.com/embedded/jetpack) for more details. If you or Levi recently flashed your Jetson, as of 10/3/22, this should be the case.

There probably exists a faster way to install VSCode onto your Jetson but think of this guide as a proven method you can always come back to! 

### Step 1: On your Jetson, download the VSCode package 
Go to the [download page](https://code.visualstudio.com/Download) for Visual Studio Code.
When selecting your version, make sure to select the ARM 64 binary next to ".deb"

### Step 2: Install the package

After your download has completed, open your terminal and use the following commands to install your package:

`sudo dpkg -i enter_path_to_your_package_here`

`sudo apt install apt-transport-https`

`sudo apt update`

`sudo apt install code`

To check if VSCode has installed successfully use `code --version`.

TIPS: 
1. If you ever want to know your current path use the `pwd` command.
2. To copy or paste in command line use Ctrl+Shift+C or Ctrl+Shift+V, respectively.

### Step 3: Run VSCode 

There currently exists a bug within Jetpack 5.0.2 where VSCode will not open if you simply call `code` in command line. A work around that solves this is:

`code -no-sandbox`

You should now see a VSCode window pop up on your screen.

### References:

1. When we first installed VSCode, we used the following [guide](https://www.forecr.io/blogs/programming/how-to-install-visual-studio-code-on-nvidia-jetson-xavier-nx-nano-run-sample-in-c-application). Subsequently, that guide is the basis of this guide. There is also some additional information on the guide with working with VSCode for your reference. 

2. We found out about the 5.0.2 and VSCode bug on the Nvidia forums [here](https://forums.developer.nvidia.com/t/vs-code-is-not-working-with-jetpack-5-0-2-on-jetson-nx/226013).
