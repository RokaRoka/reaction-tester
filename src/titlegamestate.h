#ifndef TITLEGAMESTATE_H
#define TITLEGAMESTATE_H

#include <SDL2/SDL_ttf.h>
#include "gamestate.h"
#include "texture.h"

class TitleGameState : public GameState {
public:
    TitleGameState();
    ~TitleGameState();

    void render(Graphics &graphics);
    GameState* input();
    bool load(Graphics &graphics);
private:
// fonts
    TTF_Font *mTitleFont = NULL;
    TTF_Font *mTextFont = NULL;

// text graphics objects
    Texture *mTitleText = NULL;
    Texture *mTitleDesc = NULL;
};

#endif
