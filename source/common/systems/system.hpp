#pragma once

#include "events.hpp"

#include <set>
#include <queue>

namespace our
{
    template<typename T>
    class IObserver {
    public:
        virtual void update(const T& event) = 0;
        virtual ~IObserver() {}; // destructor must be virtual don't change this
    };

    template<typename T>
    class ISubject {
    public:
        virtual void addObserver(IObserver<T>* observer) = 0;
        virtual void removeObserver(IObserver<T>* observer) = 0;
        virtual void notify(const T& event) = 0;
        virtual ~ISubject() {};  // destructor must be virtual don't change this
    };


    // A base class for all systems
    // The communication between systems is done using observer pattern so that systems are loosly coupled
    // In an ECS all the logic is performed by the systems using data from components, thus there's no dependency 
    // between systems, but in some cases there's a need of direct communication between systems 
    // but a key design rule of ECS is that systems should not depend on each other and thus 
    // I decided the best way to handle the communication is by means of observer design pattern.
    // A system can observe multiple systems and a system can have multiple observers (It's both a subject and observer),
    // although this may seem like multiple inheritance (which i think it's a very bad idea), it's not it just implements 2 interfaces.
    // The class can be implemented without using interfaces but I decided to implement it this way because
    // maybe at some point a class rather than system will be interested in the events fired by a system.
    class System : public IObserver<Event>, public ISubject<Event> {
    protected:
        // A list of registered systems to notify when an event occurs.
        // The registered systems are the systems who care about an event fired by this system.
        std::set<IObserver<Event>*> observers;
        // Each frame the events that the system care about are stored here (if any).
        // This queue must be emptied each frame.
        std::queue<Event> eventQueue;
        // A list of systems that the current system is observing.
        // This list is kept in case a system wants to unregister from a particular system dynamically.
        std::set<ISubject<Event>*> subjects;
        
    public:
        // The most important functions are notify, and listen

        // Receive an event comming from a system that the current system is observing and add it to the event queue
        // to be handled later by the system, that is, systems handle incoming events asynchronously.
        void update(const Event& event) {
            eventQueue.push(event);
        }
        // Register an observer (usually a system) to notify when an event occur.
        void addObserver(IObserver<Event>* observer) {
            observers.insert(observer);
        }
        // Unregister an observer so that he no longer receives events.
        void removeObserver(IObserver<Event>* observer) {
            observers.erase(observer);
        }
        // Notify all observers when an event occur.
        // Use this function to anounce the occurence of some event.
        void notify(const Event& event) {
            for(IObserver<Event>* observer: observers){
                observer->update(event);
            }
        }

        // Listen to the events fired by a subject (usually a system).
        void listen(ISubject<Event>* system) {
            system->addObserver(this);
            subjects.insert(system);
        }
        // Unsubscribe from a subject so I no longer listen to the fired events.
        void detach(ISubject<Event>* system) {
            system->removeObserver(this);
            subjects.erase(system);
        }
    };

}