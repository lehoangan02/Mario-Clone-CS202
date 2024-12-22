// GameState.cpp
#include "GameState.hpp"

void GameState::handle(Application& app) {
    app.game.start();
    if (app.game.getState() == LEVEL_RETURN_MESSAGE::QUIT) {
        app.setState(new MenuState());
    }
}