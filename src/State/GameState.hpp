// GameState.hpp
#ifndef GameState_hpp
#define GameState_hpp

#include "State.hpp"
#include "../Application/Application.hpp"

class GameState : public State {
public:
    void handle(Application& app) override;
};

#endif /* GameState_hpp */