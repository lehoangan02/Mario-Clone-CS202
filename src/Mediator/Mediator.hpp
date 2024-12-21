#pragma once
#include "../levels/Level.hpp"
#include <string>
class Mediator;
class Component
{
    protected:
    Mediator* m_Mediator;
    std::string m_Name;
    public:
    Component() = default;
    Component(Mediator* mediator) : m_Mediator(mediator) {};
    std::string getName() { return m_Name; }
    void setMediator(Mediator* mediator) { m_Mediator = mediator; }
    protected:
    void setName(std::string name) { m_Name = name; }

};
class Mediator
{
    friend class Component;
    public:
        virtual void notify(Component* sender, int EventCode) = 0;
}; 