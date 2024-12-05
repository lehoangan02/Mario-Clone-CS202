#pragma once

#include <string>
class Component
{
    private:
    Mediator* m_Mediator;
    std::string m_Name;
    public:
    Component(Mediator* mediator) : m_Mediator(mediator) {};
};
class Mediator
{
    friend class Component;
    private:
        virtual void notify(Component* sender, std::string Event) = 0;
}; 