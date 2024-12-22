// State.hpp
#ifndef State_hpp
#define State_hpp

class Application;

class State {
public:
    virtual ~State() {}
    virtual void handle(Application& app) = 0;
};

#endif /* State_hpp */