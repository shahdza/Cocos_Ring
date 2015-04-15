#include "HelloScene.h"


Scene* HelloScene::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloScene::create();
    scene->addChild(layer);
    return scene;
}


bool HelloScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->setOpacity(0);
    this->showUI();
    
    return true;
}


void HelloScene::showUI()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();

    auto bg = Sprite::create(IMG_LOADING_BG);
    bg->setPosition(visibleSize/2);
    this->addChild(bg);
    
    auto fadeIn = FadeTo::create(0.1f, 255);
    auto fadeOut = FadeTo::create(0.1f, 0);
    auto func = CallFunc::create(CC_CALLBACK_0(HelloScene::changeScene, this));
    auto action = Sequence::create(fadeIn, fadeOut, func, nullptr);
    
    this->runAction(action);
}


void HelloScene::changeScene()
{
    GM()->enterHomeScene();
}

