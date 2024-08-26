cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Tetris)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# variables
set( TARGET ${PROJECT_NAME} )
set( SOURCE_PATH "${PROJECT_SOURCE_DIR}/src" )
set( INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include" )

# project files
file( GLOB_RECURSE HPPS "${INCLUDE_PATH}/*.h" )
file( GLOB_RECURSE CPPS "${SOURCE_PATH}/*.cpp" )

# Add the executable
add_executable(${TARGET} ${HPPS} ${CPPS})

# Find the SDL2 library
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_compile_options( ${TARGET} PRIVATE -Wall -Wextra -Wshadow -Wconversion -Wsign-conversion -Wunused-parameter -Wno-long-long -pedantic )

# Link the SDL2 library
target_link_libraries(${TARGET} ${SDL2_LIBRARIES})
