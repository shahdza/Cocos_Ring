#ifndef __WorldMapLayer_H__
#define __WorldMapLayer_H__

#include "Public.h"

class WorldMapLayer : public PanZoomLayer
{
public:
    virtual bool init();
    CREATE_FUNC(WorldMapLayer);
    WorldMapLayer();
    virtual ~WorldMapLayer();

    void addTouch();
    virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
    virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch, Event* pEvent);
    void moveToCenter(Vec2 pos, float delta);
    
    void setHudLayer(Layer* layer);
    void enterAction();
    
    void loadData();
    void showUI();
    void addTown();
    void addMiwu();
    
public:
    CCSize _mapSize;
    Vector<TownSprite*> _town;
    Vector<MiwuSprite*> _miwu;
    TownSprite* _touchTown;
    MiwuSprite* _touchMiwu;
    
    Layer* _hudLayer;
};

#endif // __WorldMapLayer_H__
