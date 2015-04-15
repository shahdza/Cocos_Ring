#ifndef __HeroInfoDialog_H__
#define __HeroInfoDialog_H__

#include "Public.h"


class HeroInfoDialog : public cocos2d::Layer
{
public:
    static HeroInfoDialog* create(int ID);
    virtual bool init(int ID);
    
    void showDialog();
    void hideDialog();
    void removeDialog();
    void showInfo();
    void closeCallback(Ref* sender, Widget::TouchEventType type);

    void baseCallback(Ref* sender, Widget::TouchEventType type);
    void skillCallback(Ref* sender, Widget::TouchEventType type);
    
    void update(float dt);
private:
    int _id;
    Armature* arm;
    
    ImageView* baseBoard;
    ImageView* skillBoard;
};

#endif // __HeroInfoDialog_H__
