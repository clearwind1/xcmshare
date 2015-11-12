//
//  GameEvent.cpp
//  xcm
//
//  Created by Yang on 15/8/20.
//
//

#include "GameEvent.h"

static GameEvent* g_sShardGameEvent = nullptr;

GameEvent* GameEvent::getInstance()
{
    if(!g_sShardGameEvent)
    {
        g_sShardGameEvent = new (std::nothrow)GameEvent();
    }
    
    return g_sShardGameEvent;
}

GameEvent::GameEvent()
{
    g_sShardGameEvent = this;
}
GameEvent::~GameEvent()
{
    
}

void GameEvent::createGameEvent(const char* eventname, void* eventdata)
{
    EventCustom event(eventname);
    event.setUserData(eventdata);
    _eventDispatcher->dispatchEvent(&event);
}

void GameEvent::addListenEvent(const std::string& eventName, const std::function<void(EventCustom*)>& callback, int eventPriority)
{
    EventListenerCustom* _listener = EventListenerCustom::create(eventName, callback);
    _eventDispatcher->addEventListenerWithFixedPriority(_listener, eventPriority);
}
void GameEvent::removeListenEventByName(const char* eventName, ...)
{
    const char* name = eventName;
    va_list ap;
    va_start(ap, eventName);
    
    while(true)
    {
        
        //CCLOG("removelisten_name=======%s",name);
        _eventDispatcher->removeCustomEventListeners(name);
        
        name = va_arg(ap, const char*);
        
        if(name == NULL)
            break;
        
    }
    
    va_end(ap);
    
}





