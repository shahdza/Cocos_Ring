#ifndef __HarvestBubble_H__
#define __HarvestBubble_H__

#include "Public.h"


class HarvestBubble : public cocos2d::Sprite
{
public:
    static HarvestBubble* create(int type);
    virtual bool init(int type);
    
    void addTouch();
    virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
    virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch, Event* pEvent);
    
    void showUI();
    void beganAction();
    void endAction();
    void harvest();
    void remove();
    
    std::function<void()> _callback;
    EventListenerTouchOneByOne* listener;
private:
    int _type;
    float _delta;
    bool isHarvest;
    
    Sprite* _bubble;
    Sprite* _image;
};

#endif // __HarvestBubble_H__
