cmake_minimum_required(VERSION 3.16.3)
project(flower_game)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(lib/SFML/)
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-audio sfml-network sfml-graphics sfml-window sfml-system)
