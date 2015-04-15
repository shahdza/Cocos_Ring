#include "BulletSprite.h"


BulletSprite* BulletSprite::create(Vec2 src, Vec2 des, int damage, BaseSprite* target, string img)
{
    BulletSprite *pRet = new(std::nothrow) BulletSprite();
    if (pRet && pRet->init(src, des, damage, target, img)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool BulletSprite::init(Vec2 src, Vec2 des, int damage, BaseSprite* target, string img)
{
    if ( !Sprite::init() ) {
        return false;
    }
    
    _src = src;
    _des = des;
    _damage = damage;
    _target = target;
    _img = img;
    
    showUI();
    
    return true;
}


void BulletSprite::showUI()
{
    this->setTexture(_img);
    this->setPosition(_src);
    this->setScale(0.7);
    
    auto delta = _des - _src;
    auto ang = atan2(delta.y, delta.x) * 180 / acos(-1.0);
    ang = 360 - ang;
    this->setRotation(ang);
    
    auto move = MoveBy::create(0.2f, delta);
    auto func = CallFunc::create(CC_CALLBACK_0(BulletSprite::atk, this));
    this->runAction(Sequence::create(move, func, nullptr));
}


void BulletSprite::atk()
{
    _target->hurt(_damage);
    this->removeFromParent();
}

