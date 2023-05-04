#include "texture.h"

#include <SDL2/SDL_image.h>

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
