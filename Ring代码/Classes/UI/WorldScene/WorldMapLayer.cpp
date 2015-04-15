#include "WorldMapLayer.h"


WorldMapLayer::WorldMapLayer()
{
}

WorldMapLayer::~WorldMapLayer()
{
    auto dispatcher = this->getEventDispatcher();
    dispatcher->removeEventListenersForTarget(this);
}

bool WorldMapLayer::init()
{
    if ( !PanZoomLayer::init() )
    {
        return false;
    }
    
    this->loadData();
    this->showUI();
    this->addTown();
    this->addMiwu();
    this->addTouch();
    
    this->enterAction();
    
    return true;
}

void WorldMapLayer::loadData()
{
    
}

void WorldMapLayer::showUI()
{
    auto bg = Sprite::create(IMG_WORLD_BG);
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


void WorldMapLayer::addTown()
{
    ValueVector town = DM()->_town;
    for (int i = 1; i < town.size(); i++) {
        TownSprite* t = TownSprite::create();
        t->setTown(i);
        this->addChild(t);
        _town.pushBack(t);
    }
}


void WorldMapLayer::addMiwu()
{
    ValueVector miwu = DM()->_miwu;
    for (int i = 1; i < miwu.size(); i++) {
        ValueMap vm = miwu.at(i).asValueMap();
        if (vm["Type"].asInt() == MIWU_TYPE_LOCK) {
            MiwuSprite* t = MiwuSprite::create();
            t->setMiwu(i);
            this->addChild(t, 1);
            _miwu.pushBack(t);
        }
    }
}


void WorldMapLayer::setHudLayer(Layer* layer)
{
    _hudLayer = layer;
}


void WorldMapLayer::addTouch()
{
    auto dispatcher = this->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(WorldMapLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(WorldMapLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(WorldMapLayer::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool WorldMapLayer::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    _touchTown = nullptr;
    _touchMiwu = nullptr;
    for (int i = 0; i < _miwu.size(); i++) {
        MiwuSprite* miwu = (MiwuSprite*)_miwu.at(i);
        if (miwu->onTouchBegan(pTouch, pEvent)) {
            _touchMiwu = miwu;
            return true;
        }
    }
    for (int i = 0; i < _town.size(); i++) {
        TownSprite* town = (TownSprite*)_town.at(i);
        if (town->onTouchBegan(pTouch, pEvent)) {
            _touchTown = town;
            return true;
        }
    }
    return false;
}

void WorldMapLayer::onTouchMoved(Touch* pTouch, Event* pEvent)
{
    if (_touchTown != nullptr) _touchTown->onTouchMoved(pTouch, pEvent);
}

void WorldMapLayer::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    if(_touchTown != nullptr) _touchTown->onTouchEnded(pTouch, pEvent);
    _touchTown = nullptr;
    _touchMiwu = nullptr;
}


// 将城池移动到屏幕中心, 稍微靠下的位置
void WorldMapLayer::moveToCenter(Vec2 pos, float delta)
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
void WorldMapLayer::enterAction()
{
    Size WIN_SIZE = Director::getInstance()->getWinSize();
    
    Vec2 pos = Vec2((WIN_SIZE.width - _mapSize.width)/2, (WIN_SIZE.height - _mapSize.height)/2);
    this->setPosition(pos);
    
    moveToCenter(Vec2(_mapSize.width/2, _mapSize.height/2), 0.5);
}

