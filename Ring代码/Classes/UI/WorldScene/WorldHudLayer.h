#ifndef __WorldHudLayer_H__
#define __WorldHudLayer_H__

#include "Public.h"


class WorldHudLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(WorldHudLayer);
    WorldHudLayer();
    virtual ~WorldHudLayer();

public:
    void loadData();
    void showUI();
    
    void addGold(int add);
    void addWood(int add);
    
    void setMapLayer(Layer* layer);

    void btnCallback(Ref* sender, Widget::TouchEventType type);

private:
    string _name;
    int _level;
    int _exp;
    int _expRequire;
    int _ringCount;
    int _goldCount;
    int _woodCount;
    int _goldCapacity;
    int _woodCapacity;
    
    Layer* _mapLayer;
};

#endif // __WorldHudLayer_H__
