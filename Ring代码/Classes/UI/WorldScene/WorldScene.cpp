#include "WorldScene.h"


Scene* WorldScene::createScene()
{
    auto scene = WorldScene::create();
    return scene;
}

bool WorldScene::init()
{
    if (! Scene::init())
    {
        return false;
    }
    
    _mapLayer = WorldMapLayer::create();
    _hudLayer = WorldHudLayer::create();
    this->addChild(_mapLayer, -1);
    this->addChild(_hudLayer, 9);
    
    _mapLayer->setHudLayer(_hudLayer);
    _hudLayer->setMapLayer(_mapLayer);
    
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    SimpleAudioEngine::getInstance()->playBackgroundMusic(OGG_BATTLEGROUND, true);
    
    return true;
}


