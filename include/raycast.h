#ifndef RAYCAST_H
#define RAYCAST_H


#include <SDL2/SDL.h>

struct rayCastInfo {
    float distance;
    int side;
    float mapX;
    float mapY;
    float wallX;
};

void castRay(SDL_Renderer * renderer, float startX, float startY, float angle);
struct rayCastInfo rayCastV2(float startX, float startY, float angle);

#endif
