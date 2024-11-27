#pragma once
#include <vector>
class Subject;
class Observer
{
    private:
        std::vector<Subject*> m_Subjects;
    public:
        virtual void onNotify() = 0;
        void addSubject(Subject* subject)
        {
            m_Subjects.push_back(subject);
        }
};
class Subject
{
    private:
        std::vector<Observer*> m_Observers;
    public:
        void addObserver(Observer* observer)
        {
            m_Observers.push_back(observer);
        }
        void notify()
        {
            for (auto& observer : m_Observers)
            {
                observer->onNotify();
            }
        }
};
