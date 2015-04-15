#include "Soilder.h"


Soilder* Soilder::create(int soilderID, Vec2 pos, AIManager* ai)
{
    Soilder *pRet = new(std::nothrow) Soilder();
    if (pRet && pRet->init(soilderID, pos, ai)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool Soilder::init(int soilderID, Vec2 pos, AIManager* ai)
{
    if ( !BaseSprite::init() ) {
        return false;
    }
    
    _soilderID = soilderID;
    _pos = pos;
    _target = nullptr;
    _ai = ai;
    
    loadData();
    showUI();
    addHPBar();
    
    schedule(schedule_selector(Soilder::update), 0.8f);
    
    return true;
}


void Soilder::loadData()
{
    ValueMap& data = DM()->getSoilderInfo(_soilderID);
    
    _type           = data["Type"].asInt();
    _level          = data["Level"].asInt();
    _name           = data["Name"].asInt();
    
    _healthPoint    = data["HealthPoint"].asInt();
    _totalHP        = _healthPoint;
    _damage         = data["Damage"].asInt();
    _attackSpeed    = data["AttackSpeed"].asInt();
    _shootRange     = data["ShootRange"].asInt();
    
    _isbroken       = false;
}


void Soilder::showUI()
{
    switch (_type) {
        case SOILDER_TYPE_FIGHTER: {
            arm = Armature::create(ANIM_NAME_FIGHTER);
        }
            break;
        case SOILDER_TYPE_BOWMAN: {
            arm = Armature::create(ANIM_NAME_BOWMAN);
        }
            break;
        case SOILDER_TYPE_GUNNER: {
            arm = Armature::create(ANIM_NAME_GUNNER);
        }
            break;
        case SOILDER_TYPE_MEAT: {
            arm = Armature::create(ANIM_NAME_MEATSHIELD);
        }
            break;
        default:
            break;
    }
    
    this->addChild(arm);
    
    this->setPosition(GM()->getMapPos(_pos));
    this->setLocalZOrder((int)_pos.x + (int)_pos.y);
    
    this->setScale(0.6);
}


void Soilder::addHPBar()
{
    auto bg = Sprite::create(IMG_BUILD_PRO_BK);
    _hpBar = LoadingBar::create(IMG_BUILD_PRO);
    bg->setPosition(0, arm->getContentSize().height/2 + 10);
    _hpBar->setPosition(bg->getContentSize()/2);
    bg->addChild(_hpBar);
    this->addChild(bg, 9, "Bar");
    
    bg->setScale(0.7);
    _hpBar->setPercent(100.0 * _healthPoint / _totalHP);
}


void Soilder::update(float dt)
{
    if (_isbroken == true) {
        this->unscheduleAllCallbacks();
        return;
    }
    
    if (_target == nullptr || _target->isDeath()) {
        this->stopAllActions();
        _target = _ai->getTargetEnemy(_pos);
    }
    if (_target == nullptr) {
        arm->getAnimation()->play("run0");
        arm->getAnimation()->stop();
        return;
    }
    
    // 攻击
    if (_ai->isWithinShootRange(_pos, _target->_pos, _shootRange)) {
        _dir = GM()->getDir(_pos, _target->_pos);
        
        arm->getAnimation()->play("atk" + GM()->getIntToStr(_dir));
        
        auto delay = DelayTime::create(0.7f);
        auto func = CallFunc::create(CC_CALLBACK_0(Soilder::atk, this));
        this->runAction(Sequence::create(delay, func, nullptr));
    }
    
    // 走路
    else {
        Vec2 pos = _ai->getNextPos(_pos, _target->_pos, false);
        _dir = GM()->getDir(pos);
        
        this->runAction(MoveBy::create(1.0f, GM()->getMapDelta(_dir)));
        arm->getAnimation()->play("run" + GM()->getIntToStr( _dir <= 7 ? _dir : 1));
        
        _pos += pos;
        this->setLocalZOrder((int)_pos.x + (int)_pos.y);
    }
}


void Soilder::run()
{
    
}


void Soilder::atk()
{
    if (_isbroken == true || _healthPoint <= 0) {
        return;
    }
    if (_type == SOILDER_TYPE_BOWMAN) {
        Vec2 src = GM()->getMapPos(_pos);
        Vec2 des = GM()->getMapPos(_target->_pos);
        auto bullet = BulletSprite::create(src, des, _damage, _target, IMG_BULLET_ARROW);
        this->getParent()->addChild(bullet, 99);
    }
    else if(_type == SOILDER_TYPE_GUNNER) {
        Vec2 src = GM()->getMapPos(_pos);
        Vec2 des = GM()->getMapPos(_target->_pos);
        auto bullet = BulletSprite::create(src, des, _damage, _target, IMG_BULLET_SHELL);
        this->getParent()->addChild(bullet, 99);
    }
    else {
        _target->hurt(_damage);
    }
}


// 受伤
void Soilder::hurt(int x)
{
    if (_isbroken == true || _healthPoint <= 0) {
        _isbroken = true;
        return;
    }
    
    _healthPoint -= x;
    if (_healthPoint <= 0) {
        _isbroken = true;
        this->setVisible(false);
        arm->getAnimation()->stop();
    }
    else {
        _hpBar->setPercent(100.0 * _healthPoint / _totalHP);
    }
}


// 是否死亡
bool Soilder::isDeath()
{
    return _isbroken;
}

