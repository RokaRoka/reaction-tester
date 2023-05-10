#include "gamestate.h"

#include "graphics.h"

GameState::GameState() {
}

GameState::~GameState() {
    exit();
}

void GameState::enter() {
}

void GameState::exit() {
}

void GameState::update(float delta) {
}

void GameState::render(Graphics &graphics) {
}

GameState* GameState::input() {
    return nullptr;
}

bool GameState::load(Graphics &graphics) {
    return false;
}
