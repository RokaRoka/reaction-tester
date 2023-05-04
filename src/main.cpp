// C++ libs
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
#include "graphics.h"
#include "texture.h"

// Starts SDL, creates a window, inits SDL_image and SDL_ttf
bool init();
// Loads all media to be used in the program
bool loadMedia(Graphics &graphics);
// Frees loaded media and closes SDL
void close();

void render();

const int MS_UPDATE_FRAME = 32; // 30 FPS

// fonts
TTF_Font *gTitleFont = NULL;
TTF_Font *gTextFont = NULL;

// text graphics objects
Texture *tTitleText = NULL;
Texture *tTitleDesc = NULL;

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
                        if ( !loadMedia(graphics) ) {
                                printf("Media was not able to be loaded :(\n");
                        }
                        else {
                                bool quit = false;
                                while (!quit) {
                                        // check for events
                                        SDL_Event event;
                                        while(SDL_PollEvent(&event)) {
                                                // if quit event, leave gameloop
                                                if (event.type == SDL_QUIT) {
                                                        quit = true;
                                                }
                                        }
                                        render();
                                        SDL_Delay(MS_UPDATE_FRAME);
                                }
                        }
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

bool loadMedia(Graphics &graphics) {
  bool success = true;
  gTitleFont = TTF_OpenFont("assets/fonts/compass-gold-v1/CompassGold.ttf", 52);
  if (gTitleFont == NULL) {
    printf("Font Compass Gold could not init for gTitleFont. TTF Error: %s\n",
           TTF_GetError());
    success = false;
  }
  else {
    gTextFont = TTF_OpenFont("assets/fonts/compass-gold-v1/CompassGold.ttf", 24);
    if (gTitleFont == NULL) {
      printf("Font Compass Gold could not init for gTextFont. TTF Error: %s\n",
             TTF_GetError());
      success = false;
    }
    else {
      // create title text
      SDL_Color color = {0, 0, 0};
      tTitleText = new Texture();
      tTitleText->loadFromText(graphics, "Reaction Tester (TM)", gTitleFont, color);
      if (tTitleText == NULL) {
        printf("Title text creation failed :(\n");
        success = false;
      }
      else {
        // create title text
        tTitleDesc = new Texture();
        tTitleDesc->loadFromText(graphics, "Test your reaction time! Press enter to begin!", gTextFont, color);
        if (tTitleText == NULL) {
          printf("Title description text creation failed :(\n");
          success = false;
        }
      }
    }
  }

  return success;
}

void close() {
  // Free loaded textures
  delete tTitleText;
  delete tTitleDesc;

  // Free fonts
  TTF_CloseFont(gTitleFont);
  TTF_CloseFont(gTextFont);

  // Quit SDL subsystems
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void render(Graphics &graphics) {
        // Start a new draw
        graphics.clear();

        SDL_Rect rect;
        rect.w = tTitleText->getWidth();
        rect.h = tTitleText->getHeight();
        rect.x = Graphics::SCREEN_WIDTH / 2 - rect.w/2;
        rect.y = rect.h;
        SDL_RenderCopy(graphics.getRenderer(), tTitleText->getTexture(), NULL, &rect);

        SDL_Rect rect2;
        rect2.w = tTitleDesc->getWidth();
        rect2.h = tTitleDesc->getHeight();
        rect2.x = Graphics::SCREEN_WIDTH / 2 - rect2.w/2;
        rect2.y = Graphics::SCREEN_HEIGHT - rect2.h - 48;
        SDL_RenderCopy(graphics.getRenderer(), tTitleDesc->getTexture(), NULL, &rect2);
        graphics.flip();
}
