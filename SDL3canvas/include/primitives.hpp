#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include <vector>
#include <SDL3/SDL.h>

template <typename T> struct Point{
  T x, y;
};

struct GeomCircle{

  float cx, cy, r;
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

#endif