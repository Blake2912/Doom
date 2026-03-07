#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#define TEX_WIDTH 64
#define TEX_HEIGHT 64


extern Uint32 wallTexture[TEX_WIDTH * TEX_HEIGHT];

void loadTexture();

#endif
