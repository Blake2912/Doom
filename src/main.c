#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "player.h"
#include "map.h"
#include "raycast.h"
#include "config.h"

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("SDL Init error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "Doom",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        0);

    SDL_Renderer *renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        printf("Renderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    Uint32 lastTime = SDL_GetTicks();
    int frames = 0;

    while (running)
    {
        /* ================= INPUT ================= */

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
        }

        updatePlayer();

        /* ================= CLEAR ================= */

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);



        /* ================= CEILING ================= */

        SDL_Rect ceilingRect = {
            0,
            0,
            SCREEN_WIDTH,
            SCREEN_HEIGHT / 2};

        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderFillRect(renderer, &ceilingRect);

        /* ================= FLOOR ================= */

        SDL_Rect floorRect = {
            0,
            SCREEN_HEIGHT / 2,
            SCREEN_WIDTH,
            SCREEN_HEIGHT / 2};

        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderFillRect(renderer, &floorRect);

        /* ================= OPTIONAL MINIMAP ================= */

        // drawMap(renderer);
        // drawPlayer(renderer);m

        /* ================= RAYCAST ================= */

        float rayAngle = playerAngle - FOV / 2.0f;
        float rayStep = FOV / SCREEN_WIDTH;

        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            struct rayCastInfo hit = rayCastV2(playerX, playerY, rayAngle);

            double distance = hit.distance * cos(rayAngle - playerAngle);

            if (distance < 0.0001)
                distance = 0.0001;

            int lineHeight = (int)(SCREEN_HEIGHT / distance);

            int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
            int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;

            if (drawStart < 0)
                drawStart = 0;

            if (drawEnd >= SCREEN_HEIGHT)
                drawEnd = SCREEN_HEIGHT - 1;

            if (hit.side == 1)
                SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
            else
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

            SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);

            rayAngle += rayStep;
        }

        /* ================= PRESENT ================= */

        SDL_RenderPresent(renderer);

        /* ================= FPS COUNTER ================= */

        frames++;

        Uint32 currentTime = SDL_GetTicks();

        if (currentTime - lastTime >= 1000)
        {
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
