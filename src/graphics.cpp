#include "graphics.h"
#include "texture.h"

#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <iterator>
#include <string>

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
                clear();
                SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
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
        SDL_SetRenderDrawColor( mRenderer, mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a );
        SDL_RenderClear(mRenderer);
}

void Graphics::draw(int x, int y, Texture *texture) {
        // set render color to white for draw operation
        SDL_Rect rect = {x, y, texture->getWidth(), texture->getHeight()};
        SDL_RenderCopy(mRenderer, texture->getTexture(), NULL, &rect);
}

void Graphics::drawRect(SDL_Rect *rect, SDL_Color color) {
        SDL_SetRenderDrawColor( mRenderer, color.r, color.g, color.b, color.a );
        SDL_RenderFillRect(mRenderer, rect);
        SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
}

void Graphics::setClearColor(SDL_Color color) {
        mClearColor = color;
}

SDL_Renderer* Graphics::getRenderer() {
        return mRenderer;
}
