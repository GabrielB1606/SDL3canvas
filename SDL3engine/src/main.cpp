#include <stdio.h>
#include <vector>
#include "include/defines.hpp"
#include <SDL3/SDL.h>

SDL_Window* window;
SDL_Renderer* renderer;

struct FCircle{

  float cx, cy, r;
  std::vector<SDL_FPoint> points;

  FCircle(float cx, float cy, float r){
    this->cx = cx;
    this->cy = cy;
    this->r = r;

    for (float i = -r; i <= r; i+=0.5){
      float x = SDL_sqrt(r*r - i*i);
      points.push_back( SDL_FPoint{cx-x, cy+i} );
      points.push_back( SDL_FPoint{cx+x, cy+i} );
    }

  }

  void render(SDL_Renderer* renderer){
    if(!renderer)
      return;
    SDL_RenderLines(renderer, points.data(), points.size());
  }

};

int main(int, char**){
  if(SDL_Init(SDL_INIT_AUDIO|SDL_INIT_EVENTS|SDL_INIT_VIDEO) != 0){
    SDL_Log("SDL failed to init!");
    return -1;
  }

  window = SDL_CreateWindow("SDL3 Canvas", 1280, 720, SDL_WINDOW_HIGH_PIXEL_DENSITY);
  renderer = SDL_CreateRenderer(window, NULL);
  bool running = 1;
  
  SDL_FRect test = {100, 100, 50, 50};
  SDL_Vertex geom[3] = {
    {SDL_FPoint{0,0}, SDL_FColor{0xff,0,0,0xff}, SDL_FPoint{0,0}},
    {SDL_FPoint{100,0}, SDL_FColor{0,0,0xff,0xff}, SDL_FPoint{1,0}},
    {SDL_FPoint{0,100}, SDL_FColor{0,0xff,0,0xff}, SDL_FPoint{0,1}}
  };
  int idxs[3] = {0,1,2};

  FCircle circ(200, 200, 100);

  while(running){
    SDL_Event event;
    if(SDL_PollEvent(&event) > 0)
      switch (event.type){
        case SDL_EVENT_QUIT:
          running = false;
          break;
        
        default:
          break;
      }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0xff, 0xff);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0xff, 0, 0xff);
    SDL_SetRenderScale(renderer, 1, 1);
    // SDL_RenderFillRect(renderer, &test);
    // SDL_SetRenderScale(renderer, 2, 2);
    // SDL_RenderPoint(renderer, 200,  200);
    circ.render(renderer);
    SDL_RenderLine(renderer, 0,0,500,500);
    SDL_RenderGeometry(renderer, NULL, geom, 3, idxs, 3);
    SDL_RenderPresent(renderer);
    SDL_Delay(1);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}