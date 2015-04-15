#ifndef __HelloScene_H__
#define __HelloScene_H__

#include "Public.h"

class HelloScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HelloScene);
    
    void showUI();
    void changeScene();
};

#endif // __HelloScene_H__
