#ifndef __WorldScene_H__
#define __WorldScene_H__

#include "Public.h"


class WorldScene : public Scene
{
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(WorldScene);
    bool init();
    
private:
    WorldMapLayer* _mapLayer;
    WorldHudLayer* _hudLayer;
};

#endif //__WorldScene_H__

