# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(AsteroidsGame)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the path to the PixelGameEngine header
include_directories(${CMAKE_SOURCE_DIR}/External/olcPixelGameEngine/Include)

# Add the path to the AsteroidsGame header
include_directories(${CMAKE_SOURCE_DIR}/Include)

# Add the source files
add_executable(AsteroidsGame
    Src/main.cpp
    Src/AsteroidsGame.cpp
)


