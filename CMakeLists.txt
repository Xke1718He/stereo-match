cmake_minimum_required(VERSION 3.10)
project(stereo-match)

set(CMAKE_CXX_STANDARD 11)
set(OpenCV_DIR "/opt/ros/kinetic/share/OpenCV-3.3.1-dev")
find_package(OpenCV REQUIRED)
include_directories(
        include
        ${OpenCV_INCLUDE_DIRS}
)
set(source_file
        src/cost.cpp
        src/match.cpp
        src/Dp.cpp)
add_executable(stereo-match ${source_file} main.cpp)
target_link_libraries(stereo-match ${OpenCV_LIBS})