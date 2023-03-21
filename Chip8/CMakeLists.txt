# CMakeList.txt : CMake project for Chip8, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Add source to this project's executable.
add_executable (Chip8 "Chip8.cpp" "Chip8.h" "Main.cpp" "Display_Helper.h" "Display_Helper.cpp")

target_link_libraries(Chip8 SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Chip8 PROPERTY CXX_STANDARD 17)
endif()

# TODO: Add tests and install targets if needed.
