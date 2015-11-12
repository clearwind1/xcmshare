//
//  GameTimeLayer.cpp
//  xcm
//
//  Created by Yang on 15/8/29.
//
//

#include "GameTimeLayer.h"
#include "GameEvent.h"
#include "GameInfo.h"
#include "GameData.h"

static GameTimeLayer* g_sharedGameTime = nullptr;

GameTimeLayer::GameTimeLayer()
{
    g_sharedGameTime = this;
}
GameTimeLayer::~GameTimeLayer()
{
#if GAMEEventMODE
    GameEvent::getInstance()->removeListenEventByName(SECOND_INFO_EVENT,NULL);
#endif
}

GameTimeLayer* GameTimeLayer::getInstance()
{
    if(!g_sharedGameTime)
    {
        g_sharedGameTime = new (std::nothrow)GameTimeLayer();
    }
    
    return g_sharedGameTime;
}

bool GameTimeLayer::init()
{
    
    if(!Layer::init())
        return false;
    
    m_pNumNodeLeft = Node::create();
    m_pNumNodeLeft->setRotation(90);
    m_pNumNodeLeft->setAnchorPoint(Vec2(0.5,0.5));
    GameInfo::getInstance()->spriteSetPosition(NULL, (Sprite*)m_pNumNodeLeft, 370, 360);
    this->addChild(m_pNumNodeLeft,10);
    
    m_pNumNodeRight = Node::create();
    m_pNumNodeRight->setRotation(270);
    m_pNumNodeRight->setAnchorPoint(Vec2(0.5,0.5));
    GameInfo::getInstance()->spriteSetPosition(NULL, (Sprite*)m_pNumNodeRight, 896, 360);
    this->addChild(m_pNumNodeRight,10);
    
	// Steve 隱藏倒計時框
    ////倒计时框
    //auto timeframeleft = Sprite::createWithSpriteFrameName("timeframe.png");
    //GameInfo::getInstance()->spriteSetPosition(NULL, timeframeleft, 370, 360);
    //this->addChild(timeframeleft);
    //
    //auto timeframeright = Sprite::createWithSpriteFrameName("timeframe.png");
    //GameInfo::getInstance()->spriteSetPosition(NULL, timeframeright, 896, 360);
    //this->addChild(timeframeright);
    
    initlistenevent();
    
    resetTime();
    
    this->scheduleUpdate();
    
    return true;
}

void GameTimeLayer::initlistenevent()
{
#if GAMEEventMODE
    GameEvent::getInstance()->addListenEvent(SECOND_INFO_EVENT, CC_CALLBACK_1(GameTimeLayer::downTime, this));
#endif
    m_psecondinfo.isNew = false;
}

void GameTimeLayer::downTime(cocos2d::EventCustom *event)
{
    m_psecondinfo = *((SecondInfo*)event->getUserData());
}

void GameTimeLayer::showTime(int curtime)
{
    
    if(curtime < 0)
        return;
    
    GameInfo::getInstance()->createSpriteNum(m_pNumNodeLeft,"num", curtime);
    GameInfo::getInstance()->createSpriteNum(m_pNumNodeRight,"num", curtime);
}

void GameTimeLayer::setTimeVisble(bool bshow)
{
    this->setVisible(bshow);
}

void GameTimeLayer::showDownTime()
{
    
    if(!m_psecondinfo.isNew)
        return;
    
    m_psecondinfo.isNew = false;
#if GAMEEventMODE
#else
    SlaveMachine::getInstance()->setSecondInfo(m_psecondinfo);
#endif
    
    int curdowntime;
    curdowntime = m_psecondinfo.second;
    
    if(curdowntime >= 0)
    {
        GameData::getInstance()->setcurdowntime(curdowntime);
        showTime(curdowntime);
    }
    else
    {
        setTimeVisble(false);
    }
}

void GameTimeLayer::resetTime()
{
    m_psecondinfo.isNew = false;
    setTimeVisble(true);
    showTime(STARTDOWNTIME);
}

void GameTimeLayer::update(float dt)
{
#if GAMEEventMODE
#else
    m_psecondinfo = SlaveMachine::getInstance()->getSecondInfo();
#endif
    showDownTime();
}





