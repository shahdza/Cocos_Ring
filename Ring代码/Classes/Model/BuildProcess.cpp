#include "BuildProcess.h"


BuildProcess* BuildProcess::create(BuildingSprite* buildingSprite)
{
    BuildProcess *pRet = new(std::nothrow) BuildProcess();
    if (pRet && pRet->init(buildingSprite)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool BuildProcess::init(BuildingSprite* buildingSprite)
{
    if ( !Sprite::init() )
    {
        return false;
    }
    
    _delta = 0.0;
    _buildingSprite = buildingSprite;
    
    showUI();
    
    scheduleUpdate();
    
    return true;
}


void BuildProcess::showUI()
{
    this->setTexture(IMG_BUILD_PRO_BK);
    
    // loadingBar
    _loadingBar = LoadingBar::create(IMG_BUILD_PRO);
    _loadingBar->setPosition(this->getContentSize()/2);
    this->addChild(_loadingBar, 1, "LoadingBar");
    
    // _timeRest
    _timeRest = Text::create("", FONT_ARIAL, 16);
    _timeRest->setPosition(this->getContentSize()/2);
    this->addChild(_timeRest, 1, "TimeRest");
}


void BuildProcess::remove()
{
    this->removeFromParent();
}


void BuildProcess::update(float dt)
{
    int timeStamp = GM()->getTimeStamp();
    auto delta = timeStamp - _buildingSprite->_lastBuildTime;
    auto timeRequire = _buildingSprite->_timeRequire;
    int rest = timeRequire - delta;
    
    _loadingBar->setPercent(100.0f * delta/timeRequire);
    _timeRest->setString(GM()->getIntToStr(rest) + "s");
    
    if (rest <= 0) {
        this->unscheduleUpdate();
        
        auto delay = DelayTime::create(1.0f);
        auto func = CallFunc::create(CC_CALLBACK_0(BuildProcess::finish, this));
        this->runAction(Sequence::create(delay, func, nullptr));
    }
}


void BuildProcess::finish()
{
    _buildingSprite->upgradeFinished();
    remove();
}

