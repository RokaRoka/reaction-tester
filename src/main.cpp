// C++ libs
#include <SDL2/SDL_error.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <stdio.h>
#include <string>

// Third Party lib
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

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

Graphics::Graphics() {}

Graphics::~Graphics() {
        close();
}

bool Graphics::init() {
        bool success = true;
        // set up window + renderer
        Uint32 winFlags = SDL_WINDOW_ALLOW_HIGHDPI;
        int err = SDL_CreateWindowAndRenderer(Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT,
                                              winFlags, &this->mWindow, &this->mRenderer);
        if (err == -1) {
                printf("Window could not be initialized. SDL says %s\n", SDL_GetError());
                success = false;
        }
        else {
                SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        }
        return success;
}

void Graphics::close() {
        // Destroy window
        SDL_DestroyRenderer(mRenderer);
        SDL_DestroyWindow(mWindow);
        mWindow = NULL;
        mRenderer = NULL;
}

void Graphics::flip() {
        SDL_RenderPresent(mRenderer);
}

void Graphics::clear() {
        SDL_RenderClear(mRenderer);
}

SDL_Renderer* Graphics::getRenderer() {
        return mRenderer;
}


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

Texture::Texture() {
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

Texture::~Texture() {
  free();
}

bool Texture::loadFromText( Graphics &graphics, std::string text, TTF_Font *font, SDL_Color color) {
  free();

  bool success = true;
  SDL_Surface *textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
  if (textSurface == NULL) {
    printf("Unable to render text surface! SDL_ttf Error: %s\n",
           TTF_GetError());
    success = false;
  } else {
    mWidth = textSurface->w;
    mHeight = textSurface->h;
    // Create texture from surface pixels
    mTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), textSurface);
    if (mTexture == NULL) {
      printf("Unable to create texture from rendered text! SDL Error: %s\n",
             SDL_GetError());
      success = false;
    }
    // Get rid of old surface
    SDL_FreeSurface(textSurface);
  }
  return success;
}

bool Texture::loadFromFile( Graphics &graphics, std::string path) {
  free();

  bool success = true;
  SDL_Surface *surface = IMG_Load(path.c_str());
  if (surface == NULL) {
    printf("Unable to render text surface! SDL_img Error: %s\n",
           IMG_GetError());
    success = false;
  } else {
    mWidth = surface->w;
    mHeight = surface->h;
    mTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), surface);
    if (mTexture == NULL) {
      printf("Unable to create texture from image surface! SDL Error: %s\n",
             SDL_GetError());
      success = false;
    }
    // optimizedSurface = SDL_ConvertSurface(textSurface, gScreenSurface->format, 0);
    // if (optimizedSurface == NULL) {
    //   printf("Unable to optimize text surface. SDL_ttf Error: %s\n", SDL_GetError());
    // }
    SDL_FreeSurface(surface);
  }
  return success;
}

void Texture::free() {
  SDL_DestroyTexture(mTexture);
  mTexture = NULL;
  mWidth = 0;
  mHeight = 0;
}

int Texture::getWidth() {
  return mWidth;
}

int Texture::getHeight() {
  return mHeight;
}

SDL_Texture* Texture::getTexture() {
  return mTexture;
}

// Starts SDL, creates a window, inits SDL_image and SDL_ttf
bool init();
// Loads all media to be used in the program
bool loadMedia(Graphics &graphics);
// Frees loaded media and closes SDL
void close();

// fonts
TTF_Font *gTitleFont = NULL;
TTF_Font *gTextFont = NULL;

// text graphics objects
Texture *tTitleText = NULL;
Texture *tTitleDesc = NULL;

int main(int argc, char *argv[]) {
        if ( !init() ) {
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
                                SDL_Delay(3000);
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
