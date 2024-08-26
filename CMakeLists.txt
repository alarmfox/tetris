cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Tetris)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# variables
set( TARGET ${PROJECT_NAME} )
set( SOURCE_PATH "${PROJECT_SOURCE_DIR}/src" )
set( INCLUDE_PATH "${PROJECT_SOURCE_DIR}/include" )

# project files
file( GLOB_RECURSE HS "${INCLUDE_PATH}/*.h" )
file( GLOB_RECURSE CPPS "${SOURCE_PATH}/*.cpp" )

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Add the executable
add_executable(${TARGET} ${HS} ${CPPS})

# Link the SDL2 library
target_link_libraries(${TARGET} ${SDL2_LIBRARIES})

# add compile options and include directories
target_compile_options( ${TARGET} PRIVATE -Wall -Wextra -Wshadow -Wconversion -Wsign-conversion -Wunused-parameter -Wno-long-long -pedantic )
target_include_directories(${TARGET} PRIVATE ${INCLUDE_PATH})
