#include <SDL3/SDL.h>
#include <iostream>
#include <math.h>

static int WINDOW_WIDTH = 1600;
static int WINDOW_HEIGHT = 800;

struct Circle {
    double x;
    double y;
    double radius;
};

bool IsInsideCircle(Circle circle, double x, double y) {
    double dx = x - circle.x;
    double dy = y - circle.y;
    return (dx * dx + dy * dy) < (circle.radius * circle.radius);
}

void CreateCircle(SDL_Renderer *renderer, Circle circle) {
    double radius_squared = pow(circle.radius, 2);

    for (double x = circle.x - circle.radius; x <= circle.x + circle.radius; x++) {
        for (double y = circle.y - circle.radius; y <= circle.y + circle.radius; y++) {
            double distance_squared = pow(x - circle.x, 2) + pow(y - circle.y, 2);
            if (distance_squared < radius_squared) {
                SDL_RenderPoint(renderer, x, y);
            }
        }
    }
}

void CreateLight(SDL_Renderer *renderer, Circle source, Circle *blockers, int blockerCount) {
    for (double i = 0.0; i < 360.0; i += 0.5) {
        double angle = i * (M_PI / 180.0);
        double dx = cos(angle);
        double dy = sin(angle);

        double x = source.x + source.radius * dx;
        double y = source.y + source.radius * dy;

        bool hit = false;
        while (!hit && x >= 0 && x <= WINDOW_WIDTH && y >= 0 && y <= WINDOW_HEIGHT) {
            x += dx;
            y += dy;

            for (int b = 0; b < blockerCount; b++) {
                if (IsInsideCircle(blockers[b], x, y)) {
                    hit = true;
                    break;
                }
            }
        }

        SDL_RenderLine(renderer,
            source.x + source.radius * dx,
            source.y + source.radius * dy,
            x, y);
    }
}

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL_Init error: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    if (!SDL_CreateWindowAndRenderer("Window", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
        std::cerr << "Error: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    SDL_Event event;
    bool running = true;

    Circle circle = {800, 400, 100};
    Circle source = {200, 200, 40};

    bool draggingCircle = false;
    bool draggingSource = false;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN && event.button.button == SDL_BUTTON_LEFT) {
                double mx = event.button.x;
                double my = event.button.y;
                if (IsInsideCircle(source, mx, my)) {
                    draggingSource = true;
                } else if (IsInsideCircle(circle, mx, my)) {
                    draggingCircle = true;
                }
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && event.button.button == SDL_BUTTON_LEFT) {
                draggingCircle = false;
                draggingSource = false;
            }

            if (event.type == SDL_EVENT_MOUSE_MOTION) {
                if (draggingSource) {
                    source.x = event.motion.x;
                    source.y = event.motion.y;
                } else if (draggingCircle) {
                    circle.x = event.motion.x;
                    circle.y = event.motion.y;
                }
            }
        }

        Circle blockers[] = { circle };

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        CreateLight(renderer, source, blockers, 1);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        CreateCircle(renderer, circle);

        SDL_SetRenderDrawColor(renderer, 255, 247, 0, 255);
        CreateCircle(renderer, source);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
