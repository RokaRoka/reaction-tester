// C++ libs
#include <SDL2/SDL_pixels.h>
#include <cstdint>
#include <cstdlib>
#include <string>

// Third Party lib
#include <SDL2/SDL.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_events.h>

// our libs
#include "gameloop.h"

// Starts SDL, creates a window, inits SDL_image and SDL_ttf
bool init();
// Closes SDL
void close();


int main(int argc, char *argv[]) {
        if (!init()) {
                printf("SDL was not able to init :(\n");
        }
        else {
                GameLoop gameLoop = GameLoop();
                gameLoop.doLoop();
        }

        close();
        return 0;
}

bool init() {
        bool success = true;

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
                printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
                success = false;
        }
        else {
                // Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags)) {
                        printf("SDL Image could not init. Wah woh. IMG error: %s\n",
                               IMG_GetError());
                        success = false;
                }
                else {
                        // Initialize TTF Loading
                        if (TTF_Init() == -1) {
                                printf("SDL TTF could not init. Wah woh. TTF error: %s\n",
                                       TTF_GetError());
                                success = false;
                        }
                }
        }
        return success;
}

void close() {
  // Quit SDL subsystems
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}
