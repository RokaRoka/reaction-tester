#include "titlegamestate.h"

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
// #include <SDL2/SDL_ttf.h>

TitleGameState::TitleGameState() {

}


TitleGameState::~TitleGameState() {
    // Free loaded textures
    delete mTitleText;
    delete mTitleDesc;

    // Free fonts
    TTF_CloseFont(mTitleFont);
    TTF_CloseFont(mTextFont);
}

void TitleGameState::render(Graphics &graphics) {
    GameState::render(graphics);
    // Start a new draw
    graphics.clear();

    // draw title
    graphics.draw(Graphics::SCREEN_WIDTH / 2 - mTitleText->getWidth()/2,
                  mTitleText->getHeight(),
                  mTitleText);

    // draw desc
    graphics.draw(Graphics::SCREEN_WIDTH / 2 - mTitleDesc->getWidth()/2,
                  Graphics::SCREEN_HEIGHT - mTitleDesc->getHeight() - 48,
                  mTitleDesc);

    graphics.flip();
}

void TitleGameState::input() {
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
                        case SDLK_ESCAPE:
                                setSwitchState(GAMESTATE_QUIT);
                                return;
                        case SDLK_RETURN:
                                setSwitchState(GAMESTATE_TEST);
                                return;
                        }
                }
        }
}

bool TitleGameState::load(Graphics &graphics) {
  bool success = true;
  mTitleFont = TTF_OpenFont("assets/fonts/compass-gold-v1/CompassGold.ttf", 52);
  if (mTitleFont == NULL) {
    printf("Font Compass Gold could not init for gTitleFont. TTF Error: %s\n",
           TTF_GetError());
    success = false;
  }
  else {
    mTextFont = TTF_OpenFont("assets/fonts/compass-gold-v1/CompassGold.ttf", 24);
    if (mTitleFont == NULL) {
      printf("Font Compass Gold could not init for gTextFont. TTF Error: %s\n",
             TTF_GetError());
      success = false;
    }
    else {
      // create title text
      SDL_Color color = {0xFF, 0xFF, 0xFF};
      mTitleText = new Texture();
      mTitleText->loadFromText(graphics, "Reaction Tester (TM)", mTitleFont, color);
      if (mTitleText == NULL) {
        printf("Title text creation failed :(\n");
        success = false;
      }
      else {
        // create title text
        mTitleDesc = new Texture();
        mTitleDesc->loadFromText(graphics, "Test your reaction time! Press enter to begin!",
                                 mTextFont, color);
        if (mTitleText == NULL) {
          printf("Title description text creation failed :(\n");
          success = false;
        }
      }
    }
  }

  return success;
}
