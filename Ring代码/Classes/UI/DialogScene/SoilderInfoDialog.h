#ifndef __SoilderInfoDialog_H__
#define __SoilderInfoDialog_H__

#include "Public.h"


class SoilderInfoDialog : public cocos2d::Layer
{
public:
    static SoilderInfoDialog* create(int ID);
    virtual bool init(int ID);
    
    void showDialog();
    void hideDialog();
    void removeDialog();
    void showInfo();
    void btnCallback(Ref* sender, Widget::TouchEventType type);

    void update(float dt);
private:
    int _id;
    Armature* arm;
};

#endif // __SoilderInfoDialog_H__
