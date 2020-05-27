# cmake version to be required
cmake_minimum_required( VERSION 3.0.0 )

# project name
project( ascii-art VERSION 1.0.0)

include(CTest)
enable_testing()

# set OpenCV_DIR variable equal to the path to the cmake
# files within the previously installed opencv program
set(OpenCV_DIR ./libs/opencv/install/lib/cmake/opencv4)

# configure the necessary common CMake environment variables
# needed to include and link the OpenCV program into this
# demo project, namely OpenCV_INCLUDE_DIRS and OpenCV_LIBS
find_package( OpenCV REQUIRED )

# flags
# Tell compiler to use C++ 17 features
set(CMAKE_CXX_STANDARD 17)

# include dirs
include_directories( ${OpenCV_INCLUDE_DIRS}, ./include )

# target
add_executable( ascii-art ./src/main.cpp ./src/image_ops.cpp )

# tell it to link the executable target against OpenCV
target_link_libraries( ascii-art ${OpenCV_LIBS} )