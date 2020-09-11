# cmake version to be required
cmake_minimum_required( VERSION 3.0.0 )

# project name
project( ascii-art VERSION 1.0.0)

# Find opencv package
find_package( opencv REQUIRED )

# include dirs
include_directories( ./include )

# target
add_executable( ascii-art ./src/main.cpp ./src/image_ops.cpp )

# Tell compiler to use C++ 17 features
set_property( TARGET ascii-art PROPERTY CXX_STANDARD 17 )

# tell it to link the executable target against OpenCV
target_link_libraries( ascii-art PRIVATE ${OpenCV_LIBS} )