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
#include "gamestate.h"
#include "graphics.h"
#include "texture.h"
#include "titlegamestate.h"

// Starts SDL, creates a window, inits SDL_image and SDL_ttf
bool init();
// Closes SDL
void close();

const int MS_UPDATE_FRAME = 32; // 30 FPS

GameState* gCurrentState = NULL;

int main(int argc, char *argv[]) {
        if (!init()) {
                printf("SDL was not able to init :(\n");
        }
        else {
                // Initialize Graphics
                Graphics graphics = Graphics();
                if (!graphics.init()) {
                        printf("Graphics was not able to initialize :(\n");
                }
                else {
                        // Set new GameState
                        gCurrentState = new TitleGameState();
                        if ( !gCurrentState->load(graphics) ) {
                                printf("Media was not able to be loaded :(\n");
                        }
                        else {
                                // set clear color to black (my poor eyes, its 1:30am)
                                graphics.setClearColor({0,0,0});
                                // set draw dirty, for first draw
                                bool quit = false;
                                while (!quit) {
                                        GameState* newState = gCurrentState->input();
                                        if (newState != NULL) {
                                                delete newState;
                                                quit = true;
                                        }
                                        gCurrentState->render(graphics);
                                        SDL_Delay(MS_UPDATE_FRAME);
                                }
                        }
                        delete gCurrentState;
                }
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
