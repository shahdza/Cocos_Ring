#ifndef __BattleHudLayer_H__
#define __BattleHudLayer_H__

#include "Public.h"


class BattleHudLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(BattleHudLayer);

public:
    void loadData();
    void showUI();
    void showInfo();
    
    
    bool updateCount();
    void setMapLayer(Layer* layer);
    
    
    void selectCallback(Ref* sender, Widget::TouchEventType type);
    void skillCallback(Ref* sender, Widget::TouchEventType type);
    void retreatCallback(Ref* sender, Widget::TouchEventType type);
    
public:
    string _name;
    int _level;
    int _goldReward;
    int _woodReward;
    int _ringReward;
    int _count[5];
    int _select;
    
    int skill1;
    int skill2;
    
    BattleMapLayer* _mapLayer;
};

#endif // __BattleHudLayer_H__
