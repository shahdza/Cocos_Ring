#ifndef __MiwuSprite_H__
#define __MiwuSprite_H__

#include "Public.h"


class MiwuSprite : public cocos2d::Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(MiwuSprite);
    
    virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
    virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

    void setMiwu(int index);
    void loadData(int index);
    void showUI();
    void addPendant();
    
private:
    int _id;
    int _level;
    int _type;
    Vec2 _pos;
};

#endif // __MiwuSprite_H__
