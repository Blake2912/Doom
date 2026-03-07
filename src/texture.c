#include "texture.h"

Uint32 wallTexture[TEX_WIDTH * TEX_HEIGHT];

void loadTexture() {
    for (int y = 0; y < TEX_HEIGHT; y++) {
        for (int x = 0; x < TEX_WIDTH; x++) {
            int xorcolor = (x * 256 / TEX_WIDTH) * (y * 256 / TEX_HEIGHT);
            int ycolor = y * 256 / TEX_HEIGHT;
            int xycolor = y * 128 / TEX_HEIGHT + x * 128/ TEX_WIDTH;

            wallTexture[TEX_WIDTH * y + x] = (xycolor << 16) | (xorcolor << 8) | ycolor;
        }
    }
}
