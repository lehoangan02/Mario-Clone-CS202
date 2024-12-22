// State.hpp
#ifndef State_hpp
#define State_hpp

class Application;
enum class StateType {
    MENU_STATE,
    GAME_STATE
};
class State {
public:
    virtual ~State() {}
    virtual void handle(Application& app) = 0;
    StateType getType() { return type; }
private:
    StateType type;
};

#endif /* State_hpp */