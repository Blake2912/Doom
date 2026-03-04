#include <SDL2/SDL.h>
#include<stdbool.h>
#include<stdio.h>
#include "player.h"
#include "map.h"
#include "raycast.h"
#include "config.h"


int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL Init error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Doom",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0
    );
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        printf("Renderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;
    Uint32 lastTime = SDL_GetTicks();
    int frames = 0;

    while (running) {
        /* Handle Input */
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        updatePlayer();

        /* Clear Screen */
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawMap(renderer);
        drawPlayer(renderer);
        castRay(renderer, playerX, playerY, playerAngle);

        /* Present Frame */
        SDL_RenderPresent(renderer);

        frames++;

        Uint32 currentTime = SDL_GetTicks();

        if (currentTime - lastTime >= 1000) {
            printf("FPS: %d\n", frames);
            frames = 0;
            lastTime = currentTime;
        }
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
