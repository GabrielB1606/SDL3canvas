cmake_minimum_required(VERSION 3.5.0)
project(SDL3engine)

add_executable(SDL3engine src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC SDL3canvas)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3canvas)