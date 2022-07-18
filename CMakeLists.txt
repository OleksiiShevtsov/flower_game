cmake_minimum_required(VERSION 3.16.3)
project(flower_game)

set(CMAKE_CXX_STANDARD 14)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(lib/SFML/)
add_subdirectory(common)
add_subdirectory(logic)

