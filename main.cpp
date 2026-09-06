#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>

const int WIDTH = 1920;
const int HEIGHT = 1080;
double f_max = 2.0 * 5 * M_PI;
double a = std::min(WIDTH,HEIGHT)/(2.5*f_max); 
double df = 0.05;



int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(
        "Archimedal Spiral",  //figure title
        SDL_WINDOWPOS_CENTERED,  //x start pos
        SDL_WINDOWPOS_CENTERED,  //y start pos
        WIDTH, 
        HEIGHT,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1, 
        SDL_RENDERER_ACCELERATED //Transfer calculations from CPU to GPU for more speed
    );

    if (window == NULL || renderer == NULL) {
    std::cout << " Ошибка SDL: " << SDL_GetError() << std::endl;
    return 1;
    }

    bool running = true;
    SDL_Event event;

    while (running){
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = false;
            }
        }

        SDL_SetRenderDrawColor(
            renderer,
            0,
            0,
            0,
            255
        );
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(
            renderer,
            255,
            255,
            255,
            255
        );

        int prev_x, center_x = WIDTH/2;
        int prev_y, center_y = HEIGHT/2;

        for (double f = 0; f <= f_max; f += df){
            double p = a * f;
            int x = (WIDTH/2) + static_cast<int>(p * cos(f));
            int y = (HEIGHT/2) - static_cast<int>(p * sin(f));

            SDL_RenderDrawLine(
                renderer,
                prev_x,
                prev_y,
                x,
                y
            );

            prev_x = x;
            prev_y = y;
        }

        SDL_SetRenderDrawColor(
            renderer,
            255,
            0,
            0,
            255
        );
        SDL_RenderDrawLine(
            renderer,
            center_x,
            center_y,
            prev_x,
            prev_y
        );

        SDL_SetRenderDrawColor(
            renderer,
            0,
            255,
            0,
            255
        );
        for (double f = 0; f <= f_max; f += df){
            double neg_f = -f;
            double p = a * f;
            int x = (WIDTH/2) + static_cast<int>(p * cos(neg_f));
            int y = (HEIGHT/2) - static_cast<int>(p * sin(neg_f));

            SDL_Rect dot = {
                x - 1,
                y - 1,
                2,
                2
            };
            SDL_RenderFillRect(renderer, &dot);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}