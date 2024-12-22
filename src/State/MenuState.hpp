
#ifndef MenuState_hpp
#define MenuState_hpp

#include "State.hpp"
#include "../Application/Application.hpp"

class MenuState : public State {
public:
    void handle(Application& app) override;
};

#endif /* MenuState_hpp */