//
//  GameScene.cpp
//  xcm
//
//  Created by Yang on 15/8/14.
//
//

#include "GameScene.h"
#include "RoleLayer.h"
#include "GameEvent.h"
//#include "GameEventConfig.h"		// Steve
#include "GameData.h"
#include "GameRecords.h"
#include "GameTimeLayer.h"
#include "BonusLayer.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;

static GameScene* g_sSharedGamescene = nullptr;

GameScene* GameScene::getInstance()
{
    if(!g_sSharedGamescene)
    {
        g_sSharedGamescene = new (std::nothrow)GameScene();
    }
    
    return g_sSharedGamescene;
}

GameScene::GameScene()
:m_pangle(0)
,m_pangleSpeed(2)
{
    g_sSharedGamescene = this;
}
GameScene::~GameScene()
{
#if GAMEEventMODE
    GameEvent::getInstance()->removeListenEventByName(RUN_DATA_INFO_EVENT,NULL);
#endif
    m_pshotlightaction->release();
    m_prunlightaction->release();
}

Scene* GameScene::createScene()
{
    auto gamescene = Scene::create();
    gamescene->addChild(GameScene::create());
    return gamescene;
}

bool GameScene::init()
{
    if(!Layer::init())
        return false;
    
    
    srand(time(NULL));

#if GAMEEventMODE
#else
	// Steve - 打開串口
	this->addChild(SlaveMachine::getInstance());
	SlaveMachine::getInstance()->startSerialPortCommunication();
#endif
    
    //初始化游戏事件监听
    initlistenevent();
    //显示背景
    showGameBg();
    //时间节点
    this->addChild(GameTimeLayer::create(),12);
    //调用显示角色层
    this->addChild(RoleLayer::create(),11);
    //显示历史记录
    this->addChild(GameRecords::create(),9);
    //中奖显示
    this->addChild(BonusLayer::create(),30);
    
    //RoleLayer::getInstance()->pauseRole();
    
    //initGame();
    
    restartGame();
    
    this->scheduleUpdate();
    
    return true;
}

void GameScene::showGameBg()
{
    auto winsize = GameInfo::getInstance()->getGameDesignSize();
    
    int bgid = rand()%3;
    char buff[32];
    sprintf(buff, "gamebg%d.png",bgid);
    auto gamebgsprite = Sprite::create(buff);
    gamebgsprite->setPosition(Vec2(winsize.width*0.5,winsize.height*0.5));
    this->addChild(gamebgsprite,1);
    
    //添加知种背景小物件
    switch (bgid) {
        case 0:
            
            break;
        case 1:
        {
            auto swaction = GameInfo::getInstance()->createAnitmation("sw", 32, -1, 0.05);
            auto swsp = Sprite::create();
            this->addChild(swsp,1);
            swsp->runAction(swaction);
            
            auto coverbgsprite = Sprite::create("bgcover.png");
            coverbgsprite->setPosition(Vec2(winsize.width*0.5,winsize.height*0.5));
            this->addChild(coverbgsprite,1);
        }
            break;
        case 2:
            break;
            
        default:
            break;
    }
    
    //炮台
    m_pbottom = Sprite::createWithSpriteFrameName("bottom.png");
    GameInfo::getInstance()->spriteSetPosition(NULL, m_pbottom, winsize.width*0.5, winsize.height*0.5);
    this->addChild(m_pbottom,3);
    
    m_pshoottable = Sprite::createWithSpriteFrameName("shoottable.png");
    m_pshoottable->setAnchorPoint(Vec2(0.4,0.5));
    GameInfo::getInstance()->spriteSetPosition(NULL, m_pshoottable, winsize.width*0.5, winsize.height*0.5);
    this->addChild(m_pshoottable,20);
    
    m_pshotlight = Sprite::create();
    m_pshotlight->setVisible(false);
    m_pshotlight->setAnchorPoint(Vec2(0,0.5));
    GameInfo::getInstance()->spriteSetPosition(NULL, m_pshotlight, winsize.width*0.5, winsize.height*0.5);
    this->addChild(m_pshotlight,19);
    
    
    m_pshotlightaction = (ActionInterval*)GameInfo::getInstance()->createAnitmation("shoting", 14, 1, 0.05);
    m_pshotlightaction->retain();
    
    m_prunlightaction = (ActionInterval*)GameInfo::getInstance()->createAnitmation("light", 32, 1, 0.1);
    m_prunlightaction->retain();
    
    GameData::getInstance()->setprizeid(0);
    
//    m_prect = Sprite::create();
//    m_prect->setTextureRect(Rect(0, 0, 700, 1));
//    m_prect->setAnchorPoint(Vec2(0, 0.5));
//    GameInfo::getInstance()->spriteSetPosition(NULL, m_prect, winsize.width*0.5, winsize.height*0.5);
//    this->addChild(m_prect,21);
    
}

void GameScene::initlistenevent()
{
    m_pshoutdatainfo.isNew = false;
    m_poddsinfo.isNew = false;
    m_prundatainfo.isNew = false;
#if GAMEEventMODE
    GameEvent::getInstance()->addListenEvent(RUN_DATA_INFO_EVENT, CC_CALLBACK_1(GameScene::receiveRunEvent, this));
#endif
}

void GameScene::receiveRunEvent(cocos2d::EventCustom *event)
{
    m_prundatainfo = *((RunDataInfo*)event->getUserData());
    GameData::getInstance()->setprizeid(m_prundatainfo.toPosition);
}

void GameScene::initGame()
{
    m_bshoutdata = false;
    m_bRunFinish = false;
    m_pruncount = 0;
    m_pangleSpeed = 2.0;
#if GAMEDEBUG
    GameData::getInstance()->setcurdowntime(STARTDOWNTIME);
    this->schedule(schedule_selector(GameScene::downTimeEvent), 1.0f);
#endif
    
    RoleLayer::getInstance()->pauseRole();
    
    int bgmid = rand()%27;
    char buff[32];
    sprintf(buff, "bgm%d.mp3",bgmid);
    SimpleAudioEngine::getInstance()->playBackgroundMusic(buff,true);
    
    m_pbottom->runAction(RepeatForever::create(RotateBy::create(0.5, 10)));
    
}

void GameScene::downTimeEvent(float dt)
{
    int curtime = GameData::getInstance()->getcurdowntime();
    
   // CCLOG("curtime======%d",curtime);
    
    curtime--;
    
    if(curtime == 5)
    {
        SimpleAudioEngine::getInstance()->playBackgroundMusic("time.mp3",true);
    }
    
    if(curtime < 0)
    {
        m_pbottom->stopAllActions();
        GameRecords::getInstance()->setvisiable(false);
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        this->unschedule(schedule_selector(GameScene::downTimeEvent));
#if GAMEDEBUG
       
        shotlight();
        
        RunDataInfo rundatainfo;
        rundatainfo.isNew = true;
        rundatainfo.toPosition = rand()%28;
        rundatainfo.toPosition = 10;//test
        
        CCLOG("prizeid======%d",rundatainfo.toPosition);
        
#if GAMEEventMODE
        GameEvent::getInstance()->createGameEvent(RUN_DATA_INFO_EVENT, &rundatainfo);
#else
        SlaveMachine::getInstance()->setRunDataInfo(rundatainfo);
#endif
        
#endif
    }
    SecondInfo secondinfo;
    secondinfo.second = curtime;
    secondinfo.isNew = true;
#if GAMEEventMODE
    GameEvent::getInstance()->createGameEvent(SECOND_INFO_EVENT, &secondinfo);
#else
    SlaveMachine::getInstance()->setSecondInfo(secondinfo);
#endif
    
}

void GameScene::shotlight()
{
    m_pshotlight->setSpriteFrame("shoting0.png");
    m_pshotlight->setVisible(true);
    
    auto callback = CallFunc::create(CC_CALLBACK_0(GameScene::runlight, this));
    m_pshotlight->runAction(Sequence::create(m_prunlightaction,m_pshotlightaction,callback, NULL));
    
}
void GameScene::runlight()
{
   
    m_pshotlight->stopAllActions();
    
    RoleLayer::getInstance()->setIsruning(true);
    
    int bgmid = rand()%2;
    char buff[32];
    sprintf(buff, "run%d.mp3",bgmid);
    SimpleAudioEngine::getInstance()->playBackgroundMusic(buff,true);
    
    this->schedule(schedule_selector(GameScene::runupdate), 0.01);
}

void GameScene::tablerun()
{
    int rotacount = 3600;
    
    m_pshoottable->runAction(Repeat::create(RotateBy::create(0.01, 0.1),rotacount));
    m_pshotlight->runAction(Repeat::create(RotateBy::create(0.01, 0.1),rotacount));
    //m_prect->runAction(Repeat::create(RotateBy::create(0.01, 1),rotacount));
}

void GameScene::runupdate(float dt)
{
    
    if(m_pangle >= 360)
    {
        m_pangle = 0.0f;
        m_pruncount++;
    }
    
    m_pangle += m_pangleSpeed;
    m_pshoottable->setRotation(m_pangle);
    m_pshotlight->setRotation(m_pangle);
    
    int maxcount = 6;
    if(m_bshoutdata)
    {
        maxcount++;
    }
    
    if(m_pruncount < 2 && m_pangleSpeed < 6)
    {
        m_pangleSpeed += 0.1;
    }
    if(m_pruncount > 3 && m_pangleSpeed > 2)
    {
        m_pangleSpeed -= 0.1;
    }

    if(GameData::getInstance()->getprizeid() == 10 && m_pruncount >= 5 && RoleLayer::getInstance()->getrunroleID() == GameData::getInstance()->getprizeid())
    {
        m_pshotlight->setLocalZOrder(10);
        
        //RUN_END_COMMAND_EVENT
        //#if GAMEEventMODE
        if(m_bshoutdata)
        {
            GameEvent::getInstance()->createGameEvent(SHOUT_END_INFO_EVENT, NULL);
        }
        else
        {
            GameEvent::getInstance()->createGameEvent(RUN_END_INFO_EVENT, NULL);
            this->scheduleOnce(schedule_selector(GameScene::dispatchRunRLEndCommandEvent), 3.0f);	// Steve 發送紅黑跑燈完畢命令事件
        }
        
        //#endif
        RoleLayer::getInstance()->setIsruning(false);
        this->unschedule(schedule_selector(GameScene::runupdate));
#if GAMEEventMODE
        this->scheduleOnce(schedule_selector(GameScene::showbouns), 3);
#endif

    }
    else if(m_pruncount >= maxcount && RoleLayer::getInstance()->getrunroleID() == GameData::getInstance()->getprizeid())
    {
       
        m_pshotlight->setLocalZOrder(10);
        
        //RUN_END_COMMAND_EVENT
//#if GAMEEventMODE
        if(m_bshoutdata)
        {
            GameEvent::getInstance()->createGameEvent(SHOUT_END_INFO_EVENT, NULL);
        }
		else
		{
			GameEvent::getInstance()->createGameEvent(RUN_END_INFO_EVENT, NULL);
			this->scheduleOnce(schedule_selector(GameScene::dispatchRunRLEndCommandEvent), 3.0f);	// Steve 發送紅黑跑燈完畢命令事件
		}
           
//#endif
        RoleLayer::getInstance()->setIsruning(false);
        this->unschedule(schedule_selector(GameScene::runupdate));
#if GAMEEventMODE
        this->scheduleOnce(schedule_selector(GameScene::showbouns), 3);
#endif
    }
}

/*
 * Steve
 * 發佈紅黑跑燈完畢命令事件
 */
void GameScene::dispatchRunRLEndCommandEvent(float dt)
{
	log("TWinDebug: GameScene dispatchRunRLEndCommandEvent()");
	GameEvent::getInstance()->createGameEvent(RUN_RL_END_INFO_EVENT, NULL);
}

void GameScene::showbouns(float dt)
{
    m_pshotlight->setVisible(false);
    RoleLayer::getInstance()->setCover(true);
    BonusLayer::getInstance()->showBonus(0);
    RoleLayer::getInstance()->resumeRole(GameData::getInstance()->getprizeid());
    
    //播放中奖音效
    GameInfo::getInstance()->playEffect(GameData::getInstance()->getprizeid());
    
    if(!m_bshoutdata)
        this->scheduleOnce(schedule_selector(GameScene::endgame), 3);
    else
        m_bshoutdata = false;
}

void GameScene::endgame(float dt)
{
    m_poddsinfo.isNew = true;
}

void GameScene::restartGame()
{
    initGame();
    m_pshotlight->stopAllActions();
    m_pshotlight->setLocalZOrder(19);
    m_pshotlight->setVisible(false);
    BonusLayer::getInstance()->removeBonus();
    //RoleLayer::getInstance()->resumeRole(-1);
    GameTimeLayer::getInstance()->resetTime();
    GameRecords::getInstance()->setvisiable(true);
    RoleLayer::getInstance()->setCover(false);
    
    int movenum = 4+rand()%2;
    for(int i = 0;i < movenum;i++)
    {
        int addnum = 1+rand()%3;
        int moveid = (i+addnum)*(1+rand()%7);
        moveid = moveid%MAXROLE;
        RoleLayer::getInstance()->resumeRole(moveid);
    }
    
}

void GameScene::update(float dt)
{
#if GAMEEventMODE
#else
    m_prundatainfo = SlaveMachine::getInstance()->getRunDataInfo();
    m_poddsinfo = SlaveMachine::getInstance()->getOddsInfo();
    m_pshoutdatainfo = SlaveMachine::getInstance()->getShoutDataInfo();
#endif
    
    if(m_pshoutdatainfo.isNew)
    {
        m_pshoutdatainfo.isNew = false;
        m_bshoutdata = true;
#if GAMEEventMODE
#else
        SlaveMachine::getInstance()->setShoutDataInfo(m_pshoutdatainfo);
#endif
        
        RoleLayer::getInstance()->setIsruning(true);
        this->schedule(schedule_selector(GameScene::runupdate), 0.01);
        
        GameData::getInstance()->setprizeid(m_pshoutdatainfo.toPosition);
    }
    
    if(m_poddsinfo.isNew)
    {
        m_poddsinfo.isNew = false;
#if GAMEEventMODE
#else
        SlaveMachine::getInstance()->setOddsInfo(m_poddsinfo);
#endif
        restartGame();
    }
    
    if(!m_prundatainfo.isNew)
        return;
    
    m_prundatainfo.isNew = false;
    
    GameData::getInstance()->setprizeid(m_prundatainfo.toPosition);
#if GAMEEventMODE
#else
    SlaveMachine::getInstance()->setRunDataInfo(m_prundatainfo);
#endif
    
    shotlight();
    
    RoleLayer::getInstance()->pauseRole();
}





