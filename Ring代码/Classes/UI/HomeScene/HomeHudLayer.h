#ifndef __HomeHudLayer_H__
#define __HomeHudLayer_H__

#include "Public.h"


class HomeHudLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(HomeHudLayer);
    HomeHudLayer();
    virtual ~HomeHudLayer();

public:
    void loadData();
    void showUI();
    
    void addPlayerExp(int add);
    void addGold(int add);
    void addWood(int add);
    void setGoldCapacity(int capacity);
    void setWoodCapacity(int capacity);
    
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

#endif // __HomeHudLayer_H__
