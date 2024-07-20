#include "include/defines.hpp"

SDL_Window* window;
SDL_Renderer* renderer;

int main(int, char**){
  if(SDL_Init(SDL_INIT_AUDIO|SDL_INIT_EVENTS|SDL_INIT_VIDEO) != 0){
    SDL_Log("SDL failed to init!");
    return -1;
  }

  window = SDL_CreateWindow("SDL3 Canvas", 1280, 720, SDL_WINDOW_HIGH_PIXEL_DENSITY);
  renderer = SDL_CreateRenderer(window, NULL);
  bool running = 1;
  
  std::vector<FCircle> pts;

  FCircle circ(200, 200, 100);

  while(running){
    SDL_Event event;
    if(SDL_PollEvent(&event) > 0)
      switch (event.type){
        case SDL_EVENT_QUIT:
          running = false;
          break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
          pts.push_back( FCircle(event.motion.x, event.motion.y, 3) );
          break;
        
        default:
          break;
      }
    SDL_SetRenderDrawColor(renderer, 69, 69, 69, 0xff);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0xff, 0, 0xff);
    SDL_SetRenderScale(renderer, 1, 1);
    
    for(const auto &c:pts)
      c.render(renderer);

    SDL_RenderPresent(renderer);
    SDL_Delay(1);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}