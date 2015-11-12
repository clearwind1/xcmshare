//
//  LogoLayer.h
//  xcm
//  开机画面
//  Created by Yang on 15/8/13.
//
//

#ifndef __xcm__LogoLayer__
#define __xcm__LogoLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "SystemHeader.h"

USING_NS_CC;

const int TotalResfile = 11;         //加载资源总数

class LogoLayer : public Layer
{
private:
	bool m_bIsChangeScene;					// Steve - 是否收到換場景命令事件
	bool m_bIsLoadingComplete;				// Steve - 資源加載是否完成
    int m_iNumberOfLoaded;
    
    std::string reloadPvrPlists[TotalResfile];
	

public:
    
    ~LogoLayer();
    
    static Scene* createScene();
    
    CREATE_FUNC(LogoLayer);
    virtual bool init(void);
    
    virtual void update(float dt);			// Steve
    
    void initEventListen();
    
    void showlogo(EventCustom* event);
    void showlable(void);
    
    void initreloadname();
    void loadingtexture();
    
    void updatalable(EventCustom* event);
    
    void changescene(EventCustom* event);
    
    void isChangeScene();
    
    void testevent(float dt);
    
private:
    void dispatchLoadingCompleteCommand();	// Steve - 發佈資源加載完畢命令事件
    void loadingTextureCallback(Texture2D* texture);
    void loadingAudio();
    
    VersionInfo m_pversioninfo;
	MachineIDInfo m_pMachineIDInfo;		// Steve 機台ID
    
    SceneInfo m_psceneinfo;
    
};


#endif /* defined(__xcm__LogoLayer__) */
