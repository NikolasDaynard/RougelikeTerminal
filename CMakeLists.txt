cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(termgame VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# Find ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Add the executable
add_executable(${PROJECT_NAME} src/main.cpp)

# Link ncurses
target_link_libraries(${PROJECT_NAME} ${CURSES_LIBRARIES})
