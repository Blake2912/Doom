#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

extern float playerX;
extern float playerY;

void drawPlayer(SDL_Renderer* renderer);
void updatePlayer();


#endif
