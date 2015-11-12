//
//  LogoLayer.cpp
//  xcm
//
//  Created by Yang on 15/8/13.
//
//

#include "LogoLayer.h"
#include "GameInfo.h"
//#include "GameEventConfig.h"		// Steve
#include "GameScene.h"
#include "GameEvent.h"
#include "MyUtility.h"
#include "GameData.h"
#include "SimpleAudioEngine.h"
#include <thread>

using namespace CocosDenshion;

Scene* LogoLayer::createScene()
{
    Scene* scene = Scene::create();
    scene->addChild(LogoLayer::create());
    return scene;
}

LogoLayer::~LogoLayer()
{
#if GAMEEventMODE
    GameEvent::getInstance()->removeListenEventByName(VERSION_INFO_EVENT,LAN_TEST_INFO_EVENT,SCENE_INFO_EVENT,NULL);
#endif
}

bool LogoLayer::init()
{
    if(!Layer::init())
        return false;
    
	// Steve - 打開串口
#if GAMEEventMODE
#else
	this->addChild(SlaveMachine::getInstance());
	SlaveMachine::getInstance()->startSerialPortCommunication();
#endif
    
    //初始化资源名
    initreloadname();
    
    m_iNumberOfLoaded = 0;

	m_bIsChangeScene = false;		// Steve
	m_bIsLoadingComplete = false;	// Steve - 資源加載是否完成
	this->scheduleUpdate();			// Steve

    initEventListen();
    
//    auto t = std::thread(&LogoLayer::loadingAudio,this);
//    t.detach();
    
    //加载资源
    loadingtexture();
    
    //显示加载资源背景
    auto winsize = GameInfo::getInstance()->getGameDesignSize();
    
    auto logosprite = Sprite::create("beginBg.png");
    logosprite->setPosition(Vec2(winsize.width*0.5, winsize.height*0.5));
    this->addChild(logosprite);
    
#if GAMEEventMODE
    m_pversioninfo.isNew = true;
    m_pversioninfo.versionNumber = 1;

	m_pMachineIDInfo.isNew = true;
	m_pMachineIDInfo.machineID = 1;
#endif
    
    return true;
}

//测试换场景事件发布。。。正式版请去掉
void LogoLayer::testevent(float dt)
{
    SceneInfo sceneinfo;
    sceneinfo.isNew = true;
    sceneinfo.sceneID = Game_Scene;
#if GAMEEventMODE
    GameEvent::getInstance()->createGameEvent(SCENE_INFO_EVENT, &sceneinfo);
#else
    SlaveMachine::getInstance()->setSceneInfo(sceneinfo);
#endif
}

void LogoLayer::initEventListen()
{
#if GAMEEventMODE
    GameEvent::getInstance()->addListenEvent(VERSION_INFO_EVENT, CC_CALLBACK_1(LogoLayer::showlogo, this));
    GameEvent::getInstance()->addListenEvent(LAN_TEST_INFO_EVENT, CC_CALLBACK_1(LogoLayer::updatalable, this));
    GameEvent::getInstance()->addListenEvent(SCENE_INFO_EVENT, CC_CALLBACK_1(LogoLayer::changescene, this));
#endif
    
    m_psceneinfo.isNew = false;
    m_pversioninfo.isNew = false;
}

void LogoLayer::initreloadname()
{
    reloadPvrPlists[0] = "rolestand.";
    reloadPvrPlists[1] = "TimeImage.";
    reloadPvrPlists[2] = "GameElement.";
    reloadPvrPlists[3] = "prizebear.";
    reloadPvrPlists[4] = "prizefox.";
    reloadPvrPlists[5] = "prizesquirrel.";
    reloadPvrPlists[6] = "prizeman.";
    reloadPvrPlists[7] = "prizeowl.";
    reloadPvrPlists[8] = "prizemonkey.";
    reloadPvrPlists[9] = "shotlight.";
    reloadPvrPlists[10] = "sweffect.";
}
void LogoLayer::loadingtexture()
{
    Director::getInstance()->getTextureCache()->addImageAsync(reloadPvrPlists[m_iNumberOfLoaded] + "pvr.ccz",CC_CALLBACK_1(LogoLayer::loadingTextureCallback, this));
}
void LogoLayer::loadingTextureCallback(cocos2d::Texture2D *texture)
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(reloadPvrPlists[m_iNumberOfLoaded].append("plist"), texture);
    m_iNumberOfLoaded++;
    
    if(m_iNumberOfLoaded >= TotalResfile)
    {
        //资源加载完成
        CCLOG("load res is done!");
        //dispatchLoadingCompleteCommand();
		m_bIsLoadingComplete = true;	// Steve - 資源加載完成
    }
    else
    {
        loadingtexture();
        CCLOG("loading....%d%%",(int)(m_iNumberOfLoaded*100/TotalResfile));
    }
    
}

void LogoLayer::loadingAudio()
{
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic( "bgm0.mp3" );
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic( "bgm1.mp3" );
}

void LogoLayer::showlogo(EventCustom* event)
{
    
    VersionInfo ver = *((VersionInfo*)(event->getUserData()));
    
    auto verlable = LabelTTF::create(__String::createWithFormat("Version:%d",ver.versionNumber)->getCString(), "Arial", 40);
    GameInfo::getInstance()->spriteSetPosition(nullptr, verlable, 1000, 670);
    this->addChild(verlable,12);
    
    //淡出动画
    //logosprite->runAction(Sequence::create(DelayTime::create(1.0), FadeOut::create(2.5),NULL));
    
}

void LogoLayer::showlable()
{
    
}
void LogoLayer::updatalable(cocos2d::EventCustom *event)
{
    
}

void LogoLayer::changescene(cocos2d::EventCustom *event)
{
    m_psceneinfo = *((SceneInfo*)event->getUserData());
    
	log("TWinDebug: LogoLayer changescene() 完畢");
}

// Steve
void LogoLayer::dispatchLoadingCompleteCommand()
{
	log("TWinDebug: LogoLayer dispatchLoadingCompleteCommand()");
	EventCustom eventCustom = EventCustom(LOADING_COMPLETE_INFO_EVENT);			// Steve 改define名字
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&eventCustom);

#if GAMEDEBUG
    testevent(0);
#endif
    
}

void LogoLayer::isChangeScene()
{
    
    if(!m_psceneinfo.isNew)
        return;
    
    
    m_bIsLoadingComplete = false;
    CCLOG("seneinfo====%d",m_psceneinfo.sceneID);
    
    m_psceneinfo.isNew = false;
#if GAMEEventMODE
#else
    SlaveMachine::getInstance()->setSceneInfo(m_psceneinfo);
#endif
    
    Scene* scene;
    
    switch (m_psceneinfo.sceneID) {
        
        // Steve - sceneinfo.scene == 0 才是 GameScene
        case Game_Scene:
        log("TWinDebug: LogoLayer changescene() scene %d", m_psceneinfo.sceneID);
        m_bIsChangeScene = true;
        scene = GameScene::createScene();
        break;
        
        default:
        break;
    }
    
    if(!scene)
        return;
    
    Director::getInstance()->replaceScene(scene);
    
}

// Steve
void LogoLayer::update(float dt)
{
	// Steve - 如果資源加載完成就不斷發送"資源加載完成"命令給下位機
	if (m_bIsLoadingComplete == true) {
		dispatchLoadingCompleteCommand();
	}
    
	// Steve 機台ID
    if(m_pMachineIDInfo.isNew)
    {
        GameData::getInstance()->setmachineID(m_pMachineIDInfo.machineID);
    }

#if GAMEEventMODE
#else
    m_pversioninfo = SlaveMachine::getInstance()->getVersionInfo();
	m_pMachineIDInfo = SlaveMachine::getInstance()->getMachineIDInfo();		// Steve 機台ID
    m_psceneinfo = SlaveMachine::getInstance()->getSceneInfo();
#endif
    isChangeScene();
}









