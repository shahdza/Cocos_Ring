#include "NewBuilding.h"


NewBuilding* NewBuilding::create(int type, int gold)
{
    NewBuilding *pRet = new(std::nothrow) NewBuilding();
    if (pRet && pRet->init(type, gold)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool NewBuilding::init(int type, int gold)
{
    if ( !Sprite::init() ) {
        return false;
    }
    
    _isTouched = false;
    _type = type;
    _gold = gold;
    _pos = GM()->getSpaceTiled();
    
    showUI();
    addTouch();
    
    return true;
}


void NewBuilding::showUI()
{
    this->setTexture(IMG_BUILDING_Floor);
    _size = this->getContentSize();
    this->setColor(Color3B::GREEN);
    this->setLocalZOrder(TILED_TOTAL_X + TILED_TOTAL_Y + 1);
    
    string nomal_IMG = GM()->getBuildingIMG(_type);
    _normal = Sprite::create(nomal_IMG);
    _tip = Sprite::create(IMG_BUILDING_ArrowTip);

    this->setPosition(GM()->getMapPos(_pos));
    _normal->setAnchorPoint(Vec2::ZERO);
    _normal->setPosition(Vec2(-15, -10));
    _tip->setAnchorPoint(Vec2::ZERO);
    _tip->setPosition(Vec2(-20, -20));

    this->addChild(_normal, 1);
    this->addChild(_tip);
    
    
    // 按钮
    auto imgSize = _normal->getContentSize();
    _cancle = Button::create(IMG_BUTTON_CANCLE);
    _ok = Button::create(IMG_BUTTON_OK);
    _cancle->setPosition(Vec2(10, imgSize.height));
    _ok->setPosition(Vec2(_size.width - 10, imgSize.height));
    this->addChild(_cancle);
    this->addChild(_ok);
    _cancle->addTouchEventListener(CC_CALLBACK_2(NewBuilding::cancleCallback, this));
    _ok->addTouchEventListener(CC_CALLBACK_2(NewBuilding::okCallback, this));
}


// 触摸事件
void NewBuilding::addTouch()
{
    auto dispatcher = this->getEventDispatcher();
    listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(NewBuilding::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(NewBuilding::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(NewBuilding::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool NewBuilding::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    Vec2 pos = this->getParent()->convertToNodeSpace(pTouch->getLocation());
    _deltaPos = 0.0;
    
    if(GM()->isPointInDiamond(this->getPosition(), TILED_SIZE*2, pos)) {
        _isTouched = true;
        listener->setSwallowTouches(true);
    }
    else {
        _isTouched = false;
        listener->setSwallowTouches(false);
    }
    return true;
}

void NewBuilding::onTouchMoved(Touch* pTouch, Event* pEvent)
{
    Vec2 pos = this->getParent()->convertToNodeSpace(pTouch->getLocation());
    Vec2 delta = pos - this->getPosition();
    _deltaPos += GM()->getDistance(Vec2(0, 0), pTouch->getDelta());
    
    if (_isTouched == true) {
        moveBuilding(delta);
    }
}

void NewBuilding::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    
}


// 移动建筑
void NewBuilding::moveBuilding(Vec2 delta)
{
    if (fabs(delta.x) >= TILED_WIDTH/2.0 || fabs(delta.y) >= TILED_HEIGHT/2.0) {
        int sgnX = 1, sgnY = 1;
        if (delta.x < 0) sgnX = -1;
        if (delta.y < 0) sgnY = -1;
        
        this->setPosition(this->getPosition() + Vec2(sgnX*TILED_WIDTH/2, sgnY*TILED_HEIGHT/2));
        
        Vec2 tiledPos = GM()->getTiledPos(this->getPosition());

        // 是否越界，或被其他设施占领
        if (GM()->isOutMap(this->getPosition()) || GM()->isCovered(tiledPos)) {
            this->setColor(Color3B::RED);
            _ok->setColor(Color3B::GRAY);
        }else {
            this->setColor(Color3B::GREEN);
            _ok->setColor(Color3B::WHITE);
        }
    }
}


void NewBuilding::okCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        if (_ok->getColor() != Color3B::GRAY) {
            GM()->_newBuild = false;
            GM()->_build = nullptr;
            
            // 建造新的BuildingSprite
            _pos = GM()->getTiledPos(this->getPosition());
            auto mapLayer = (HomeMapLayer*)this->getParent();
            mapLayer->newBuild(_type, _gold, _pos);
            
            this->removeFromParent();
        }
    }
}


void NewBuilding::cancleCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        GM()->_newBuild = false;
        GM()->_build = nullptr;
        this->removeFromParent();
    }
}


