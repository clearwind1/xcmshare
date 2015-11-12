//
//  GameRecords.cpp
//  xcm
//
//  Created by Yang on 15/8/28.
//
//

#include "GameRecords.h"
#include "GameEvent.h"
#include "GameInfo.h"
#include "MyUtility.h"

static GameRecords* g_sSharedGameRecords = nullptr;

GameRecords* GameRecords::getInstance()
{
    if(!g_sSharedGameRecords)
    {
        g_sSharedGameRecords = new (std::nothrow)GameRecords();
    }
    
    return g_sSharedGameRecords;
}

GameRecords::GameRecords()
{
    g_sSharedGameRecords = this;
}
GameRecords::~GameRecords()
{
#if GAMEEventMODE
    GameEvent::getInstance()->removeListenEventByName(HISTORY_INFO_EVENT,NULL);
#endif
}

bool GameRecords::init()
{
    if(!Layer::init())
        return false;
    
    m_phistoryinfo.isNew = false;
#if GAMEEventMODE
    GameEvent::getInstance()->addListenEvent(HISTORY_INFO_EVENT, CC_CALLBACK_1(GameRecords::receiveEvent, this));
#endif
    
    initrecords(true);
    
    this->scheduleUpdate();
    
    return true;
}


void GameRecords::initrecords(bool e)
{
    this->removeAllChildren();

#if GAMEDEBUG
    for(int i = 0;i < MAXRECORDS;i++)
    {
        m_phistoryinfo.histories[i] = i;
    }
#endif
    
	// Steve - 這邊先繞過沒綠色狐狸的問題  還有直接先初始化m_phistoryinfo
    //int posTid[28] = {0,1,2,4,3,5,11,8,7,9,10,5,11,8,7,9,10,5,3,4,12,6,0,1,2,4,12,6};
    if(e)
    {
        for (int i = 0; i < MAXRECORDS; i++)
        {
            m_phistoryinfo.histories[i] = i;
        }
    }
	
	int posTid[28] = { 0, 1, 2, 4, 3, 5, 11, 8, 7, 9, 10, 5, 12, 8, 7, 9, 10, 5, 3, 4, 11, 6, 0, 1, 2, 4, 12, 6 };
    
    for(int i = 0;i < MAXRECORDS;i++)
    {
        int recordnum = m_phistoryinfo.histories[i];
        
        auto recordsprite = Sprite::createWithSpriteFrameName(__String::createWithFormat("his%d.png",posTid[recordnum])->getCString());
        GameInfo::getInstance()->spriteSetPosition(NULL, recordsprite, 279+67*i, 219);
        recordsprite->setRotation(180);
        this->addChild(recordsprite,1,i);
        
        auto recordanimation = Sprite::createWithSpriteFrameName("hisAnimation.png");
        GameInfo::getInstance()->spriteSetPosition(recordsprite, recordanimation, recordsprite->getContentSize().width*0.5, recordsprite->getContentSize().height*0.5);
        recordsprite->addChild(recordanimation);
        
        recordanimation->runAction(RepeatForever::create(RotateBy::create(0.1, 10)->reverse()));
        
    }
    
    for(int i = 0;i < MAXRECORDS;i++)
    {
        int recordnum = m_phistoryinfo.histories[i];
        
        auto recordsprite = Sprite::createWithSpriteFrameName(__String::createWithFormat("his%d.png",posTid[recordnum])->getCString());
        GameInfo::getInstance()->spriteSetPosition(NULL, recordsprite, 279+67*i, 502);
        this->addChild(recordsprite);
        
        auto recordanimation = Sprite::createWithSpriteFrameName("hisAnimation.png");
        GameInfo::getInstance()->spriteSetPosition(recordsprite, recordanimation, recordsprite->getContentSize().width*0.5, recordsprite->getContentSize().height*0.5);
        recordsprite->addChild(recordanimation);
        
        recordanimation->runAction(RepeatForever::create(RotateBy::create(0.1, 10)->reverse()));
    }
    
}

void GameRecords::setvisiable(bool e)
{
    if(!e)
    {
        this->setZOrder(-10);
    }
    else
    {
        this->setZOrder(9);
    }
}

void GameRecords::receiveEvent(cocos2d::EventCustom *event)
{
    m_phistoryinfo = *((HistoryInfo*)event->getUserData());
}

void GameRecords::showrecords()
{
    if(!m_phistoryinfo.isNew)
        return;
    
    m_phistoryinfo.isNew = false;
#if GAMEEventMODE
#else
    SlaveMachine::getInstance()->setHistoryInfo(m_phistoryinfo);
#endif
    
    initrecords(false);
    
}

void GameRecords::update(float dt)
{
#if GAMEEventMODE
#else
    m_phistoryinfo = SlaveMachine::getInstance()->getHistoryInfo();
#endif
    
    showrecords();
}



