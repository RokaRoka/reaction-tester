#ifndef GAMESTATE_H
#define GAMESTATE_H

class Graphics;

class GameState {
public:
        GameState();
        ~GameState();

        virtual void enter();
        virtual void exit();

        virtual void update(float delta);
        virtual void render(Graphics &graphics);
        virtual GameState* input();

        virtual bool load(Graphics &graphics);
private:
};

#endif
