#include "gamestate.h"

#include "graphics.h"

GameState::GameState() {
}

GameState::~GameState() {
}

void GameState::enter() {
}

void GameState::exit() {
}

void GameState::update(float delta) {
}

void GameState::render(Graphics &graphics) {
}

void GameState::input() {
}

bool GameState::load(Graphics &graphics) {
    return false;
}

GameState::GameStateSwitch GameState::getSwitchState() {
    return mSwitchState;
}

void GameState::setSwitchState(GameState::GameStateSwitch newState) {
    if (mSwitchState != GAMESTATE_QUIT)
        mSwitchState = newState;
}
