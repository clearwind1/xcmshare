//
//  GameEvent.h
//  xcm
//  游戏消息事件处理
//  Created by Yang on 15/8/20.
//
//

#ifndef __xcm__GameEvent__
#define __xcm__GameEvent__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

// Steve
//struct
//{
//    const char* downtimeEvent /*= "DownTime_Event"*/;
//    
//}EventConfigTest;

class EventData
{
public:
    EventData():downtime(30){};
    
    int downtime;
};

class GameEvent : public Layer
{
public:
    GameEvent();
    ~GameEvent();
    
    static GameEvent* getInstance();
    
    //创建游戏事件并发布
    void createGameEvent(const char* eventname,void* eventdata);
    //创建游戏事件监听
    void addListenEvent(const std::string& eventName, const std::function<void(EventCustom*)>& callback, int eventPriority = 1);
    //移除游戏事件监听
    void removeListenEventByName(const char* eventName, ...);
    
};

#endif /* defined(__xcm__GameEvent__) */
