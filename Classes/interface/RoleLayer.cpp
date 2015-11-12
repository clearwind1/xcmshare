//
//  RoleLayer.cpp
//  xcm
//
//  Created by Yang on 15/8/20.
//
//

#include "RoleLayer.h"
#include "GameScene.h"
#include "GameData.h"

// Steve
const char* rolename[MAXROLE] = {   RoleConfigowl,RoleConfigsquirrel,RoleConfigbigbear,RoleConfigmanl,RoleConfigmanm,RoleConfigmanr,RoleConfigfox,
                                    RoleConfigmonkey,RoleConfigowl,RoleConfigsquirrel,RoleConfigbigbear,RoleConfigmanr,RoleConfigfox,RoleConfigmonkey,
                                    RoleConfigowl,RoleConfigsquirrel,RoleConfigbigbear,RoleConfigmanr,RoleConfigmanm,RoleConfigmanl,RoleConfigfox,
                                    RoleConfigmonkey,RoleConfigowl,RoleConfigsquirrel,RoleConfigbigbear,RoleConfigmanl,RoleConfigfox,RoleConfigmonkey};

static RoleLayer* s_SharedRoleLayer = nullptr;

RoleLayer* RoleLayer::getInstance()
{
    if(!s_SharedRoleLayer)
    {
        s_SharedRoleLayer = new (std::nothrow)RoleLayer();
    }
    
    return s_SharedRoleLayer;
}

RoleLayer::RoleLayer()
:isruning(false)
{
    s_SharedRoleLayer = this;
}
RoleLayer::~RoleLayer()
{
    
}

bool RoleLayer::init()
{
    if(!Layer::init())
        return false;
    
    showAllRole();
    
    m_pCover = GameInfo::getInstance()->createRect(Rect(0, 0, GameInfo::getInstance()->getGameDesignSize().width, GameInfo::getInstance()->getGameDesignSize().height), 0, GameInfo::getInstance()->getGameDesignSize().height);
    m_pCover->setColor(Color3B::BLACK);
    m_pCover->setOpacity(120);
    this->addChild(m_pCover,20);
    m_pCover->setVisible(false);
    
    this->scheduleUpdate();
    
    return true;
}

void RoleLayer::showAllRole()
{
    
    float roleposition[MAXROLE][2] = {{183,94},{297,115},{410,112},{525,112},{640,112},{755,112},{878,116},{989,110},{1091,95},{1169,151},{1163,252},{1168,364},
                                      {1167,478},{1174,578},{1091,626},{979,605},{867,609},{750,608},{635,608},{525,608},{397,605},{289,612},{181,627},{109,568},
                                      {115,467},{109,354},{111,241},{104,141}};
    
	// Steve
    int roletotalnum[MAXROLE] =
                {RoleConfigowltatol,RoleConfigsquirreltatol,RoleConfigbigbeartatol,RoleConfigmantatol,RoleConfigmantatol,RoleConfigmantatol,RoleConfigfoxtatol,
                RoleConfigmonkeytatol,RoleConfigowltatol,RoleConfigsquirreltatol,RoleConfigbigbeartatol,RoleConfigmantatol,RoleConfigfoxtatol,RoleConfigmonkeytatol,
                RoleConfigowltatol,RoleConfigsquirreltatol,RoleConfigbigbeartatol,RoleConfigmantatol,RoleConfigmantatol,RoleConfigmantatol,RoleConfigfoxtatol,
                RoleConfigmonkeytatol,RoleConfigowltatol,RoleConfigsquirreltatol,RoleConfigbigbeartatol,RoleConfigmantatol,RoleConfigfoxtatol,RoleConfigmonkeytatol};
    
    // Steve
    const char* tablename[MAXROLE] = {  RoleConfiggreentable,RoleConfiggreentable,RoleConfiggreentable,RoleConfigcyantable,RoleConfigorgtable,RoleConfigbluetable,RoleConfigredtable,
                                        RoleConfigredtable,RoleConfigredtable,RoleConfigredtable,RoleConfigredtable,RoleConfigbluetable,RoleConfigredtable,RoleConfigredtable,
                                        RoleConfigredtable,RoleConfigredtable,RoleConfigredtable,RoleConfigbluetable,RoleConfigorgtable,RoleConfigcyantable,RoleConfiggreentable,
                                        RoleConfiggreentable,RoleConfiggreentable,RoleConfiggreentable,RoleConfiggreentable,RoleConfigbluetable,RoleConfiggreentable,RoleConfiggreentable};
    
    float tableposition[MAXROLE][2] = { {184,41},{298,41},{411,41},{525,41},{640,41},{755,41},{866,41},{979,41},{1092,41},{1237,152},{1237,255},{1237,359},
                                        {1237,464},{1237,568},{1091,678},{977,678},{865,678},{750,678},{637,678},{525,678},{410,678},{298,678},{182,678},{41,567},
                                        {41,462},{41,358},{41,254},{41,150}};
    
    int rotation = 0;
    
    for(int i = 0;i < MAXROLE;i++)
    {
        m_prole[i] = Sprite::create();
        GameInfo::getInstance()->spriteSetPosition(NULL, m_prole[i], roleposition[i][0], roleposition[i][1]);
        m_prole[i]->runAction(GameInfo::getInstance()->createAnitmation(rolename[i], roletotalnum[i], -1, roletotalnum[i]/380.0));
        this->addChild(m_prole[i],11);
        
        m_ptable[i] = Sprite::createWithSpriteFrameName(tablename[i]);
        GameInfo::getInstance()->spriteSetPosition(NULL, m_ptable[i], tableposition[i][0], tableposition[i][1]);
        this->addChild(m_ptable[i],10);
        
        if(i < 9)
            rotation = 180;
        else if(i < 14)
            rotation = 270;
        else if(i < 23)
            rotation = 0;
        else
            rotation = 90;
        
        
        m_prole[i]->setRotation(rotation);
        m_ptable[i]->setRotation(rotation);
        
        m_bSCaling[i] = false;
        
    }
}

void RoleLayer::pauseRole()
{
    char buff[128];
    for(int i = 0;i < MAXROLE;i++)
    {
        m_prole[i]->pause();
        sprintf(buff, "%s%d.png",rolename[i],0);
        m_prole[i]->setSpriteFrame(cache->getSpriteFrameByName(buff));
    }
}
void RoleLayer::resumeRole(int roleid)
{
    if(roleid == -1)
    {
        for(int i = 0;i < MAXROLE;i++)
        {
            m_prole[i]->resume();
        }
    }
    else
        m_prole[roleid]->resume();
}

void RoleLayer::setCover(bool e)
{
    m_pCover->setVisible(e);
    if(e)
    {
        m_prole[GameData::getInstance()->getprizeid()]->setLocalZOrder(25);
        m_ptable[GameData::getInstance()->getprizeid()]->setLocalZOrder(24);
    }
    else
    {
        m_prole[GameData::getInstance()->getprizeid()]->setLocalZOrder(11);
        m_ptable[GameData::getInstance()->getprizeid()]->setLocalZOrder(10);
    }
}

void RoleLayer::rescale(int roleid)
{
    //m_prole[roleid]->runAction(ScaleTo::create(0.5, 1.0));
    //m_ptable[roleid]->runAction(ScaleTo::create(0.5, 1.0));
}

void RoleLayer::update(float dt)
{
//    float px = sinf(GameScene::getInstance()->getShotlight()->getRotation()*M_PI/180);
    
    
    for(int i = 0;i < MAXROLE;i++)
    {
        if(m_bSCaling[i])
        {
            float curscale = m_prole[i]->getScale();
            curscale -= 0.01;
            m_prole[i]->setScale(curscale);
            m_ptable[i]->setScale(curscale);
            
            if(curscale <= 1.0f)
            {
                m_bSCaling[i] = false;
            }
        }
    }

    if(!isruning)
        return;
    
    float deta[MAXROLE] = {0.2,0.2,0.15,0.1,0.1,0.08,0.05,0.1,0.15,0.15,1.04,0,0.2,0.15,0.2,0.2,0.1,0.1,0.35,0.05,0.1,0.15,0.2,0.2,0.3,0.3,0.2,0.2};
    
    for(int i = 0;i < MAXROLE;i++)
    {
        if(!m_bSCaling[i] && GameInfo::getInstance()->isPointInLine(Vec2(640,360), 1200, GameScene::getInstance()->getShotlight()->getRotation(), m_ptable[i]->getPosition(),deta[i]))
        {
//            if(i==10)
//            {
//                CCLOG("rota10========%f",GameScene::getInstance()->getShotlight()->getRotation());
//            }
            m_prole[i]->setScale(1.2);
            m_ptable[i]->setScale(1.2);
            m_bSCaling[i] = true;
            m_prunroleID = i;
            break;
        }
    }
    
    
}






