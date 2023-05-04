#include "graphics.h"

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
