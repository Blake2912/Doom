#include <math.h>
#include "config.h"
#include <SDL2/SDL.h>
#include "raycast.h"
#include "map.h"



int determineRayMovement(float rayDir);
double determineDeltaDistance(float rayDir);
int determinePlayerPositionInGrid(float currentPos);
double computeInitialSideDistance(int mapPos, float pos, double deltaDist, float rayDir);

struct rayCastInfo rayCastV2(float startX, float startY, float angle)
{

    /* convert player position to grid space */
    float posX = startX / TILE_SIZE;
    float posY = startY / TILE_SIZE;

    /* ray direction */
    float rayDirX = cos(angle);
    float rayDirY = sin(angle);

    /* current grid square */
    int mapX = (int)posX;
    int mapY = (int)posY;

    /* length of ray from one x or y side to next */
    double deltaDistX = determineDeltaDistance(rayDirX);
    double deltaDistY = determineDeltaDistance(rayDirY);

    /* step direction */
    int stepX = determineRayMovement(rayDirX);
    int stepY = determineRayMovement(rayDirY);

    /* distance from player to first grid boundary */
    double sideDistX = computeInitialSideDistance(mapX, posX, deltaDistX, rayDirX);
    double sideDistY = computeInitialSideDistance(mapY, posY, deltaDistY, rayDirY);

    int hit = 0;
    int side = 0;

    double wallX;

    while (!hit)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }

        if (mapX < 0 || mapX >= MAP_WIDTH ||
            mapY < 0 || mapY >= MAP_HEIGHT)
        {
            break;
        }

        if (worldMap[mapY][mapX] > 0)
        {
            hit = 1;
        }
    }

    double perpWallDist;

    if (side == 0)
        perpWallDist = (mapX - posX + (1 - stepX) / 2.0) / rayDirX;
    else
        perpWallDist = (mapY - posY + (1 - stepY) / 2.0) / rayDirY;

    /* exact hit point in world space */
    float hitX = startX + rayDirX * perpWallDist * TILE_SIZE;
    float hitY = startY + rayDirY * perpWallDist * TILE_SIZE;


    if (side == 0){
        wallX = posY + perpWallDist * rayDirY;
    }
    else {
        wallX = posX + perpWallDist * rayDirX;
    }

    wallX -= floor(wallX);

    struct rayCastInfo returnObj;

    returnObj.distance = perpWallDist;
    returnObj.side = side;
    returnObj.mapX = mapX;
    returnObj.mapY = mapY;
    returnObj.wallX = wallX;

    return returnObj;
}

void castRay(SDL_Renderer *renderer, float startX, float startY, float angle)
{
    /* convert player position to grid space */
    float posX = startX / TILE_SIZE;
    float posY = startY / TILE_SIZE;

    /* ray direction */
    float rayDirX = cos(angle);
    float rayDirY = sin(angle);

    /* current grid square */
    int mapX = (int)posX;
    int mapY = (int)posY;

    /* length of ray from one x or y side to next */
    double deltaDistX = determineDeltaDistance(rayDirX);
    double deltaDistY = determineDeltaDistance(rayDirY);

    /* step direction */
    int stepX = determineRayMovement(rayDirX);
    int stepY = determineRayMovement(rayDirY);

    /* distance from player to first grid boundary */
    double sideDistX = computeInitialSideDistance(mapX, posX, deltaDistX, rayDirX);
    double sideDistY = computeInitialSideDistance(mapY, posY, deltaDistY, rayDirY);

    int hit = 0;
    int side = 0;

    /* ===== DDA LOOP ===== */
    while (!hit)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }

        if (mapX < 0 || mapX >= MAP_WIDTH ||
            mapY < 0 || mapY >= MAP_HEIGHT)
        {
            break;
        }

        if (worldMap[mapY][mapX] > 0)
        {
            hit = 1;
        }
    }

    /* perpendicular wall distance */
    double perpWallDist;

    if (side == 0)
        perpWallDist = (mapX - posX + (1 - stepX) / 2.0) / rayDirX;
    else
        perpWallDist = (mapY - posY + (1 - stepY) / 2.0) / rayDirY;

    /* exact hit point in world space */
    float hitX = startX + rayDirX * perpWallDist * TILE_SIZE;
    float hitY = startY + rayDirY * perpWallDist * TILE_SIZE;

    /* draw ray */
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderDrawLine(
        renderer,
        (int)startX,
        (int)startY,
        (int)hitX,
        (int)hitY
    );
}


double computeInitialSideDistance(int mapPos, float pos, double deltaDist, float rayDir)
{
    if (rayDir < 0)
        return (pos - mapPos) * deltaDist;
    else
        return (mapPos + 1.0 - pos) * deltaDist;
}


int determinePlayerPositionInGrid(float currentPos)
{
    return (int)(currentPos / TILE_SIZE);
}


double determineDeltaDistance(float rayDir)
{
    if (rayDir == 0)
        return 1e30;

    return fabs(1 / rayDir);
}


int determineRayMovement(float rayDir)
{
    if (rayDir < 0)
        return -1;
    else
        return 1;
}
