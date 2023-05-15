#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <unordered_map>

class Texture;

class Graphics {
        public:
                static const int SCREEN_WIDTH = 640;
                static const int SCREEN_HEIGHT = 480;

                Graphics();
                ~Graphics();

                bool init();
                void close();

                void flip();
                void clear();

                bool loadFont( std::string name, int size );

                void draw(int x, int y, Texture *texture);
                void drawRect(SDL_Rect *rect, SDL_Color color);

                void setClearColor(SDL_Color color);

                SDL_Renderer* getRenderer();
        private:
                SDL_Window *mWindow = NULL;
                SDL_Renderer *mRenderer = NULL;

                SDL_Color mClearColor = {0xFF, 0xFF, 0xFF};
};

#endif
