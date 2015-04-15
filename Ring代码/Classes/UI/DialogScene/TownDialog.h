#ifndef __TownDialog_H__
#define __TownDialog_H__

#include "Public.h"


class TownDialog : public cocos2d::Layer
{
public:
    static TownDialog* create(TownSprite* town);
    virtual bool init(TownSprite* town);
    
    void addTouch();
    virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
    
    void showDialog();
    void hideDialog();
    void removeDialog();
    
    void btnCallback(Ref* sender, Widget::TouchEventType type);

private:
    int _type;
    
    TownSprite* _town;
};

#endif // __TownDialog_H__
