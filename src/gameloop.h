#ifndef GAMELOOP_H
#define GAMELOOP_H

#include "gamestate.h"

class GameLoop {
    public:
        void doLoop();
    private:
        const int MS_UPDATE_FRAME = 32; // 30 FPS
        GameState* mGameState;
};

#endif
