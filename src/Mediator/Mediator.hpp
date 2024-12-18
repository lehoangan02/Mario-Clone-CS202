#pragma once
#include "../levels/Level.hpp"
#include <string>
class Mediator;
class Component
{
    private:
    Mediator* m_Mediator;
    std::string m_Name;
    public:
    Component() = default;
    Component(Mediator* mediator) : m_Mediator(mediator) {};
    std::string getName() { return m_Name; }
    private:
    void setName(std::string name) { m_Name = name; }
    void setMediator(Mediator* mediator) { m_Mediator = mediator; }

};
class Mediator
{
    friend class Component;
    private:
        virtual void notify(Component* sender,  LEVEL_RETURN_MESSAGE EventCode) = 0;
}; 