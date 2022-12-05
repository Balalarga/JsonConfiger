cmake_minimum_required(VERSION 3.15)

project(JsonConfigerTester LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(../ JsonConfiger)

# Source files
file(GLOB_RECURSE PROJECT_SOURCES Source/*.cpp Source/*.h Source/*.hpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE Source)

target_link_libraries (${PROJECT_NAME} LINK_PUBLIC JsonConfiger)
target_include_directories(${PROJECT_NAME} PUBLIC JsonConfiger)