# cmake version to be required
cmake_minimum_required( VERSION 3.14 )

if(NOT DEFINED VCPKG_ROOT)
	if(DEFINED ENV{VCPKG_ROOT})
		set(VCPKG_ROOT $ENV{VCPKG_ROOT} CACHE PATH "Path to vcpkg directory")
	endif()
endif()

if(DEFINED VCPKG_ROOT)
	set(
		CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
		CACHE PATH "Path to vcpkg toolchain")

	if(NOT EXISTS "${CMAKE_TOOLCHAIN_FILE}")
		message(FATAL_ERROR "Invalid VCPKG_ROOT specified (${VCPKG_ROOT}); please specify an absolute path")
	endif()
endif()

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
  CACHE STRING "Vcpkg toolchain file")

# project name
project( ascii-art VERSION 0.0.2)

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