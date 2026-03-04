#include <math.h>
#include "config.h"
#include <SDL2/SDL.h>
#include "raycast.h"
#include "map.h"


void castRay(SDL_Renderer *renderer, float startX, float startY, float angle)
{
    float rayX = startX;
    float rayY = startY;

    float stepSize = 2.0;

    float dirX = cos(angle);
    float dirY = sin(angle);

    while (1)
    {
        rayX += dirX * stepSize;
        rayY += dirY * stepSize;

        int mapX = rayX / TILE_SIZE;
        int mapY = rayY / TILE_SIZE;

        if (mapX < 0 || mapY < 0 || mapX >= MAP_WIDTH || mapY >= MAP_HEIGHT){
            break;
        }

        if (worldMap[mapY][mapX] == 1) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            SDL_RenderDrawLine(renderer, startX, startY, rayX, rayY);
            break;
        }
    }
}
