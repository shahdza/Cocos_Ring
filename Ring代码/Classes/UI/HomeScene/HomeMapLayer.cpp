#include "HomeMapLayer.h"


bool HomeMapLayer::init()
{
    if ( !PanZoomLayer::init() )
    {
        return false;
    }
    
    this->loadData();
    
    this->showUI();
    this->addMap();
    this->addRobot();
    this->addObscale();
    
    this->addTouch();
    
    this->enterAction();
    
    return true;
}

void HomeMapLayer::loadData()
{
    
}

void HomeMapLayer::showUI()
{
    auto bg = Sprite::create(IMG_HOME_BG);
    bg->setAnchorPoint(Vec2(0, 0));
    bg->setPosition(Vec2(0, 0));
    this->addChild(bg, -1);
    
    _mapSize = bg->getContentSize();
    
    this->setPanBoundsRect(Rect(_mapSize.width * -1.0, _mapSize.height * -1.0,
                                _mapSize.width * 1.0, _mapSize.height * 1.0));
    this->setMinScale(0.5f);
    this->setMaxScale(1.5f);
    this->setZoomDelta(0.0f, 0.1f);
    this->setScale(0.5f);
}


void HomeMapLayer::addMap()
{
    // 清空占地情况
    GM()->clearCovered();

    ValueVector building = DM()->_building;
    for (int i = 1; i < building.size(); i++) {
        BuildingSprite* t = BuildingSprite::create(i);
        this->addChild(t);
    }
}


void HomeMapLayer::addRobot()
{
    for(int i = 1; i <= 4; i++) {
        auto r = Robot::create(i);
        this->addChild(r);
    }
}


void HomeMapLayer::addObscale()
{
    auto tree1 = Sprite::create(IMG_TREE);
    auto tree2 = Sprite::create(IMG_TREE);
    auto tree3 = Sprite::create(IMG_TREE);
    auto tree4 = Sprite::create(IMG_TREE);
    
    tree1->setPosition(GM()->getMapPos(Vec2(5, 5)));
    tree2->setPosition(GM()->getMapPos(Vec2(33, 33)));
    tree3->setPosition(GM()->getMapPos(Vec2(5, 33)));
    tree4->setPosition(GM()->getMapPos(Vec2(33, 5)));
    
    tree1->setLocalZOrder(10);
    tree2->setLocalZOrder(66);
    tree3->setLocalZOrder(38);
    tree4->setLocalZOrder(38);
    
    GM()->setCoverd(Vec2(5, 5), 1);
    GM()->setCoverd(Vec2(33, 33), 1);
    GM()->setCoverd(Vec2(5, 33), 1);
    GM()->setCoverd(Vec2(33, 5), 1);
    
    this->addChild(tree1);
    this->addChild(tree2);
    this->addChild(tree3);
    this->addChild(tree4);
    
    
}


void HomeMapLayer::detachAllBuilding()
{
    auto childen = this->getChildren();
    for (int i = 0; i < childen.size(); i++) {
        if(childen.at(i)->getName() == "BuildingSprite") {
            auto build = (BuildingSprite*)childen.at(i);
            build->detach();
        }
    }
}


// 建造新设施
void HomeMapLayer::newBuild(int type, int gold, Vec2 tiledPos)
{
    auto hudLayer = (HomeHudLayer*)this->_hudLayer;
    hudLayer->addGold(-gold);
    
    // 更新数据库
    int index = DM()->addNewBuilding(type, tiledPos);
    BuildingSprite* t = BuildingSprite::create(index);
    this->addChild(t);
}



void HomeMapLayer::setHudLayer(Layer* layer)
{
    _hudLayer = layer;
}


// 触摸事件
void HomeMapLayer::addTouch()
{
    auto dispatcher = this->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HomeMapLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HomeMapLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HomeMapLayer::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool HomeMapLayer::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    
    return true;
}

void HomeMapLayer::onTouchMoved(Touch* pTouch, Event* pEvent)
{
    
    
}

void HomeMapLayer::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    
    
}


// 将城池移动到屏幕中心, 稍微靠下的位置
void HomeMapLayer::moveToCenter(Vec2 pos, float delta)
{
    Size WIN_SIZE = Director::getInstance()->getWinSize();
    
    float scale = this->getScale();
    pos = Vec2(pos.x/scale, pos.y/scale);
    Vec2 worldPos = this->convertToWorldSpace(pos);
    
    Vec2 diff = Vec2(WIN_SIZE.width/2 - worldPos.x, (WIN_SIZE.height/3) - worldPos.y);
    
    auto scaleTo = ScaleTo::create(delta, 1.0);
    auto moveBy = MoveBy::create(delta, diff);
    this->runAction(scaleTo);
    this->runAction(moveBy);
}

// 进入时动画
void HomeMapLayer::enterAction()
{
    Size WIN_SIZE = Director::getInstance()->getWinSize();
    
    Vec2 pos = Vec2((WIN_SIZE.width - _mapSize.width)/2, (WIN_SIZE.height - _mapSize.height)/2);
    this->setPosition(pos);
    
    moveToCenter(Vec2(_mapSize.width/2, _mapSize.height/2), 0.5);
}

