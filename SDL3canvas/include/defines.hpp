#ifndef DEFINES_HPP
#define DEFINES_HPP

#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
#include <SDL3/SDL.h>
#include "imgui.h"

struct GeomCircle{
  float cx, cy, r;

  SDL_Vertex vert[3];
  int idxs[3] = {0, 1, 2};

  std::vector<SDL_Vertex> points;
  std::vector<int> indexes;
  
  GeomCircle(float cx, float cy, float r){

    this->cx = cx;
    this->cy = cy;
    this->r = r;

    points.push_back(
      SDL_Vertex{
        SDL_FPoint{cx, cy},
        SDL_FColor{0.0, 1.0, 0.0}
      }
    );

    points.push_back(
      SDL_Vertex{
        SDL_FPoint{cx, cy-r},
        SDL_FColor{0.0, 1.0, 0.0}
      }
    );

    indexes.push_back(0);
    indexes.push_back(1);
    indexes.push_back(2);
    
    indexes.push_back(0);
    indexes.push_back(3);
    indexes.push_back(1);

    float step = std::max((float)r/100.0, 1.0);
    for (float i = -r; i <= r; i += step){
      float x = SDL_sqrt(r * r - i * i);
      points.push_back(
        SDL_Vertex{
          SDL_FPoint{cx-x, cy+i},
          SDL_FColor{0.0, 1.0, 0.0}
        }
      );
      points.push_back(
        SDL_Vertex{
          SDL_FPoint{cx+x, cy+i},
          SDL_FColor{0.0, 1.0, 0.0}
        }
      );
      indexes.push_back(0);
      indexes.push_back(points.size()-1);
      indexes.push_back(points.size()-3);
      
      indexes.push_back(0);
      indexes.push_back(points.size()-2);
      indexes.push_back(points.size());
      
    }

    points.push_back(
      SDL_Vertex{
        SDL_FPoint{cx, cy+r},
        SDL_FColor{0.0, 1.0, 0.0}
      }
    );

    indexes.push_back(0);
    indexes.push_back(points.size()-3);
    indexes.push_back(points.size()-1);

    indexes.push_back(0);
    indexes.push_back(points.size()-1);
    indexes.push_back(points.size()-2);

    // std::cout << points.size() << " " << indexes.size()<< "\n";
  }

  void render(SDL_Renderer *renderer)const{
    SDL_RenderGeometry(renderer, NULL, points.data(), points.size(), indexes.data(), indexes.size());
  }

};

struct FCircle{

  float cx, cy, r;
  std::vector<SDL_FPoint> points;

  FCircle(float cx, float cy, float r){
    this->cx = cx;
    this->cy = cy;
    this->r = r;

    for (float i = -r; i <= r; i += 0.0125){
      float x = SDL_sqrt(r * r - i * i);
      points.push_back(SDL_FPoint{cx - x, cy + i});
      points.push_back(SDL_FPoint{cx + x, cy + i});
    }
  }

  bool operator<(const FCircle &ot) const{
    return std::make_pair(cx, cy) < std::make_pair(ot.cx, ot.cy);
  }

  void render(SDL_Renderer *renderer, bool fill = true) const {
    if (!renderer)
      return;
    if(fill)
      SDL_RenderLines(renderer, points.data(), points.size());
    else
      SDL_RenderPoints(renderer, points.data(), points.size());
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

  bool intersects(Point<T> aa, Point<T> bb){
    return !(
      boundaries[0].x > bb.x ||
      boundaries[1].x < aa.x ||
      boundaries[0].y > bb.y ||
      boundaries[1].y < aa.y
    );
  }

  bool isContained(Point<T> aa, Point<T> bb){
    return
      boundaries[0].x >= aa.x &&
      boundaries[1].x <= bb.x &&
      boundaries[0].y >= aa.y &&
      boundaries[1].y <= bb.y;
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

    for (size_t i = 0; i < children.size(); i++)
      children[i].insert(value);

    return true;

  }

  std::vector<Point<T>> getPoints(){

    std::vector<Point<T>> ans;

    if(children.size()){
      for (int i = 0; i < children.size(); i++){
        std::vector<Point<T>> q = children[i].getPoints();
        for(const auto &item:q)
          ans.push_back(item);
      }
    }else{
      for(int i = 0; i<data.size(); ++i)
        ans.push_back(data[i]);
    }
    
    return ans;

  }

  std::vector<Point<T>> query(Point<T> aa, Point<T> bb){

    if(this->isContained(aa, bb))
      return getPoints();
    
    if(!this->intersects(aa, bb))
      return {};

    std::vector<Point<T>> ans;

    if(children.size()){
      for (int i = 0; i < children.size(); i++){
        std::vector<Point<T>> q = children[i].query(aa, bb);
        for(const auto &item:q)
          ans.push_back(item);
      }
    }else{
      for(int i = 0; i<data.size(); ++i)
        if( aa.x < data[i].x && aa.y < data[i].y && bb.x > data[i].x && bb.y > data[i].y )
          ans.push_back(data[i]);
    }
    
    return ans;

  }

  bool isContainedInCircle(Point<T> c, T r){
    T d0 = (boundaries[0].x - c.x)*(boundaries[0].x - c.x) + (boundaries[0].y - c.y)*(boundaries[0].y - c.y);
    T d1 = (boundaries[1].x - c.x)*(boundaries[1].x - c.x) + (boundaries[1].y - c.y)*(boundaries[1].y - c.y);
    T rr = r*r;
    return d0<rr && d1<rr;
  }

  std::vector<Point<T>> circleQuery(Point<T> c, T r){
    if(this->isContainedInCircle(c, r))
      return getPoints();
    
    if(!this->intersects({c.x-r, c.y-r}, {c.x+r, c.y+r}))
      return {};

    std::vector<Point<T>> ans;

    if(children.size()){
      for (int i = 0; i < children.size(); i++){
        std::vector<Point<T>> q = children[i].circleQuery(c, r);
        for(const auto &item:q)
          ans.push_back(item);
      }
    }else{
      T rr = r*r;
      for(int i = 0; i<data.size(); ++i)
        if( rr > (data[i].x-c.x)*(data[i].x-c.x) + (data[i].y-c.y)*(data[i].y-c.y))
          ans.push_back(data[i]);
    }
    
    return ans;
  }

};

void takeScreenshot(SDL_Renderer* renderer, const char *filename);

void drawCanvas(SDL_Renderer* renderer);
void pollEvent(SDL_Event event, ImGuiIO io);
void drawGui(SDL_Renderer* renderer, ImGuiIO io);

#endif