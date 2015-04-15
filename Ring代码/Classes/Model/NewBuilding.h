#ifndef __NewBuilding_H__
#define __NewBuilding_H__

#include "Public.h"


class NewBuilding : public cocos2d::Sprite
{
public:
    virtual bool init(int type, int gold);
    static NewBuilding* create(int type, int gold);
    
    void addTouch();
    virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
    virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

    
    void okCallback(Ref* sender, Widget::TouchEventType type);
    void cancleCallback(Ref* sender, Widget::TouchEventType type);
    
public:
    void showUI();                  // 显示UI
    void moveBuilding(Vec2 delta);  // 移动建筑

public:
    // 基础属性
    int _type;
    int _gold;
    Vec2 _pos;
    
    // 触摸属性
    bool _isTouched;            // 是否被触摸
    float _deltaPos;            // 移动偏移
    EventListenerTouchOneByOne* listener;
    
    // 图片
    CCSize _size;       // 尺寸
    Sprite* _normal;    // 正常图片
    Sprite* _tip;       // 箭头
    Button* _cancle;
    Button* _ok;
};

#endif // __NewBuilding_H__
