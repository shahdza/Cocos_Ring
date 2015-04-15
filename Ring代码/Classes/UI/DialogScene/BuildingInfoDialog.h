#ifndef __BuildingInfoDialog_H__
#define __BuildingInfoDialog_H__

#include "Public.h"


class BuildingInfoDialog : public cocos2d::Layer
{
public:
    static BuildingInfoDialog* create(BuildingSprite* buildingSprite);
    virtual bool init(BuildingSprite* buildingSprite);
    
    void showDialog();
    void hideDialog();
    void removeDialog();
    void showInfo();
    void btnCallback(Ref* sender, Widget::TouchEventType type);

private:
    int _type;
    
    BuildingSprite* _buildingSprite;
};

#endif // __BuildingInfoDialog_H__
