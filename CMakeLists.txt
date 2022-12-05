cmake_minimum_required(VERSION 3.15)

project(JsonConfiger LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json)
    configure_file(${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json COPYONLY)
endif()

# Source files
file(GLOB_RECURSE PROJECT_SOURCES Source/*.cpp Source/*.h Source/*.hpp)

add_library(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE Source)
