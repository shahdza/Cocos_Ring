#ifndef __HomeOptLayer_H__
#define __HomeOptLayer_H__

#include "Public.h"


class HomeOptLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(HomeOptLayer);

public:
    void loadData();
    void showUI();

    void show(BuildingSprite* buildingSprite);  // ID为设施的ID
    void hide(BuildingSprite* buildingSprite);  // ID为设施的ID
    void showAction(Button* btn, float delay);
    void hideAction(Button* btn, float delay);
    
    void infoCallback(Ref* sender, Widget::TouchEventType type);
    void upgradeCallback(Ref* sender, Widget::TouchEventType type);
    void enterCallback(Ref* sender, Widget::TouchEventType type);

public:
    Button* btnInfo;
    Button* btnUpgrade;
    Button* btnEnter;
    Text* label;
    
    BuildingSprite* _buildingSprite;
};

#endif // __HomeOptLayer_H__
