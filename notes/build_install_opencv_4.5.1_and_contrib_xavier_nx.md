# Intro
The OpenCV shipped with the Xavier NX is version 4.1.1 (current version is 4.5.1) and does not include OpenCV contrib (which contains some popular facial recognition algorithms). Installing OpenCV contrib from PyPi can remove gstreamer support causing the raspberry pi camera to not work (also at the time of writing it installs a broken version of NumPy that causes `import numpy` to crash).

This note shows how to build OpenCV 4.5.1 and contrib from source, with gstreamer and CUDA support for the Xavier NX.

# Uninstall old packages
If you are reading this, you may have tried to install newer OpenCV and NumPy packages from PyPi. It is best to uninstall them. The following commands should do so, they will not uninstall the system version of these packages so nothing will break.

```
pip3 uninstall opencv-contrib-python
pip3 uninstall opencv-python
pip3 uninstall numpy
```

# Run the build script
This repo contains a build script for quickly building an installing.

The build process takes about 100 minutes.

The install command is not included in the script because it prompts for a password.

It is best to close all applications (especially Chromium) to avoid running out of RAM. It is good to open up another terminal to run `htop` and monitor system resource usage.

```
mkdir opencv
cd opencv
wget https://raw.githubusercontent.com/UMD-ENEE408I/ENEE408I_Notes_Examples/main/notes/build_install_opencv_4.5.1_and_contrib_xavier_nx.sh
bash build_install_opencv_4.5.1_and_contrib_xavier_nx.sh
cd opencv-build
sudo make -j6 install
```

# Uninstall

To uninstall, and go back to the version of OpenCV shipped with the Xavier NX, `cd` into the build directory (probably ~/opencv/opencv-build) and run `sudo make uninstall`

# Sources
https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html

https://docs.opencv.org/master/d2/de6/tutorial_py_setup_in_ubuntu.html

https://docs.opencv.org/3.4/d6/d15/tutorial_building_tegra_cuda.html

https://forums.developer.nvidia.com/t/what-compute-capability-of-jetson-xavier-nx-gpu-is/146241
