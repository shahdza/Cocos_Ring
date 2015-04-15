#include "BuildingSprite.h"


BuildingSprite* BuildingSprite::create(int index)
{
    BuildingSprite *pRet = new(std::nothrow) BuildingSprite();
    if (pRet && pRet->init(index)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool BuildingSprite::init(int index)
{
    if ( !Sprite::init() ) {
        return false;
    }
    
    _isSelected = false;
    _isTouched = false;
    _canTouched = true;
    
    _index = index;
    
    loadData(index);
    
    showUI();
    showUpgradePro();
    showBubble();
    
    addTouch();
    scheduleUpdate();
    
    // 设置名称
    this->setName("BuildingSprite");
    
    return true;
}


void BuildingSprite::loadData(int index)
{
    ValueMap data = DM()->_building.at(index).asValueMap();
    
    _id                 = data["ID"].asInt();
    _BuildingID         = data["BuildingID"].asInt();
    _pos                = Vec2(data["PositionX"].asInt(), data["PositionY"].asInt());
    _buildState         = data["BuildState"].asInt();
    _lastBuildTime      = data["LastBuildTime"].asInt();
    _lastGoldHarvest    = data["LastGoldHarvest"].asInt();
    _lastWoodHarvest    = data["LastWoodHarvest"].asInt();

    _type               = data["Type"].asInt();
    _level              = data["Level"].asInt();
    _name               = data["Name"].asString();
    _healthPoint        = data["HealthPoint"].asInt();
    _description        = data["Description"].asString();

    _goldRequire        = data["GoldRequire"].asInt();
    _woodRequire        = data["WoodRequire"].asInt();
    _timeRequire        = data["TimeRequire"].asInt();
    _baseLevelRequire   = data["BaseLevelRequire"].asInt();
    _playerLevelRequire = data["PlayerLevelRequire"].asInt();
    _expReward          = data["ExpReward"].asInt();

    // 生产属性
    _goldProduct        = data["GoldProduct"].asInt();
    _woodProduct        = data["WoodProduct"].asInt();
    // 资源属性
    _goldCapacity       = data["GoldCapacity"].asInt();
    _woodCapacity       = data["WoodCapacity"].asInt();
    // 攻击属性
    _isBroken           = false;
    _canAttack          = data["CanAttack"].asInt();
    _damage             = data["Damage"].asInt();
    _attackSpeed        = data["AttackSpeed"].asInt();
    _shootRange         = data["ShootRange"].asInt();
    _damageRange        = data["DamageRange"].asInt();
    

    // 覆盖地面
    GM()->setCoverd(_pos, 1);
    
//    CCLOG("%d: %d, %s (%d,%d)", _id, _BuildingID, _name.c_str(), _buildState, _lastBuildTime);
}


void BuildingSprite::showUI()
{
    this->setTexture(IMG_BUILDING_Floor);
    _size = this->getContentSize();
    
    string nomal_IMG = GM()->getBuildingIMG(_type);
    string broken_IMG = GM()->getBuildingBrokenIMG(_type);
    _normal = Sprite::create(nomal_IMG);
    _broken = Sprite::create(broken_IMG);
    _tip = Sprite::create(IMG_BUILDING_ArrowTip);
    _broken->setOpacity(0);
    _tip->setOpacity(0);

    this->setPosition(GM()->getMapPos(_pos));
    _normal->setAnchorPoint(Vec2::ZERO);
    _normal->setPosition(Vec2(-15, -10));
    _tip->setAnchorPoint(Vec2::ZERO);
    _tip->setPosition(Vec2(-20, -20));

    this->addChild(_normal, 1);
    this->addChild(_broken, 1);
    this->addChild(_tip);
    
    // 遮罩
    this->setLocalZOrder(_pos.y + _pos.x);
    this->setOpacity(0);

}


// 触摸事件
void BuildingSprite::addTouch()
{
    auto dispatcher = this->getEventDispatcher();
    listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(BuildingSprite::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(BuildingSprite::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(BuildingSprite::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool BuildingSprite::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    if (_canTouched == false) return false;
    if (GM()->_newBuild == true) return false;

    Vec2 pos = this->getParent()->convertToNodeSpace(pTouch->getLocation());
    _deltaPos = 0.0;
    
    if(GM()->isPointInDiamond(this->getPosition(), TILED_SIZE*2, pos)) {
        _isTouched = true;
        if (_isSelected == true) {
            listener->setSwallowTouches(true);
        }
    }
    else {
        _isTouched = false;
        _isSelected = false;
        listener->setSwallowTouches(false);
    }
    return true;
}

void BuildingSprite::onTouchMoved(Touch* pTouch, Event* pEvent)
{
    Vec2 pos = this->getParent()->convertToNodeSpace(pTouch->getLocation());
    Vec2 delta = pos - this->getPosition();
    _deltaPos += GM()->getDistance(Vec2(0, 0), pTouch->getDelta());
    
    if (_isSelected == true) {
        moveBuilding(delta);
    }
}

void BuildingSprite::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    // 标记为被选中
    if(_isTouched == true) {
        if (_deltaPos <= LIMIT_DELTA) {
            
            // 第一次点击
            if (_isSelected == false) {
                // 先去除占地
                GM()->setCoverd(_pos, -1);
            }
            
            _isSelected = true;
            this->setOpacity(255);
            this->setColor(Color3B::GREEN);
            this->setLocalZOrder(TILED_TOTAL_X + TILED_TOTAL_Y + 1);
            _tip->setOpacity(255);
            selectedAction();
        }
    }
    else {
        if (_isShowOpt == true) {
            _isSelected = false;
            this->setOpacity(0);
            this->setColor(Color3B::WHITE);
            this->setTiledPos();
            _tip->setOpacity(0);
            unselectedAction();
        }
    }
    
    // 显示/隐藏操作opt
    if (_isTouched == true) {
        if (_deltaPos <= LIMIT_DELTA) {
            auto maplayer = (HomeMapLayer*)this->getParent();
            auto optlayer = ((HomeScene*)maplayer->getParent())->_optLayer;
            optlayer->show(this);
            _isShowOpt = true;
        }
    }
    else if(_isShowOpt == true) {
        auto maplayer = (HomeMapLayer*)this->getParent();
        auto optlayer = ((HomeScene*)maplayer->getParent())->_optLayer;
        optlayer->hide(this);
        _isShowOpt = false;
    }
}

// 取消选中
void BuildingSprite::detach()
{
    _isTouched = false;
    _isSelected = false;
    listener->setSwallowTouches(false);
    
    if (_isShowOpt == true) {
        this->setOpacity(0);
        this->setColor(Color3B::WHITE);
        this->setTiledPos();
        _tip->setOpacity(0);
        unselectedAction();
        
        auto maplayer = (HomeMapLayer*)this->getParent();
        auto optlayer = ((HomeScene*)maplayer->getParent())->_optLayer;
        optlayer->hide(this);
        _isShowOpt = false;
    }
}


// 被选中时的动画效果
void BuildingSprite::selectedAction()
{
    unselectedAction();

    auto scaleUp = ScaleTo::create(0.1f, 1.1f);
    auto scaleDown = ScaleTo::create(0.1f, 1.0f);
    auto moveUp = MoveBy::create(0.1f, Vec2(0, 3));
    auto moveDown = MoveBy::create(0.1f, Vec2(0, -3));
    auto tintIn = TintTo::create(1.0f, Color3B(160, 160, 160));
    auto tintOut = TintTo::create(1.0f, Color3B::WHITE);
    auto act1 = Sequence::create(scaleUp, scaleDown, nullptr);
    auto act2 = Sequence::create(moveUp, moveDown, nullptr);
    auto act3 = RepeatForever::create(Sequence::create(tintIn, tintOut, nullptr));
    _normal->runAction(act1);
    _normal->runAction(act2);
    _normal->runAction(act3);
}


// 未被选择，取消动画
void BuildingSprite::unselectedAction()
{
    _normal->stopAllActions();
    _normal->setScale(1.0f);
    _normal->setPosition(Vec2(-15, -10));
    _normal->setColor(Color3B::WHITE);
}


// 移动建筑
void BuildingSprite::moveBuilding(Vec2 delta)
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
        }else {
            this->setColor(Color3B::GREEN);
        }
    }
}


// 设置瓦片坐标
void BuildingSprite::setTiledPos()
{
    auto mapPos = this->getPosition();
    if (GM()->isOutMap(mapPos) || GM()->isCovered(GM()->getTiledPos(mapPos))) {
        this->setPosition(GM()->getMapPos(_pos));
    }
    else {
        _pos = GM()->getTiledPos(this->getPosition());
        
        // 更新数据库
        DM()->updateBuildingPos(_id, _pos);
    }
    this->setLocalZOrder(_pos.y + _pos.x);
    
    // 恢复占地
    GM()->setCoverd(_pos, 1);
}


// 加入升级进度条
void BuildingSprite::showUpgradePro()
{
    if (_buildState == BUILDING_STATE_BUILDING) {
        // 加入进度条
        auto buildPro = BuildProcess::create(this);
        buildPro->setPosition(this->getContentSize().width/2, _normal->getContentSize().height - 20);
        this->addChild(buildPro, 9);
    }
}

// 升级设施
void BuildingSprite::upgrade()
{
    // 更新数据库 : 正在建设
    DM()->updateBuildingBuildState(_id, BUILDING_STATE_BUILDING);
    
    // 更新内容
    ValueMap& map = DM()->getBuilding(_id);
    _buildState = BUILDING_STATE_BUILDING;
    _lastBuildTime = map["LastBuildTime"].asInt();
    
    showUpgradePro();
}


// 升级完成
void BuildingSprite::upgradeFinished()
{
    // 动画特效
    auto scaleUp = ScaleTo::create(0.1f, 1.1f);
    auto scaleDown = ScaleTo::create(0.1f, 1.0f);
    _normal->runAction(Sequence::create(scaleUp, scaleDown, nullptr));
    
    // 更新HudLayer的玩家经验
    auto homeScene = (HomeScene*)this->getParent()->getParent();
    auto hudLayer = homeScene->_hudLayer;
    hudLayer->addPlayerExp(_expReward);

    // 获取下一等级信息，并更新数值
    ValueMap& data = DM()->getBuildingNextInfo(_BuildingID);
    _BuildingID         = data["BuildingID"].asInt();
    _buildState         = BUILDING_STATE_FINISHED;
    
    _level              = data["Level"].asInt();
    _healthPoint        = data["HealthPoint"].asInt();
    
    _goldRequire        = data["GoldRequire"].asInt();
    _woodRequire        = data["WoodRequire"].asInt();
    _timeRequire        = data["TimeRequire"].asInt();
    _baseLevelRequire   = data["BaseLevelRequire"].asInt();
    _playerLevelRequire = data["PlayerLevelRequire"].asInt();
    _expReward          = data["ExpReward"].asInt();
    // 生产属性
    _goldProduct        = data["GoldProduct"].asInt();
    _woodProduct        = data["WoodProduct"].asInt();
    // 资源属性
    _goldCapacity       = data["GoldCapacity"].asInt();
    _woodCapacity       = data["WoodCapacity"].asInt();
    // 攻击属性
    _damage             = data["Damage"].asInt();
    _attackSpeed        = data["AttackSpeed"].asInt();
    _shootRange         = data["ShootRange"].asInt();
    _damageRange        = data["DamageRange"].asInt();
    

    // 更新DM()数据
    DM()->updateBuildingLevel(_id);

    
    // 特殊建筑还要更新一些信息
    switch (_type) {
        // 司令部
        case BUILDING_TYPE_BaseTower: {
            // 更新Hud的capacity
            hudLayer->setGoldCapacity(_goldCapacity);
            hudLayer->setWoodCapacity(_woodCapacity);
        }
            break;
            
        // 雷达
        case BUILDING_TYPE_Raider: {
            // 更新迷雾信息
            DM()->updateMiwuType(_level);
        }
            break;
            
        // 英雄旅馆
        case BUILDING_TYPE_HeroHotel: {
            
        }
            break;
            
        // 兵营
        case BUILDING_TYPE_Camp: {
            
        }
            break;
            
        // 研究所
        case BUILDING_TYPE_ResearchLab: {
            
        }
            break;
        default:
            break;
    }
    
    // 更新OptLayer
    auto optLayer = homeScene->_optLayer;
    if (optLayer->_buildingSprite == this) {
        optLayer->show(this);
    }
}


// 显示收获气泡
void BuildingSprite::showBubble()
{
    if (_type == BUILDING_TYPE_MineFactory || _type == BUILDING_TYPE_WoodFactory) {
        scheduleUpdate();
    }
}

// 更新
void BuildingSprite::update(float dt)
{
    // 是否仍在升级中
    
    // 是否为金矿厂、木材厂
    if (_type != BUILDING_TYPE_MineFactory && _type != BUILDING_TYPE_WoodFactory) return;
    if (bubble != nullptr) return;
    
    int stamp = GM()->getTimeStamp();
    
    if (_type == BUILDING_TYPE_MineFactory) {
        if (_lastGoldHarvest == 0) return;
        if (stamp - _lastGoldHarvest > 60) {
            bubble = HarvestBubble::create(HARVEST_TYPE_GOLD);
            bubble->setPosition(Vec2(_size.width/2, _normal->getContentSize().height ));
            this->addChild(bubble, 100);
            bubble->_callback = CC_CALLBACK_0(BuildingSprite::harvest, this);
        }
    }
    else {
        if (_lastWoodHarvest == 0) return;
        if (stamp - _lastWoodHarvest > 60) {
            bubble = HarvestBubble::create(HARVEST_TYPE_WOOD);
            bubble->setPosition(Vec2(_size.width/2, _normal->getContentSize().height ));
            this->addChild(bubble, 100);
            bubble->_callback = CC_CALLBACK_0(BuildingSprite::harvest, this);
        }
    }
}


// 收获资源
void BuildingSprite::harvest()
{
    int stamp = GM()->getTimeStamp();
    
    if (_type == BUILDING_TYPE_MineFactory) {
        int diff = stamp - _lastGoldHarvest;
        int gold = (diff * _goldProduct) / 3600;
        
        HomeMapLayer* parent = (HomeMapLayer*)this->getParent();
        HomeHudLayer* hud = (HomeHudLayer*)parent->_hudLayer;
        hud->addGold(gold);
        
        _lastGoldHarvest = stamp;
        DM()->updateLastGoldHarvest(_id, _lastGoldHarvest);
    }
    else {
        int diff = stamp - _lastWoodHarvest;
        int wood = (diff * _woodProduct) / 3600;
        
        HomeMapLayer* parent = (HomeMapLayer*)this->getParent();
        HomeHudLayer* hud = (HomeHudLayer*)parent->_hudLayer;
        hud->addWood(wood);
        
        _lastWoodHarvest = stamp;
        DM()->updateLastWoodHarvest(_id, _lastWoodHarvest);
    }

    bubble = nullptr;
}
