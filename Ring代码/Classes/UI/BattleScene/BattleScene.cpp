#include "BattleScene.h"


Scene* BattleScene::createScene()
{
    auto scene = BattleScene::create();
    return scene;
}

bool BattleScene::init()
{
    if (! Scene::init())
    {
        return false;
    }
    
    _mapLayer = BattleMapLayer::create();
    _hudLayer = BattleHudLayer::create();
    this->addChild(_mapLayer);
    this->addChild(_hudLayer, 9);
    
    _hudLayer->setMapLayer(_mapLayer);
    _mapLayer->setHudLayer(_hudLayer);

    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    SimpleAudioEngine::getInstance()->playBackgroundMusic(OGG_BATTLEGROUND, true);
    
    return true;
}


