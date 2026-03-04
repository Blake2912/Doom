#include <math.h>
#include "config.h"
#include <SDL2/SDL.h>
#include "raycast.h"
#include "map.h"


int determineRayMovement(float rayDir);
float determineDeltaDistance(float rayDir);
int determinePlayerPositionInGrid(float currentPos);
double computeInitialSideDistance(int mapPos, float playerPos, double deltaDist, float rayDir);
double computeWallCoordinates(float player, float rayDir, int mapPos);

void castRay(SDL_Renderer *renderer, float startX, float startY, float angle)
{
    float rayDirX = cos(angle);
    float rayDirY = sin(angle);

    int mapPlayerX = determinePlayerPositionInGrid(startX);
    int mapPlayerY = determinePlayerPositionInGrid(startY);

    double deltaDistX = determineDeltaDistance(rayDirX);
    double deltaDistY = determineDeltaDistance(rayDirY);

    int stepX = determineRayMovement(rayDirX);
    int stepY = determineRayMovement(rayDirY);

    double sideDistX = computeInitialSideDistance(mapPlayerX, startX, deltaDistX, rayDirX);
    double sideDistY = computeInitialSideDistance(mapPlayerY, startY, deltaDistY, rayDirY);

    int hit = 0;

    while (hit == 0)
    {
        if (sideDistX < sideDistY){
            sideDistX += deltaDistX;
            mapPlayerX += stepX;
        }
        else {
            sideDistY += deltaDistY;
            mapPlayerY += stepY;
        }

        if(mapPlayerX < 0 || mapPlayerX >= MAP_WIDTH ||
           mapPlayerY < 0 || mapPlayerY >= MAP_HEIGHT)
        {
            break;
        }

        if (worldMap[mapPlayerY][mapPlayerX] == 1)
        {
            hit = 1;
        }


    }

    double wallX = computeWallCoordinates(startX, rayDirX, mapPlayerX);
    double wallY = computeWallCoordinates(startY, rayDirY, mapPlayerY);

    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDrawLine(renderer, startX, startY, wallX, wallY);
}


double computeInitialSideDistance(int mapPos, float playerPos, double deltaDist, float rayDir)
{
    if(rayDir < 0)
        return (playerPos/TILE_SIZE - mapPos) * deltaDist;
    else
        return (mapPos + 1.0 - playerPos/TILE_SIZE) * deltaDist;
}

int determinePlayerPositionInGrid(float currentPos)
{
    return (int)(currentPos / TILE_SIZE);
}

float determineDeltaDistance(float rayDir)
{
    if(rayDir == 0)
            return 1e30;  // very large number
    return fabs(1 / rayDir);
}

int determineRayMovement(float rayDir)
{
    if (rayDir < 0) {
        return -1;
    }
    else {
        return 1;
    }
}

double computeWallCoordinates(float player, float rayDir, int mapPos)
{
    return player + rayDir * TILE_SIZE * mapPos;
}
