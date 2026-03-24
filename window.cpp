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
  double x;
  double y;
  double radius;
};

void CreateCircle(SDL_Renderer *renderer, struct Circle circle) {
  
  double raidus_squared = pow(circle.radius, 2);
 
  for(double x = circle.x - circle.radius; x <= circle.x + circle.radius; x++) {
    for(double y = circle.y - circle.radius; y <= circle.y + circle.radius; y++) {
      double distance_squared = pow(x - circle.x, 2) + pow(y - circle.y, 2);
      if(distance_squared < raidus_squared) {
        SDL_RenderPoint(renderer, x, y);
      }
    }
  }
}

void CreateLight(SDL_Renderer *renderer, struct Circle source) {
  for(int i = 0; i < 360; i++) {
    SDL_RenderLine(
        renderer,
        source.x + source.radius * cos(i),
        source.y + source.radius * sin(i),
        (WINDOW_WIDTH * cos(i)) * 10,
        (WINDOW_HEIGHT * sin(i)) * 10
        );
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
  Circle circle = {800, 400, 100};
  Circle source = {200, 200, 40};
  while (running) {
    while (SDL_PollEvent(&event)) {
      if(event.type == SDL_EVENT_QUIT) {
        running = false;
      }
      if(event.type == SDL_EVENT_MOUSE_MOTION && 
          event.motion.state == true && 
          event.motion.x > circle.x-circle.radius &&
          event.motion.y > circle.y-circle.radius &&
          event.motion.x < circle.x+circle.radius &&
          event.motion.y < circle.y+circle.radius) {
        circle.x = event.motion.x;
        circle.y = event.motion.y;
      }
      if(event.type == SDL_EVENT_MOUSE_MOTION && 
          event.motion.state == true && 
          event.motion.x > source.x-source.radius &&
          event.motion.y > source.y-source.radius &&
          event.motion.x < source.x+source.radius &&
          event.motion.y < source.y+source.radius) {
        source.x = event.motion.x;
        source.y = event.motion.y;
      }
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    CreateCircle(renderer, circle);

    SDL_SetRenderDrawColor(renderer, 255, 247, 0, 255);
    CreateCircle(renderer, source);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    CreateLight(renderer, source);

    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

}
