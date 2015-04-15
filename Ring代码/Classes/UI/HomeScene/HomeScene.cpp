#include "HomeScene.h"


Scene* HomeScene::createScene()
{
    auto scene = HomeScene::create();
    return scene;
}

bool HomeScene::init()
{
    if (! Scene::init())
    {
        return false;
    }
    
    _hudLayer = HomeHudLayer::create();
    _optLayer = HomeOptLayer::create();
    _mapLayer = HomeMapLayer::create();
    this->addChild(_hudLayer, 9);
    this->addChild(_optLayer, 9);
    this->addChild(_mapLayer);
    
    _mapLayer->setHudLayer(_hudLayer);
    _hudLayer->setMapLayer(_mapLayer);
    
    // 没有新建建筑
    GM()->_newBuild = false;
    GM()->_build = nullptr;
    
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    SimpleAudioEngine::getInstance()->playBackgroundMusic(OGG_BACKGROUND, true);
    

    return true;
}


