cmake_minimum_required(VERSION 3.5.0)
project(SDL3imgui VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES_IMGUI imgui_draw.cpp imgui_impl_sdl3.cpp imgui_impl_sdlrenderer3.cpp imgui_tables.cpp imgui_widgets.cpp imgui.cpp imgui_demo.cpp)

set(SOURCES_IMGUI_OPENGL imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp imgui.cpp imgui_demo.cpp imgui_impl_sdl3.cpp imgui_impl_opengl3.cpp)

if(USE_OPENGL)
add_library(${PROJECT_NAME} ${SOURCES_IMGUI_OPENGL})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PUBLIC opengl32 SDL3::SDL3)
else()
add_library(${PROJECT_NAME} ${SOURCES_IMGUI})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/ SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3)
endif()