#ifndef __BattleMapLayer_H__
#define __BattleMapLayer_H__

#include "Public.h"

class BattleMapLayer : public PanZoomLayer
{
public:
    virtual bool init();
    CREATE_FUNC(BattleMapLayer);

    void addTouch();
    virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
    virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch, Event* pEvent);
    void moveToCenter(Vec2 pos, float delta);
    
    void setHudLayer(Layer* layer);
    void enterAction();
    
    void loadData();
    void addAI();
    void showUI();
    void addMap();
    void addHero(Vec2 pos);
    void addSoilder(Vec2 pos);
    
public:
    CCSize _mapSize;
    
    float _delta;

    BattleHudLayer* _hudLayer;
    AIManager* _ai;
};

#endif // __BattleMapLayer_H__
