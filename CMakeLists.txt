cmake_minimum_required(VERSION 3.5.0)

project(SDL3canvasTEST)

set(USE_OPENGL ON)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/SDL)
add_subdirectory(vendor/SDL3imgui)
add_subdirectory(SDL3canvas)
add_subdirectory(SDL3engine)