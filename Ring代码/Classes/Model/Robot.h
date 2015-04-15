#ifndef __Robot_H__
#define __Robot_H__

#include "Public.h"


class Robot : public cocos2d::Sprite
{
public:
    virtual bool init(int type);
    static Robot* create(int type);

public:
    void showUI();          // 显示UI
    void idle();            // 悠闲

private:
    int _type;
    Vec2 _pos;
    Armature* arm;
};

#endif // __Robot_H__
