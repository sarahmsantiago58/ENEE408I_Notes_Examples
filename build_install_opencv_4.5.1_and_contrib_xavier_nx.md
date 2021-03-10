# Compile OpenCV and OpenCV contrib 4.5.1 from source for Jetson Xavier NX

This note shows how to install a newer version of OpenCV and OpenCV contrib (4.5.1) on the Jetson than what is installed by default (4.1.1 and without OpenCV contrib).

This allows using a newer version of OpenCV and OpenCV contrib on the Xavier NX without losing gstreamer support (needed for opening the Raspberry Pi camera).

# Remove old packages
If you are reading this note, it is possible you tried installing a newer version of OpenCV from PyPi already (using pip). It is recommended to uninstall those packages.

If the following commands fail, it is most likely because the package was not installed from PyPi or the only version of the package installed is the one that shipped with the Jetson (and cannot be removed by pip running without sudo). In both cases the errors can be ignored.

```
pip3 uninstall opencv-python
pip3 uninstall opencv-contrib-python
pip3 uninstall numpy
```

# Get the install script
A script that builds and installs OpenCV and OpenCV contrib 4.5.1 is in this repo. You can download and run it with the following commands. The install command is not included in the script because the final install command will require the password and the build takes so long that the previous password authentication times out.

The build process takes 100 minutes. OpenCV is a very large library and the script below compiles almost every component. 

It is recommended that most other programs are closed (especially Chromium) or the Jetson could run out of RAM. A good idea is to run `htop` in another terminal to monitor resource usage.

```
mkdir opencv
cd opencv
wget https://raw.githubusercontent.com/UMD-ENEE408I/ENEE408I_Notes_Examples/main/notes/build_install_opencv_4.5.1_and_contrib_xavier_nx.sh
bash build_install_opencv_4.5.1_and_contrib_xavier_nx.sh
cd opencv-build
sudo make -j6 install
```

The install step uses `-j6` because OpenCV performs linking in the install phase which can be speed up considerably with parallelization.

# Uninstall
To uninstall, and revert back to the preinstall OpenCV 4.1.1, `cd` into the build directory (most likely `~/opencv/opencv-build`) and run `sudo make uninstall`

# Sources
https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html

https://docs.opencv.org/master/d2/de6/tutorial_py_setup_in_ubuntu.html

https://docs.opencv.org/3.4/d6/d15/tutorial_building_tegra_cuda.html

https://forums.developer.nvidia.com/t/what-compute-capability-of-jetson-xavier-nx-gpu-is/146241
