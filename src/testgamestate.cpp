#include "testgamestate.h"
#include "gamestate.h"
#include "texture.h"
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>

TestGameState::TestGameState() {

}


TestGameState::~TestGameState() {
    delete mHowToTexture;
    delete mCountDownTexture;
    delete mResultTexture;
    delete mTitleReturnTexture;

    TTF_CloseFont(mTextFont);
}

void TestGameState::enter() {
    srand(time(NULL));
}

bool TestGameState::load(Graphics &graphics) {
    bool success = true;

    mTextFont = TTF_OpenFont("assets/fonts/compass-gold-v1/CompassGold.ttf", 24);
    if (mTextFont == NULL) {
        success = false;
    }
    else {
        mHowToTexture = new Texture();
        if (!mHowToTexture->loadFromText(graphics, mHowToStr, mTextFont, {0xFF, 0xFF, 0xFF})) {
            success = false;
        }
        mCountDownTexture = new Texture();
        mResultTexture = new Texture();
        mTitleReturnTexture = new Texture();
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
                            if (mReactionInputted)
                                setSwitchState(GAMESTATE_TITLE);
                            else if (mShowStimulus)
                                reactionInput();
                            break;
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

    if (mHowToVisible) {
        graphics.draw(Graphics::SCREEN_WIDTH / 2 - mHowToTexture->getWidth()/2,
                  Graphics::SCREEN_HEIGHT / 2 - mHowToTexture->getHeight() - 10,
                  mHowToTexture);

        mCountDownTexture->loadFromText(graphics, std::to_string((int)std::ceil(mCountDownT)), mTextFont, {0xFF, 0xFF, 0xFF});
        graphics.draw(Graphics::SCREEN_WIDTH / 2 - mCountDownTexture->getWidth()/2,
                      Graphics::SCREEN_HEIGHT / 2 - mCountDownTexture->getHeight()/2,
                      mCountDownTexture);
    }

    if (mShowStimulus) {
        graphics.drawRect(NULL, {0x10, 0xCC, 0x10});
    }

    if (mReactionInputted) {
        mResultTexture->loadFromText(graphics, std::to_string(mReactionT) + " seconds", mTextFont, {0xFF, 0xFF, 0xFF});
        graphics.draw(Graphics::SCREEN_WIDTH / 2 - mResultTexture->getWidth()/2,
                      Graphics::SCREEN_HEIGHT / 2 - mResultTexture->getHeight()/2,
                      mResultTexture);


        mTitleReturnTexture->loadFromText(graphics, mTitleReturnStr, mTextFont, {0xFF, 0xFF, 0xFF});
        graphics.draw(Graphics::SCREEN_WIDTH / 2 - mResultTexture->getWidth()/2,
                      Graphics::SCREEN_HEIGHT - mTitleReturnTexture->getHeight(),
                      mTitleReturnTexture);
    }

    graphics.flip();
}

void TestGameState::update(float delta) {
    if (mCountDownT > 0) {
        mCountDownT -= delta;
        if (mCountDownT <= 0) {
            // start test...
            mStimulusCountDownT = static_cast<float>(rand() % (MAX_RNG_TIME - MIN_RNG_TIME) + MIN_RNG_TIME);
            mHowToVisible = false;
        }
    }
    if (mStimulusCountDownT > 0) {
        mStimulusCountDownT -= delta;
        if (mStimulusCountDownT <= 0) {
            // show stimulus! Start count for reaction speed
            mShowStimulus = true;
        }
    }
    else if (mShowStimulus && !mReactionInputted) {
        mReactionT += delta;
    }
}

void TestGameState::reactionInput() {
    mReactionInputted = true;
}
