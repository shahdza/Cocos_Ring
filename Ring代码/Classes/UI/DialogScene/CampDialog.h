#ifndef __CampDialog_H__
#define __CampDialog_H__

#include "Public.h"


class CampDialog : public cocos2d::Layer
{
public:
    static CampDialog* create();
    CampDialog();
    virtual bool init();
    
    void showDialog();
    void hideDialog();
    void removeDialog();
    void showInfo();
    
    void closeCallback(Ref* sender, Widget::TouchEventType type);
    void infoCallback(Ref* sender, Widget::TouchEventType type);
    void buyCallback(Ref* sender, Widget::TouchEventType type);
private:
    
    ValueMap& fighter;
    ValueMap& bowman;
    ValueMap& gunner;
    ValueMap& meat;
    int campLevel;
    int labLevel;
    int limit;
    int gold;
    int wood;
};

#endif // __CampDialog_H__
