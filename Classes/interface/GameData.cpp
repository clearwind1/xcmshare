//
//  GameData.cpp
//  xcm
//
//  Created by Yang on 15/8/20.
//
//

#include "GameData.h"

static GameData* g_sSharedGameData = nullptr;

GameData* GameData::getInstance()
{
    if(!g_sSharedGameData)
    {
        g_sSharedGameData = new (std::nothrow)GameData();
    }
    
    return g_sSharedGameData;
}

GameData::GameData()
{
    g_sSharedGameData = this;
    
}
GameData::~GameData()
{
    
}

