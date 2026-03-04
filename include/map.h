#ifndef MAP_H
#define MAP_H

#include "config.h"
#include<SDL2/SDL.h>

extern int worldMap[MAP_HEIGHT][MAP_WIDTH];
void drawMap(SDL_Renderer *renderer);

#endif
