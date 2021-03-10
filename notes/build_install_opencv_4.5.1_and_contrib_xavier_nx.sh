set -e

# Update package index (standard procedure to make sure package lists are up to date)
sudo apt update

# Standard build tools
sudo apt install -y cmake g++ wget unzip python3-dev

# Get packages for v4l, gstreamer (accessing raspberry pi camera), and gtk support (gui's)
sudo apt install -y libavcodec-dev libavformat-dev libswscale-dev
sudo apt install -y libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev
sudo apt install -y libgtk-3-dev

# Download and extract OpenCV 4.5.1 source for main repository and contrib
wget https://github.com/opencv/opencv/archive/4.5.1.tar.gz -O opencv-4.5.1.tar.gz
wget https://github.com/opencv/opencv_contrib/archive/4.5.1.tar.gz -O opencv_contrib-4.5.1.tar.gz
tar -xf opencv-4.5.1.tar.gz
tar -xf opencv_contrib-4.5.1.tar.gz

# Make and enter build directory
mkdir opencv-build
cd opencv-build

# Configure build
# Most features (like gstreamer support) turn on automatically if supporting libraries are installed (as installed above)
# CUDA has to be turned on manually (-DWITH_CUDA=ON)
# Generate CUDA binaries only for the Xavier NX's compute capability (-DCUDA_ARCH_BIN=7.2)
# Do not generate forward compatible binaries using an intermediate instruction set (-DCUDA_ARCH_PTX="")
cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib-4.5.1/modules -DWITH_CUDA=ON -DCUDA_ARCH_BIN=7.2 -DCUDA_ARCH_PTX="" ../opencv-4.5.1

# Parallel build with 6 cores
make -j6

