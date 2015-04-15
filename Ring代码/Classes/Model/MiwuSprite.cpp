#include "MiwuSprite.h"


bool MiwuSprite::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }
    
    _id = 0;
    _level = 0;
    _type = 0;
    _pos = Vec2(0, 0);
    
    return true;
}


void MiwuSprite::setMiwu(int index)
{
    loadData(index);
    showUI();
}


void MiwuSprite::loadData(int index)
{
    ValueMap data = DM()->_miwu.at(index).asValueMap();
    _id = data["MiwuID"].asInt();
    _level = data["Level"].asInt();
    _pos = Vec2(data["PositionX"].asFloat(), data["PositionY"].asFloat());
    _type = data["Type"].asInt();
}


void MiwuSprite::showUI()
{
    this->setPosition(_pos);
    this->setTexture(IMG_MIWU);
}


bool MiwuSprite::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    Vec2 pos = this->getParent()->convertToNodeSpace(pTouch->getLocation());

    if(GM()->isPointInRect(this->getPosition(), this->getContentSize(), pos)) {
        return true;
    }
    return false;
}


void MiwuSprite::onTouchMoved(Touch* pTouch, Event* pEvent)
{
    
}

void MiwuSprite::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    
}

