#ifndef __LabDialog_H__
#define __LabDialog_H__

#include "Public.h"


class LabDialog : public cocos2d::Layer
{
public:
    static LabDialog* create();
    LabDialog();
    virtual bool init();
    
    void showDialog();
    void hideDialog();
    void removeDialog();
    void showInfo();
    
    void closeCallback(Ref* sender, Widget::TouchEventType type);
    void infoCallback(Ref* sender, Widget::TouchEventType type);
    void upCallback(Ref* sender, Widget::TouchEventType type);
private:
    
    ValueMap& fighter;
    ValueMap& bowman;
    ValueMap& gunner;
    ValueMap& meat;
    int labLevel;
    int gold;
    int wood;
};

#endif // __LabDialog_H__
