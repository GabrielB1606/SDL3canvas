#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <vector>
#include <SDL3/SDL.h>

struct FCircle{

  float cx, cy, r;
  std::vector<SDL_FPoint> points;

  FCircle(float cx, float cy, float r){
    this->cx = cx;
    this->cy = cy;
    this->r = r;

    for (float i = -r; i <= r; i += 0.5){
      float x = SDL_sqrt(r * r - i * i);
      points.push_back(SDL_FPoint{cx - x, cy + i});
      points.push_back(SDL_FPoint{cx + x, cy + i});
    }
  }

  void render(SDL_Renderer *renderer) const {
    if (!renderer)
      return;
    SDL_RenderLines(renderer, points.data(), points.size());
  }
};

struct FQuadtree{

  int capacity;

};

#endif