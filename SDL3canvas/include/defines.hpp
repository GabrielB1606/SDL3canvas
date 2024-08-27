#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
#include <SDL3/SDL.h>
#include "imgui.h"

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

#include "primitives.hpp"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

void takeScreenshot(SDL_Renderer* renderer, const char *filename);

void drawCanvas(SDL_Renderer* renderer);
void pollEvent(SDL_Event event, ImGuiIO io);
void drawGui(SDL_Renderer* renderer, ImGuiIO io);

void initCanvas();
void cleanUpCanvas();

#endif