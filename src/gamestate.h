#ifndef GAMESTATE_H
#define GAMESTATE_H

class Graphics;

class GameState {
public:
        GameState();
        ~GameState();

        enum GameStateSwitch { GAMESTATE_QUIT = -1, GAMESTATE_NONE, GAMESTATE_TITLE, GAMESTATE_TEST };

        virtual void enter();
        virtual void exit();

        virtual bool load(Graphics &graphics);

        virtual void update(float delta);
        virtual void render(Graphics &graphics);
        virtual void input();

        GameState::GameStateSwitch getSwitchState();
        void setSwitchState(GameState::GameStateSwitch newState);

private:
        GameStateSwitch mSwitchState = GAMESTATE_NONE;
};


#endif
