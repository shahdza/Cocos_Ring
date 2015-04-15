#ifndef __BuildingUpgradeDialog_H__
#define __BuildingUpgradeDialog_H__

#include "Public.h"


class BuildingUpgradeDialog : public cocos2d::Layer
{
public:
    static BuildingUpgradeDialog* create(BuildingSprite* buildingSprite);
    virtual bool init(BuildingSprite* buildingSprite);
    
    void showDialog();
    void hideDialog();
    void removeDialog();
    void showNowInfo();     // 显示当前等级信息
    void showNextInfo();    // 显示下一等级增量信息
    void showRequire();     // 显示资源需求信息
    void btnCallback(Ref* sender, Widget::TouchEventType type);
    void upgradeCallback(Ref* sender, Widget::TouchEventType type);
private:
    int _type;
    int _goldRequire;
    int _woodRequire;
    int _timeRequire;
    
    BuildingSprite* _buildingSprite;
};

#endif // __BuildingUpgradeDialog_H__
