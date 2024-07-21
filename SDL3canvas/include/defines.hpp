#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <vector>
#include <array>
#include <SDL3/SDL.h>
#include "imgui.h"

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

template <typename T> struct Point{
  T x, y;
};

template <typename T> struct Quadtree{

  unsigned long long capacity = 4;
  std::vector<Point<T>> data;
  std::vector<Quadtree<T>> children;
  Point<T> boundaries[2];
  SDL_FRect rect;

  Quadtree(Point<T> from, Point<T> to, unsigned long long capacity=4){
    this->capacity = capacity;
    boundaries[0] = from;
    boundaries[1] = to;
    this->rect = {
      boundaries[0].x,
      boundaries[0].y,
      boundaries[1].x-boundaries[0].x,
      boundaries[1].y-boundaries[0].y
    };
  }

  void render(SDL_Renderer *renderer){
    if(!renderer)
      return;
    SDL_RenderRect(renderer, &this->rect);
    for (size_t i = 0; i < children.size(); i++)
      children[i].render(renderer);
  }

  bool contains(Point<T> pt){
    return 
      pt.x > boundaries[0].x &&
      pt.x <= boundaries[1].x &&
      pt.y > boundaries[0].y &&
      pt.y <= boundaries[1].y; 
  }

  bool insert(Point<T> value){

    if(!contains(value))
      return false;
    
    if(!children.size() && data.size() < capacity){
      data.push_back(value);
      return true;
    }

    if(!children.size()){
      
      T lx = boundaries[0].x, mx = (boundaries[0].x + boundaries[1].x)/2, rx = boundaries[1].x;
      T ty = boundaries[0].y, my = (boundaries[0].y + boundaries[1].y)/2, by = boundaries[1].y;

      children.push_back( Quadtree<T>(
        Point<T>{lx, ty},
        Point<T>{mx, my},
        this->capacity
      ) );

      children.push_back( Quadtree<T>(
        Point<T>{lx, my},
        Point<T>{mx, by},
        this->capacity
      ) );

      children.push_back( Quadtree<T>(
        Point<T>{mx, my},
        Point<T>{rx, by},
        this->capacity
      ) );

      children.push_back( Quadtree<T>(
        Point<T>{mx, ty},
        Point<T>{rx, my},
        this->capacity
      ) );

      for (size_t i = 0; i < data.size(); i++)
        for(size_t j = 0; j<children.size(); ++j)
          children[j].insert(data[i]);
      
      data.clear();
    }

    for (size_t i = 0; i < capacity; i++)
      children[i].insert(value);

    return true;

  }

};

void drawCanvas(SDL_Renderer* renderer);
void pollEvent(SDL_Event event);
void drawGui(ImGuiIO io);

#endif