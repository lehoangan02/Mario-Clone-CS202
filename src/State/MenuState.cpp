// MenuState.cpp
#include "MenuState.hpp"

void MenuState::handle(Application& app) {
    // if (app.getStateType() == StateType::MENU_STATE)
    // {
    //     std::cout << "Menu state" << std::endl;
    // }
    app.menu.draw();
    int tab = app.menu.handle();
    if (app.menu.getIsChange()) {
        app.menu.setIsChange(false);
        app.game.changeMenu(app.menu.characterMenu(), app.menu.levelMenu());
    }
    if (tab == 11) {
        std::cout << "New game" << std::endl;
        app.game.change("continue.txt");
        app.setState(new GameState());
        app.menu.reset();
    }
    if (tab == 10) {
        std::cout << "New game 2 " << std::endl;
        app.game.changeMenu(app.menu.characterMenu(), app.menu.levelMenu());
        app.setState(new GameState());
        app.menu.reset();
    }
    
}