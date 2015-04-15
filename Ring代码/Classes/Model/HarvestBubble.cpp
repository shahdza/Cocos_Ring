#include "HarvestBubble.h"


HarvestBubble* HarvestBubble::create(int type)
{
    HarvestBubble *pRet = new(std::nothrow) HarvestBubble();
    if (pRet && pRet->init(type)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool HarvestBubble::init(int type)
{
    if ( !Sprite::init() )
    {
        return false;
    }
    
    _type = type;
    isHarvest = false;
    
    showUI();
    addTouch();
    
    return true;
}


void HarvestBubble::showUI()
{
    _bubble = Sprite::create(IMG_BUBBLE);
    _bubble->setPosition(_bubble->getContentSize()/2);
    this->addChild(_bubble);
    
    this->setContentSize(_bubble->getContentSize());
    
    if(_type == HARVEST_TYPE_GOLD || _type == HARVEST_TYPE_BOTH) {
        _image = Sprite::create(IMG_GOLD);
    }
    else {
        _image = Sprite::create(IMG_WOOD);
    }
    
    auto size = this->getContentSize();
    _image->setPosition(Vec2(size.width/2, size.height/2 + 5));
    this->addChild(_image);
    
    beganAction();
}

void HarvestBubble::beganAction()
{
    auto scaleSmall = ScaleTo::create(0.2, 0.9);
    auto scaleBig = ScaleTo::create(0.2, 1.0);
    auto act = RepeatForever::create(Sequence::create(scaleSmall, scaleBig, nullptr));
    this->runAction(act);
}

void HarvestBubble::endAction()
{
    this->stopAllActions();
}


void HarvestBubble::addTouch()
{
    auto dispatcher = this->getEventDispatcher();
    listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HarvestBubble::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HarvestBubble::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HarvestBubble::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


bool HarvestBubble::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    if (isHarvest == true) return false;

    Vec2 pos = this->getParent()->convertToNodeSpace(pTouch->getLocation());
    
    if(this->getBoundingBox().containsPoint(pos)) {
        this->endAction();
        this->setScale(0.9f);
        _delta = 0.0;
        return true;
    }
    return false;
}


void HarvestBubble::onTouchMoved(Touch* pTouch, Event* pEvent)
{
    _delta += GM()->getDistance(Vec2(0, 0), pTouch->getDelta());
}


void HarvestBubble::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    this->setScale(1.0f);
    
    if (_delta <= LIMIT_DELTA) {
        harvest();
    }else {
        this->beganAction();
    }
}


void HarvestBubble::harvest()
{
    if(isHarvest == true) return;
    isHarvest = true;
    
    // hide bubble
    _bubble->setOpacity(0);
    
    // action image
    auto flip = RotateBy::create(0.3f, 0, -360*2);
    auto move = MoveBy::create(0.3f, Vec2(0, 100));
    auto fade = FadeTo::create(0.3f, 0);
    auto spawn = Spawn::create(flip, move, fade, nullptr);
    auto func = CallFunc::create(CC_CALLBACK_0(HarvestBubble::remove, this));
    _image->runAction(Sequence::create(spawn, func, nullptr));
    
    // callback
    _callback();
}


void HarvestBubble::remove()
{
    this->removeFromParent();
}

