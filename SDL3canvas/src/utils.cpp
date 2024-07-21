#include "include/defines.hpp"

void takeScreenshot(SDL_Renderer* renderer, const char *filename){
  SDL_Rect camera = {0, 0, 1280, 720};
  SDL_Surface *frame = SDL_RenderReadPixels(renderer, &camera);
  SDL_SaveBMP(frame, filename);
  SDL_DestroySurface(frame);
}