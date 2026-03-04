#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

extern float playerX;
extern float playerY;
extern float playerAngle;

void drawPlayer(SDL_Renderer* renderer);
void updatePlayer();


#endif
