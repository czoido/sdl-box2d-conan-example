cmake_minimum_required(VERSION 3.15)
project(mygame CXX)

find_package(SDL2 REQUIRED CONFIG)
find_package(box2d REQUIRED CONFIG)
# FIXME: sdl_image conan package still not adding properties
find_package(sdl_image REQUIRED CONFIG)

add_executable(mygame src/main.cpp)

# FIXME: sdl_image conan package still not adding properties
target_link_libraries(${PROJECT_NAME} box2d::box2d SDL2::SDL2main sdl_image::sdl_image)
