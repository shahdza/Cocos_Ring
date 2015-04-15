#include "Building.h"


Building* Building::create(int index, AIManager* ai)
{
    Building *pRet = new(std::nothrow) Building();
    if (pRet && pRet->init(index, ai)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool Building::init(int index, AIManager* ai)
{
    if ( !BaseSprite::init() ) {
        return false;
    }
    
    _index = index;
    _ai = ai;
    
    loadData(index);
    
    showUI();
    addHPBar();
    
    schedule(schedule_selector(Building::update), 1.0f);
    
    return true;
}


void Building::loadData(int index)
{
    ValueMap data = DM()->_battleBuilding.at(index).asValueMap();
    
    _id                 = data["ID"].asInt();
    _BuildingID         = data["BuildingID"].asInt();
    _pos                = Vec2(data["PositionX"].asInt(), data["PositionY"].asInt());

    _type               = data["Type"].asInt();
    _name               = data["Name"].asString();
    _healthPoint        = data["HealthPoint"].asInt();
    _totalHP            = _healthPoint;

    // 攻击属性
    _isBroken           = false;
    _canAttack          = data["CanAttack"].asInt();
    _damage             = data["Damage"].asInt();
    _shootRange         = data["ShootRange"].asInt();
    _damageRange        = data["DamageRange"].asInt();

    // 覆盖地面
    GM()->setCoverd(_pos, 1);
}


void Building::showUI()
{
    this->setTexture(IMG_BUILDING_Floor);
    _size = this->getContentSize();
    
    string nomal_IMG = GM()->getBuildingIMG(_type);
    string broken_IMG = GM()->getBuildingBrokenIMG(_type);
    _normal = Sprite::create(nomal_IMG);
    _broken = Sprite::create(broken_IMG);
    _broken->setVisible(false);
    _broken->setOpacity(200);

    this->setPosition(GM()->getMapPos(_pos));
    _normal->setAnchorPoint(Vec2::ZERO);
    _normal->setPosition(Vec2(-15, -10));
    _broken->setAnchorPoint(Vec2::ZERO);
    _broken->setPosition(Vec2(-15, -10));

    this->addChild(_normal, 1);
    this->addChild(_broken, 1);
    
    // 遮罩
    this->setLocalZOrder(_pos.y + _pos.x);
    this->setOpacity(0);
}


void Building::addHPBar()
{
    auto bg = Sprite::create(IMG_BUILD_PRO_BK);
    _hpBar = LoadingBar::create(IMG_BUILD_PRO_ENEMY);
    bg->setPosition(this->getContentSize().width/2, _normal->getContentSize().height - 20);
    _hpBar->setPosition(bg->getContentSize()/2);
    bg->addChild(_hpBar);
    this->addChild(bg, 9, "Bar");
    
    _hpBar->setPercent(100.0 * _healthPoint / _totalHP);
}



void Building::atk()
{
    if(_isBroken == true) return;
    
    if(BUILDING_TYPE_ArrowTower == _type) {
        // 单体
        Vec2 src = GM()->getMapPos(_pos);
        Vec2 des = GM()->getMapPos(_target->_pos);
        
        auto bullet = BulletSprite::create(src, des, _damage, _target, IMG_BULLET_ARROW);
        this->getParent()->addChild(bullet, 99);
    }
    else if (BUILDING_TYPE_Laser == _type) {
        // 单体
        Vec2 src = GM()->getMapPos(_pos);
        Vec2 des = GM()->getMapPos(_target->_pos);
        
        auto bullet = BulletSprite::create(src, des, _damage, _target, IMG_BULLET_LASER);
        this->getParent()->addChild(bullet, 99);
    }
    else if(BUILDING_TYPE_Cannon == _type) {
        // 单体
        Vec2 src = GM()->getMapPos(_pos);
        Vec2 des = GM()->getMapPos(_target->_pos);
        
        auto bullet = BulletSprite::create(src, des, _damage, _target, IMG_BULLET_FIRE);
        this->getParent()->addChild(bullet, 99);
    }
}


void Building::hurt(int x)
{
    if (_healthPoint <= 0 || _isBroken == true) {
        _isBroken = true;
        return;
    }
    
    _healthPoint -= x;
    if (_healthPoint <= 0) {
        this->_isBroken = true;
        
        auto bg = (Sprite*)this->getChildByName("Bar");
        bg->removeFromParent();
        _normal->setVisible(false);
        _broken->setVisible(true);
        
        // 司令部
        if(_type == BUILDING_TYPE_BaseTower) {
            auto layer = (BattleMapLayer*)this->getParent();
            layer->_ai->gameOver(GAME_OVER_SUCCESS);
        }
        
    }
    else {
        _hpBar->setPercent(100.0 * _healthPoint / _totalHP);
    }
}


bool Building::isDeath()
{
    return _isBroken;
}


void Building::update(float dt)
{
    if (_isBroken == true) {
        this->unscheduleAllCallbacks();
        return;
    }
    if (_canAttack == 2) return;
    
    // 找目标攻击
    _target = _ai->getTargetFriend(_pos, _shootRange);
    if (_target != nullptr) {
        // 发射子弹
        atk();
    }
}

