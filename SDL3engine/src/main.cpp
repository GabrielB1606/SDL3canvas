#include <stdio.h>
#include "include/defines.hpp"
#include <SDL3/SDL.h>

SDL_Window* window;

int main(int, char**){

  if(SDL_Init(SDL_INIT_AUDIO|SDL_INIT_EVENTS|SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_GAMEPAD) != 0){
    SDL_Log("SDL failed to init!");
    return -2;
  }

  window = SDL_CreateWindow("SDL3 Canvas", 1280, 720, 0);
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
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}