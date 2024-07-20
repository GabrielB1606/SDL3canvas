cmake_minimum_required(VERSION 3.5.0)
project(SDL3engine)

add_executable(SDL3engine src/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC SDL3canvas SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3canvas SDL3::SDL3)

if(WIN32)
add_custom_command(
TARGET ${PROJECT_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy
${CMAKE_SOURCE_DIR}/build/vendor/SDL/SDL3.dll
$<TARGET_FILE_DIR:${PROJECT_NAME}>/ )
else()
add_custom_command(
TARGET ${PROJECT_NAME} POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy
${CMAKE_SOURCE_DIR}/build/vendor/SDL/libSDL3.so
$<TARGET_FILE_DIR:${PROJECT_NAME}>/ )
endif()