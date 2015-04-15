#ifndef __HomeScene_H__
#define __HomeScene_H__

#include "Public.h"


class HomeScene : public Scene
{
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(HomeScene);
    bool init();
    
public:
    HomeMapLayer* _mapLayer;
    HomeHudLayer* _hudLayer;
    HomeOptLayer* _optLayer;
};

#endif //__HomeScene_H__

