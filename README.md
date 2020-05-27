# ASCII-art
Transforms images to ASCII-art using OpenCV.

Project works using either 2 or 3 command-line argument (./ascii-art included). The 2nd argument specifies the image location (mandatory). The 3rd argument can take any of the following 3 values: "average" (default, no need to specify explicitely), "min-max" and "luminosity" which specifies the algorithm to be used for calculation of intensity of pixels.

*Pre-compiled OpenCV binaries are included.

## Build Process
This follows the standard CMake process
1. mkdir build
2. cd build
3. cmake ..
4. make (use -j$(sysctl -n hw.physicalcpu) for multi-threaded compilation)
