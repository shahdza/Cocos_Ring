#ifndef __HeroHotelDialog_H__
#define __HeroHotelDialog_H__

#include "Public.h"


class HeroHotelDialog : public cocos2d::Layer
{
public:
    static HeroHotelDialog* create();
    virtual bool init();
    
    void showDialog();
    void hideDialog();
    void removeDialog();
    void showInfo();
    
    void closeCallback(Ref* sender, Widget::TouchEventType type);
    void infoCallback(Ref* sender, Widget::TouchEventType type);
    void battleCallback(Ref* sender, Widget::TouchEventType type);
private:
    
    
};

#endif // __HeroHotelDialog_H__
