//
//  BonusLayer.cpp
//  xcm
//
//  Created by Yang on 15/8/20.
//
//

#include "BonusLayer.h"
#include "GameInfo.h"
#include "GameData.h"
#include "RoleLayer.h"
#include "GameRecords.h"
#include "GameScene.h"

static BonusLayer* g_sShardBonus = nullptr;

BonusLayer* BonusLayer::getInstance()
{
    if(!g_sShardBonus)
    {
        g_sShardBonus = new (std::nothrow)BonusLayer();
    }
    
    return g_sShardBonus;
}

BonusLayer::BonusLayer()
{
    g_sShardBonus = this;
    m_pbonusinfo.isNew = false;
    this->scheduleUpdate();
}
BonusLayer::~BonusLayer()
{
    
}

void BonusLayer::showBonus(int type)
{
    const char* prizename[MAXROLE] = {  PrizeConfigowl,PrizeConfigsquirrel,PrizeConfigbigbear,PrizeConfigman,PrizeConfigman,PrizeConfigman,PrizeConfigfox,
                                        PrizeConfigmonkey,PrizeConfigowl,PrizeConfigsquirrel,PrizeConfigbigbear,PrizeConfigman,PrizeConfigfox,PrizeConfigmonkey,
                                        PrizeConfigowl,PrizeConfigsquirrel,PrizeConfigbigbear,PrizeConfigman,PrizeConfigman,PrizeConfigman,PrizeConfigfox,
                                        PrizeConfigmonkey,PrizeConfigowl,PrizeConfigsquirrel,PrizeConfigbigbear,PrizeConfigman,PrizeConfigfox,PrizeConfigmonkey};
    
    int prizetotalnum[MAXROLE] =
        {PrizeConfigowltatol,PrizeConfigsquirreltatol,PrizeConfigbigbeartatol,PrizeConfigmantatol,PrizeConfigmantatol,PrizeConfigmantatol,PrizeConfigfoxtatol,
        PrizeConfigmonkeytatol,PrizeConfigowltatol,PrizeConfigsquirreltatol,PrizeConfigbigbeartatol,PrizeConfigmantatol,PrizeConfigfoxtatol,PrizeConfigmonkeytatol,
        PrizeConfigowltatol,PrizeConfigsquirreltatol,PrizeConfigbigbeartatol,PrizeConfigmantatol,PrizeConfigmantatol,PrizeConfigmantatol,PrizeConfigfoxtatol,
        PrizeConfigmonkeytatol,PrizeConfigowltatol,PrizeConfigsquirreltatol,PrizeConfigbigbeartatol,PrizeConfigmantatol,PrizeConfigfoxtatol,PrizeConfigmonkeytatol};
    

    auto winsize = GameInfo::getInstance()->getGameDesignSize();
    
    int prizeid = GameData::getInstance()->getprizeid();
    CCLOG("prizeid=======%d",prizeid);
    
    auto prizesprite = Sprite::create();
    GameInfo::getInstance()->spriteSetPosition(NULL,prizesprite, 370, winsize.height*0.5);
    prizesprite->runAction(GameInfo::getInstance()->createAnitmation(prizename[prizeid], prizetotalnum[prizeid], -1, prizetotalnum[prizeid]/380.0));
    this->addChild(prizesprite,11);
    
    auto prizesprite2 = Sprite::create();
    GameInfo::getInstance()->spriteSetPosition(NULL,prizesprite2, 896, winsize.height*0.5);
    prizesprite2->setRotation(180);
    prizesprite2->runAction(GameInfo::getInstance()->createAnitmation(prizename[prizeid], prizetotalnum[prizeid], -1, prizetotalnum[prizeid]/380.0));
    this->addChild(prizesprite2,11);
    
}
void BonusLayer::removeBonus()
{
    this->removeAllChildren();
}

void BonusLayer::update(float dt)
{
#if GAMEEventMODE
#else
    m_pbonusinfo = SlaveMachine::getInstance()->getBonusDistributionInfo();
    GameData::getInstance()->setbonusinfo(m_pbonusinfo);
#endif
    
    if(!m_pbonusinfo.isNew)
        return;
    
    m_pbonusinfo.isNew = false;
#if GAMEEventMODE
#else
    SlaveMachine::getInstance()->setBonusDistributionInfo(m_pbonusinfo);
#endif
    
    GameScene::getInstance()->getShotlight()->setVisible(false);
    
    RoleLayer::getInstance()->setCover(true);
    
    //播放中奖音效
    GameInfo::getInstance()->playEffect(GameData::getInstance()->getprizeid());
    
    showBonus(0);
    RoleLayer::getInstance()->resumeRole(GameData::getInstance()->getprizeid());
    
}





