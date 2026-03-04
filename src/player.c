#include <SDL2/SDL.h>
#include "config.h"

float playerX = 3.5 * TILE_SIZE;
float playerY = 3.5 * TILE_SIZE;

float playerSpeed = 2.5f;

void drawPlayer(SDL_Renderer* renderer)
{
    SDL_Rect player = {
        playerX - 5,
        playerY - 5,
        10,
        10
    };

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &player);
}

void updatePlayer()
{
    const Uint8* keys = SDL_GetKeyboardState(NULL);
    if (keys[SDL_SCANCODE_W]){
        playerY -= playerSpeed;
    }
    if (keys[SDL_SCANCODE_S]){
        playerY += playerSpeed;
    }
    if (keys[SDL_SCANCODE_A]){
        playerX -= playerSpeed;
    }
    if (keys[SDL_SCANCODE_D]){
        playerX += playerSpeed;
    }
    if (keys[SDL_SCANCODE_R]){
        playerX = 3.5 * TILE_SIZE;
        playerY = 3.5 * TILE_SIZE;
    }
}
