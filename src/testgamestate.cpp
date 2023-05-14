#include "testgamestate.h"
#include "gamestate.h"
#include <SDL2/SDL_ttf.h>

TestGameState::TestGameState() {

}


TestGameState::~TestGameState() {
    delete mHowToTexture;

    TTF_CloseFont(mTextFont);
}

bool TestGameState::load(Graphics &graphics) {
    bool success = true;

    mTextFont = TTF_OpenFont("assets/fonts/compass-gold-v1/CompassGold.ttf", 16);
    if (mTextFont == NULL) {
        success = false;
    }
    else {
        mHowToTexture = new Texture();
        if (!mHowToTexture->loadFromText(graphics, mHowToText, mTextFont, {0xFF, 0xFF, 0xFF})) {
            success = false;
        }
    }

    return success;
}

void TestGameState::input() {
        // check for events
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
                // if quit event, leave gameloop
                if (event.type == SDL_QUIT) {
                    setSwitchState(GAMESTATE_QUIT);
                    return;
                }
                else if (event.type == SDL_KEYDOWN) {
                        switch (event.key.keysym.sym) {
                        case SDLK_RETURN:
                        case SDLK_ESCAPE:
                            setSwitchState(GAMESTATE_QUIT);
                            return;
                        }
                }
        }
}


void TestGameState::render(Graphics &graphics) {
    GameState::render(graphics);
    // Start a new draw
    graphics.clear();

    graphics.draw(Graphics::SCREEN_WIDTH / 2 - mHowToTexture->getWidth()/2,
                  mHowToTexture->getHeight(),
                  mHowToTexture);

    graphics.flip();
}
