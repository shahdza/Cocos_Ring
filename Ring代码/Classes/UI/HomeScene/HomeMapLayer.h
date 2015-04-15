#ifndef __HomeMapLayer_H__
#define __HomeMapLayer_H__

#include "Public.h"

class HomeMapLayer : public PanZoomLayer
{
public:
    virtual bool init();
    CREATE_FUNC(HomeMapLayer);

    void addTouch();
    virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
    virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch, Event* pEvent);
    void moveToCenter(Vec2 pos, float delta);
    
    void setHudLayer(Layer* layer);
    void enterAction();
    
    void loadData();
    void showUI();
    void addMap();
    void addRobot();
    void addObscale();
    void detachAllBuilding();
    void newBuild(int type, int gold, Vec2 tiledPos);
    
public:
    CCSize _mapSize;
    Vector<BuildingSprite*> _building;

    Layer* _hudLayer;
};

#endif // __HomeMapLayer_H__
