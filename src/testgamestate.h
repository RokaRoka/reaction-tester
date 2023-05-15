#ifndef TESTGAMESTATE_H
#define TESTGAMESTATE_H

#include <SDL2/SDL_ttf.h>
#include "gamestate.h"
#include "texture.h"

class TestGameState : public GameState {
public:
        TestGameState();
        ~TestGameState();

        void enter();

        bool load(Graphics &graphics);
        void input();
        void render(Graphics &graphics);
        void update(float delta);
private:
        // fonts
        TTF_Font *mTextFont = NULL;

        // Countdown and HowTo
        const std::string mHowToStr = "When you see the screen turn green, press enter!";
        Texture *mHowToTexture = NULL;
        float mCountDownT = 5;
        Texture *mCountDownTexture = NULL;
        bool mHowToVisible = true;

        // Test Stimulus
        float mStimulusCountDownT = 0;
        const int MAX_RNG_TIME = 10;
        const int MIN_RNG_TIME = 4;
        bool mShowStimulus = false;
        float mReactionT = 0;
        bool mReactionInputted = false;

        // Results
        Texture *mResultTexture = NULL;
        const std::string mTitleReturnStr = "Your result! Press enter to return to title.";
        Texture *mTitleReturnTexture = NULL;

        void reactionInput();
};

#endif
