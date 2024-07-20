#include <stdio.h>
#include "include/defines.hpp"
#include <SDL3/SDL.h>

SDL_Window* window;
SDL_Renderer* renderer;

int main(int, char**){

  if(SDL_Init(SDL_INIT_AUDIO|SDL_INIT_EVENTS|SDL_INIT_VIDEO) != 0){
    SDL_Log("SDL failed to init!");
    return -1;
  }

  window = SDL_CreateWindow("SDL3 Canvas", 600, 600, 0);
  renderer = SDL_CreateRenderer(window, NULL);
  bool running = 1;
  
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
    SDL_RenderPresent(renderer);
    SDL_Delay(1);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}