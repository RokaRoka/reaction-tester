#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>

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

        SDL_Renderer* getRenderer();
private:
        SDL_Window *mWindow = NULL;
        SDL_Renderer *mRenderer = NULL;
};

#endif
