# Stellar Salvage

## Build with SDL2

### Windows MSVC
1. Download the ``SDL2-devel-2.xx-VC.zip`` https://github.com/libsdl-org/SDL/releases
2. Unzip it in a folder
3. Add folder path to system ``PATH``
4. Maybe you have to set SDL2_DIR for find_package to work
5. To find ``SDL2.dll`` during runtime add SDL2 lib folder to system ``PATH``

### Ubuntu gcc
1. ``sudo apt update && sudo apt upgrade``
2. ``sudo apt install build-essential && sudo apt install cmake``
3. ``sudo apt install libsdl2-dev libsdl2-2.0-0 -y``
4. To use c++-20 you have to install ``gcc-13``

## Build with SFML

### Windows MSVC
1. Download SFML source https://www.sfml-dev.org/download.php
2. Unzip into folder
3. Add folder path to system ``PATH``
4. To find ``SFML.dll`` during runtime add SFML lib folder to system ``PATH

### Install gcc-13 ubuntu
1. Install software-properties-common package: ``sudo apt install software-properties-common``
2. Add GCC PPA containing all gcc versions: ``sudo add-apt-repository ppa:ubuntu-toolchain-r/test``
3. ``sudo apt update``
4. Install specific or multiple versions: ``sudo apt install gcc-12 g++-12 gcc-13 g++-13 -y``
5. Manage version with update-alternatives tool: ``sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-12 12 --slave /usr/bin/g++ g++ /usr/bin/g++-12``
6. Add the GCC 13 alternative to the update-alternatives filesystem: ``sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-13 13 --slave /usr/bin/g++ g++ /usr/bin/g++-13``
7. Switch between versions: ``sudo update-alternatives --config gcc``