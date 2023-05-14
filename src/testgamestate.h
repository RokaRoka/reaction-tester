#ifndef TESTGAMESTATE_H
#define TESTGAMESTATE_H

#include <SDL2/SDL_ttf.h>
#include "gamestate.h"
#include "texture.h"

class TestGameState : public GameState {
public:
        TestGameState();
        ~TestGameState();

        bool load(Graphics &graphics);
        void input();
        void render(Graphics &graphics);
private:
        // fonts
        TTF_Font *mTextFont = NULL;

        // text graphics objects
        const std::string mHowToText = "When you see the screen turn green, press enter!";
        Texture *mHowToTexture = NULL;

        // Countdown stuff
        // Test Stimulus
        // Results
};

#endif
