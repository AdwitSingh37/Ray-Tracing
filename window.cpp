#include <SDL3/SDL.h>
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <iostream>
#include <math.h>
#include <iostream>

static int WINDOW_WIDTH = 1600;
static int WINDOW_HEIGHT = 800;

struct Circle {
  float x;
  float y;
  double radius;
};

void CreateCircle(SDL_Renderer *renderer, struct Circle circle) {
  for(int i = 0; i < 360; i++) {
    SDL_RenderPoint(renderer, circle.x + circle.radius * cos(i), circle.y +  circle.radius * sin(i));
  }
}

int main() {
  if(!SDL_Init(SDL_INIT_VIDEO)) {
    std::cerr << "SDL_Init error: " << SDL_GetError() << "\n";
    return 1;
  }

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  if(!SDL_CreateWindowAndRenderer("Window", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
    std::cerr << "Error: " << SDL_GetError() << "\n";
    SDL_Quit();
    return 1;
  }

  SDL_Event event;
  bool running = true;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if  (event.type == SDL_EVENT_QUIT) {
        running = false;
      }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    Circle circle;
    circle.x = 200;
    circle.y = 200;
    circle.radius = 50;
    CreateCircle(renderer, circle);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

}
