// MenuState.cpp
#include "MenuState.hpp"

void MenuState::handle(Application& app) {
    app.menu.draw();
    int tab = app.menu.handle();
    if (app.menu.getIsChange()) {
        app.menu.setIsChange(false);
        app.game = Game(app.menu.characterMenu(), app.menu.levelMenu());
        app.setState(new GameState());
    }
    if (tab == 11) {
        app.game.change("continue.txt");
        app.setState(new GameState());
    }
    if (tab == 10) {
        app.game = Game(app.menu.characterMenu(), app.menu.levelMenu());
        app.setState(new GameState());
    }
}