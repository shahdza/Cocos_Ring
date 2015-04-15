#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "Public.h"


class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual void initGLContextAttrs();

    virtual bool applicationDidFinishLaunching();
    virtual void applicationDidEnterBackground();
    virtual void applicationWillEnterForeground();
    
    void loadResources();
};

#endif // _APP_DELEGATE_H_

