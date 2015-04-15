#ifndef __BaseSprite_H__
#define __BaseSprite_H__

#include "cocos2d.h"
USING_NS_CC;

class BaseSprite : public cocos2d::Sprite
{
public:
    virtual bool init();
    CREATE_FUNC(BaseSprite);
    BaseSprite() {}
    virtual ~BaseSprite() {}

public:
    virtual void atk();
    virtual void run();
    virtual void hurt(int x);
    virtual void idle();
    virtual bool isDeath();

public:
    Vec2 _pos;
};


#endif // __BaseSprite_H__
