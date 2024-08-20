cmake_minimum_required(VERSION 3.5.0)
project(SDL3engine)

# set(SOURCES_IMGUI SDL3imgui/imconfig.h SDL3imgui/imgui.h SDL3imgui/imgui_impl_sdl3.h SDL3imgui/imgui_impl_sdlrenderer3.h SDL3imgui/imgui_internal.h SDL3imgui/imstb_rectpack.h SDL3imgui/imstb_textedit.h SDL3imgui/imstb_truetype.h SDL3imgui/imgui_draw.cpp SDL3imgui/imgui_impl_sdl3.cpp SDL3imgui/imgui_impl_sdlrenderer3.cpp SDL3imgui/imgui_tables.cpp SDL3imgui/imgui_widgets.cpp SDL3imgui/imgui.cpp)

if(USE_OPENGL)
add_executable(SDL3engine src/main_opengl.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC GLAD SDL3canvas SDL3::SDL3 SDL3imgui glm::glm)
target_include_directories(${PROJECT_NAME} PUBLIC GLAD SDL3canvas SDL3::SDL3 SDL3imgui)
include_directories(${CMAKE_SOURCE_DIR}/vendor/SDL3imgui ${CMAKE_SOURCE_DIR}/vendor/glad/include)
else()
add_executable(SDL3engine src/main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3canvas SDL3::SDL3 SDL3imgui glm::glm)
target_include_directories(${PROJECT_NAME} PUBLIC SDL3canvas SDL3::SDL3 SDL3imgui)
include_directories(${CMAKE_SOURCE_DIR}/vendor/SDL3imgui)
endif()

# find_package(SDL3imgui REQUIRED PATHS "${CMAKE_BINARY_DIR}/vendor/SDL3imgui")


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