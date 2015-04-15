#ifndef __TownSprite_H__
#define __TownSprite_H__

#include "Public.h"

class TownDialog;

class TownSprite : public cocos2d::Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(TownSprite);
    
    virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
    virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch, Event* pEvent);
    void moveToCenter();
    
    void setTown(int index);
    void loadData(int index);
    void showUI();
    void addPendant();
    
    void showDialog();
    
    void harvest();
    void update(float dt);

public:
    int _id;
    string _name;
    int _level;
    int _type;
    Vec2 _pos;
    string _description;
    
    int _goldReward;
    int _woodReward;
    int _ringReward;
    
    int _goldProduct;
    int _woodProduct;
    int _lastHarvest;
    
    string _img;
    float _delta;
    
    HarvestBubble* bubble;
};

#endif // __TownSprite_H__
