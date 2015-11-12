//
//  GameInfo.cpp
//  xcm
//
//  Created by Yang on 15/8/5.
//
//

#include "GameInfo.h"

static GameInfo* s_SharedGameInfo = nullptr;

GameInfo::GameInfo()
{
    s_SharedGameInfo = this;
}
GameInfo::~GameInfo()
{
    
}

GameInfo* GameInfo::getInstance()
{
    if(!s_SharedGameInfo)
    {
        s_SharedGameInfo = new (std::nothrow)GameInfo();
    }
    
    return s_SharedGameInfo;
}

Action* GameInfo::createAnitmation(const char *pathname, int total, int loopcount, float delay,bool reverse)
{
    //__Array* actionarray = __Array::create();
    
    Vector<SpriteFrame*> frames;
    char buff[128];
    for(int i = 0;i < total;i++)
    {
        int nameid = i;
        if(reverse){
            nameid = total-i-1;
        }
        sprintf(buff, "%s%d.png",pathname,nameid);
        if(cache->getSpriteFrameByName(buff))
        {
            frames.pushBack(cache->getSpriteFrameByName(buff));
        }
        else
        {
            Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(buff);
            SpriteFrame* spriteframe = SpriteFrame::createWithTexture(texture, Rect(0, 0, texture->getContentSize().width, texture->getContentSize().height));
            frames.pushBack(spriteframe);
        }
        
    }

    Animation* action = Animation::createWithSpriteFrames(frames,delay);
    Animate* animate = CCAnimate::create(action);
    
    if(loopcount == -1)
    {
        RepeatForever* repeat = RepeatForever::create(animate);
        return repeat;
    }
    else
    {
        Repeat* repeat = CCRepeat::create(animate, loopcount);
        return repeat;
    }

}

void GameInfo::spriteSetPosition(Node *node,cocos2d::Node *sprite,float x,float y)
{
    //坐标系的转换
    if(node == NULL)
        sprite->setPosition(x,m_GameDesignSize.height-y);
    else
        sprite->setPosition(x,node->getContentSize().height-y);
}

void GameInfo::createSpriteNum(cocos2d::Node *node,const char* numName, int num)
{
    //float start,width = 0;
    //Sprite *sprite;
    Size size;
    
    char buff[64];
    sprintf(buff, "%d",num);
    
    const char* str = buff;
    
    node->removeAllChildren();
    
    size.width = 0;
    size.height = 0;
    
    char numbuff[64];
    
    for(int i = 0;i < strlen(str);i++)
    {
        int curnum = str[i] - '0';

        sprintf(numbuff, "%s%d.png",numName,curnum);
        auto sprite = Sprite::createWithSpriteFrameName(numbuff);
        sprite->setPosition(size.width + sprite->getContentSize().width / 2,0 + sprite->getContentSize().height / 2);
        node->addChild(sprite);
        size.width += sprite->getContentSize().width;
        size.height = sprite->getContentSize().height;
    }
    
    node->setContentSize(Size(size.width,size.height));
    
}

bool GameInfo::isPointInLine(Point soildP, float linelen, float angle, Point judeP,float deta)
{
    //P1(x1,y1)、P2(x2,y2)、Q(x3,y3)
    Point P1 = soildP;
    Point P2;
    P2.x = P1.x + linelen*sinf((90+angle)*M_PI/180);
    P2.y = P1.y + linelen*cosf((90+angle)*M_PI/180);
    Point Q = judeP;
    
   // CCLOG("p2x======%f",P2.x);
   // CCLOG("p2y======%f",P2.y);
    
    float xa = P2.x - P1.x;
    float ya = P2.y - P1.y;
    float xb = Q.x - P1.x;
    float yb = Q.y - P1.y;
    
    
    float delta = deta;
    
  //  如果要判断 Q 是否落在线段 P1P2 上，则
  //  float distance = xa * yb - xb * ya;
    
    float yc = Q.y - P2.y;
    if(yc >= -2 && yc <= 2 && MIN(P1.x,P2.x)<=Q.x && Q.x<=MAX(P1.x,P2.x))
    {
        return true;
    }
    
    float distance = xa/ya - xb/yb;
    
    
    if(distance >= -delta &&  distance <= delta &&
       MIN(P1.x,P2.x)<=Q.x && Q.x<=MAX(P1.x,P2.x) &&
       MIN(P1.y,P2.y)<=Q.y && Q.y<=MAX(P1.y,P2.y) ) {
        // Q 落在线段 P1P2 上
        
//        CCLOG("xa * yb====%f",xa/ya);
//        
//        CCLOG("xb * ya====%f",xb/yb);
//        
//        CCLOG("distance====%f",distance);
        
        return true;
    }
    
    return false;
}

Sprite* GameInfo::createRect(Rect rect,float x,float y)
{
    Sprite *m_prect = Sprite::create();
    m_prect->setTextureRect(rect);
    m_prect->setAnchorPoint(Vec2(0, 0));
    GameInfo::getInstance()->spriteSetPosition(NULL, m_prect, x, y);
    
    
    return m_prect;
}

void GameInfo::playEffect(int prizeID)
{
 
    //自行改变所对应音效名
    const char* effName[28] = {"bengbeng.mp3","guangtouqiang.mp3","huli.mp3","jiji.mp3","tutu.mp3","xiongda.mp3","xionger.mp3",
                                "bengbeng.mp3","guangtouqiang.mp3","huli.mp3","jiji.mp3","tutu.mp3","xiongda.mp3","xionger.mp3",
                                "bengbeng.mp3","guangtouqiang.mp3","huli.mp3","jiji.mp3","tutu.mp3","xiongda.mp3","xionger.mp3",
                                "bengbeng.mp3","guangtouqiang.mp3","huli.mp3","jiji.mp3","tutu.mp3","xiongda.mp3","xionger.mp3"};
    
    SimpleAudioEngine::getInstance()->playEffect(effName[prizeID]);
}









