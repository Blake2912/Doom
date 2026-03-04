cmake_minimum_required(VERSION 3.10)

project(doom C)

include_directories(/opt/homebrew/include)

link_directories(/opt/homebrew/lib)

add_executable(doom src/main.c)

target_link_libraries(doom SDL2)
