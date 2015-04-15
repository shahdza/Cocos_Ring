#ifndef __BulletSprite_H__
#define __BulletSprite_H__

#include "Public.h"
#include "BaseSprite.h"

class BulletSprite : public cocos2d::Sprite
{
public:
    virtual bool init(Vec2 src, Vec2 des, int damage, BaseSprite* target, string img);
    static BulletSprite* create(Vec2 src, Vec2 des, int damage, BaseSprite* target, string img);

public:
    void showUI();
    void atk();
public:
    Vec2 _src;
    Vec2 _des;
    int _damage;
    BaseSprite* _target;
    string _img;
};

#endif // __BulletSprite_H__
