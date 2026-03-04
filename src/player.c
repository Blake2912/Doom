#include <SDL2/SDL.h>
#include "config.h"

float playerX = 3.5 * TILE_SIZE;
float playerY = 3.5 * TILE_SIZE;

float playerSpeed = 2.5f;
float playerAngle = 0;

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

    int playerSize = 5;
    // Boundary conditions
    if (playerX < playerSize) {
        playerX = playerSize;
    }
    if (playerY < playerSize){
        playerY = playerSize;
    }
    if (playerX > MAP_WIDTH * TILE_SIZE - playerSize){
        playerX = MAP_WIDTH * TILE_SIZE - playerSize;
    }

    if (playerY > MAP_HEIGHT * TILE_SIZE - playerSize){
        playerY = MAP_WIDTH * TILE_SIZE - playerSize;
    }

    if (keys[SDL_SCANCODE_LEFT]){
        playerAngle -= 0.05;
    }
    if (keys[SDL_SCANCODE_RIGHT]){
        playerAngle += 0.05;
    }
}
