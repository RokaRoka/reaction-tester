#include "gameloop.h"

#include "graphics.h"
#include "gamestate.h"
#include "titlegamestate.h"
#include "testgamestate.h"

void GameLoop::doLoop() {
                // Initialize Graphics
                Graphics graphics = Graphics();
                if (!graphics.init()) {
                        printf("Graphics was not able to initialize :(\n");
                }
                else {
                        // set clear color to black (my poor eyes, its 1:30am)
                        graphics.setClearColor({0,0,0});

                        // Set to title!
                        mGameState = new TitleGameState();
                        if ( !mGameState->load(graphics) ) {
                                printf("Media was not able to be loaded :(\n");
                        }
                        else {
                                mGameState->enter();
                                // set draw dirty, for first draw
                                bool quit = false;
                                while (!quit) {
                                        float delta = MS_UPDATE_FRAME;
                                        mGameState->input();
                                        mGameState->update(delta);
                                        mGameState->render(graphics);
                                        SDL_Delay(MS_UPDATE_FRAME);

                                        // check for a change in state
                                        GameState::GameStateSwitch switchState = mGameState->getSwitchState();
                                        if (switchState != GameState::GAMESTATE_NONE) {
                                                // exit the old state
                                                mGameState->exit();
                                                delete mGameState;
                                                switch (switchState) {
                                                        case GameState::GAMESTATE_QUIT:
                                                                quit = false;
                                                                return;
                                                        case GameState::GAMESTATE_TITLE:
                                                                mGameState = new TitleGameState();
                                                                break;
                                                        case GameState::GAMESTATE_TEST:
                                                                //switch gamestate
                                                                mGameState = new TestGameState();
                                                                break;
                                                }
                                                // load new state
                                                if (!mGameState->load(graphics)) {
                                                        printf("Media was not able to be for GameState :(\n");
                                                        delete mGameState;
                                                        return;
                                                }
                                                else {
                                                        // enter new state if load went well
                                                        mGameState->enter();
                                                }
                                        }
                                }
                        }
                }
}
