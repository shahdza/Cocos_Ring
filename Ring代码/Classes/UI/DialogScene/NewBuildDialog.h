#ifndef __NewBuildDialog_H__
#define __NewBuildDialog_H__

#include "Public.h"


class NewBuildDialog : public cocos2d::Layer
{
public:
    static NewBuildDialog* create();
    virtual bool init();
    
    void showDialog();
    void hideDialog();
    void removeDialog();
    void showInfo();
    
    void showNotice(string text);
    void closeCallback(Ref* sender, Widget::TouchEventType type);
    void buildCallback(Ref* sender, Widget::TouchEventType type);
    
private:
    Text* gold;
    Text* wood;
    int mineCount;
    int woodCount;
    int arrowCount;
    int cannonCount;
    int laserCount;
    int mineLimit;
    int woodLimit;
    int arrowLimit;
    int cannonLimit;
    int laserLimit;
    
    float _delta;
};

#endif // __NewBuildDialog_H__
