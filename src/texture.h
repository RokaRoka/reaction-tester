#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "graphics.h"

class Graphics;

// Texture Class
class Texture {
public:
        Texture();
        ~Texture();

        void free();

        bool loadFromFile( Graphics &graphics, std::string path);
        bool loadFromText( Graphics &graphics, std::string text, TTF_Font *font, SDL_Color color);

        int getWidth();
        int getHeight();
        SDL_Texture* getTexture();

private:
        SDL_Texture* mTexture;

        int mWidth;
        int mHeight;
};

#endif
