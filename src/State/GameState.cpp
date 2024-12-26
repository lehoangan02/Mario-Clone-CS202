// GameState.cpp
#include "GameState.hpp"

void GameState::handle(Application& app) {
    // std::cout << "1" << std::endl;
    if (app.game.getState() == LEVEL_RETURN_MESSAGE::QUIT) {
        std::cout << "Quitting game" << std::endl;
        app.setState(new MenuState());
        app.game.reset();
        return;
    }    
    if (app.getStateType() == StateType::GAME_STATE)
    {
        std::cout << "Game state" << std::endl;
    }
    if (app.getStateType() == StateType::MENU_STATE)
    {
        std::cout << "Menu state" << std::endl;
    }
    app.game.start();
    
}