#include "config.h"
#include <SDL2/SDL.h>



int worldMap[8][8] = {
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,0,1},
    {1,0,1,0,1,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,1,0,1,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1}
};

void drawMap(SDL_Renderer* renderer)
{
    for(int y = 0; y < MAP_HEIGHT; y++)
    {
        for(int x = 0; x < MAP_WIDTH; x++)
        {
            SDL_Rect tile = {
                x * TILE_SIZE,
                y * TILE_SIZE,
                TILE_SIZE,
                TILE_SIZE
            };

            if(worldMap[y][x] == 1)
                SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
            else
                SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);

            SDL_RenderFillRect(renderer, &tile);
        }
    }
}
