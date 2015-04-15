#ifndef __BuildProcess_H__
#define __BuildProcess_H__

#include "Public.h"


class BuildProcess : public cocos2d::Sprite
{
public:
    static BuildProcess* create(BuildingSprite* buildingSprite);
    virtual bool init(BuildingSprite* buildingSprite);
    
    void showUI();
    void remove();
    void update(float dt);
    void finish();
    
private:
    float _delta;
    LoadingBar* _loadingBar;
    Text* _timeRest;
    
    BuildingSprite* _buildingSprite;
};

#endif // __BuildProcess_H__
