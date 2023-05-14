#ifndef TITLEGAMESTATE_H
#define TITLEGAMESTATE_H

#include <SDL2/SDL_ttf.h>
#include "gamestate.h"
#include "texture.h"

class TitleGameState : public GameState {
public:
    TitleGameState();
    ~TitleGameState();

    bool load(Graphics &graphics);
    void render(Graphics &graphics);
    void input();
private:
// fonts
    TTF_Font *mTitleFont = NULL;
    TTF_Font *mTextFont = NULL;

// text graphics objects
    Texture *mTitleText = NULL;
    Texture *mTitleDesc = NULL;
};

#endif
