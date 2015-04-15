#ifndef __BattleScene_H__
#define __BattleScene_H__

#include "Public.h"


class BattleScene : public Scene
{
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(BattleScene);
    bool init();
    
public:
    BattleMapLayer* _mapLayer;
    BattleHudLayer* _hudLayer;
};

#endif //__BattleScene_H__

