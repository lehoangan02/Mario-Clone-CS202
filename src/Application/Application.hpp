// Application.hpp
#ifndef Application_hpp
#define Application_hpp

#include "../State/State.hpp"
#include "../State/GameState.hpp"
#include "../State/MenuState.hpp"
#include "GUI.hpp"
#include "Game.hpp"

class Application {
private:
    State* currentState;
public:
    Menu menu;
    Game game;

    Application();
    ~Application();
    void setState(State* state);
    void run();
};

#endif /* Application_hpp */