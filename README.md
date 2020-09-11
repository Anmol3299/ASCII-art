# ASCII-art
Transforms images to ASCII-art using OpenCV.

Project works using either 2 or 3 command-line argument (./ascii-art included). The 2nd argument specifies the image location (mandatory). The 3rd argument can take any of the following 3 values: "average" (default, no need to specify explicitely), "min-max" and "luminosity" which specifies the algorithm to be used for calculation of intensity of pixels.

## Build Process
Assuming you have `VCPKG_ROOT` in your environment variables, the following
will work in sh:

```sh
$ cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake
$ cmake --build build
```
