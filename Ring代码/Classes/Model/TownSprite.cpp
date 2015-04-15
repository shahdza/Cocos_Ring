#include "TownSprite.h"
USING_NS_CC;


bool TownSprite::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }
    
    _id = 0;
    _name = "";
    _level = 0;
    _type = 0;
    _pos = Vec2(0, 0);
    _description = "";
    
    _goldReward = 0;
    _woodReward = 0;
    _ringReward = 0;
    
    _goldProduct = 0;
    _woodProduct = 0;
    _lastHarvest = 0;
    
    _img = "";
    
    bubble = nullptr;
    
    return true;
}


void TownSprite::setTown(int index)
{
    loadData(index);
    showUI();
    scheduleUpdate();
}


void TownSprite::loadData(int index)
{
    ValueMap data = DM()->_town.at(index).asValueMap();
    
    _id = data["TownID"].asInt();
    _name = data["Name"].asString();
    _level = data["Level"].asInt();
    _type = data["Type"].asInt();
    _pos = Vec2(data["PositionX"].asFloat(), data["PositionY"].asFloat());
    _description = data["Description"].asString();
    _goldReward = data["GoldReward"].asInt();
    _woodReward = data["WoodReward"].asInt();
    _ringReward = data["RingReward"].asInt();
    _goldProduct = data["GoldProduct"].asInt();
    _woodProduct = data["WoodProduct"].asInt();
    _lastHarvest = data["LastHarvest"].asInt();
    
//    CCLOG("%d %s %d (%.1f,%.1f) %d %s", _id,_name.c_str(),_level,_pos.x,_pos.y,_type,_description.c_str());
//    CCLOG("(%d,%d,%d) (%d,%d,%d)", _goldReward,_woodReward,_ringReward,_goldProduct,_woodProduct,_lastHarvest);
}


void TownSprite::showUI()
{
    switch (_type) {
        case TOWN_TYPE_HOME:
            _img = IMG_TOWN_HOME;
            break;
        case TOWN_TYPE_CHAPTER:
            _img = IMG_TOWN_CHAPTER;
            break;
        case TOWN_TYPE_LIBERATE:
            _img = IMG_TOWN_LIBERATE;
            break;
        default:
            break;
    }
    
    this->setPosition(_pos);
    this->setTexture(_img);
    this->addPendant();
}


// 添加配件
void TownSprite::addPendant()
{
    // 城池名称
    auto lbName = Label::createWithSystemFont(_name, FONT_ARIAL, 20);
    lbName->setAnchorPoint(Vec2(0.5, 0.0));
    lbName->setPosition(this->getContentSize().width/2, 0);
    this->addChild(lbName);

    // 城池等级
    if (_type != TOWN_TYPE_HOME) {
        char level[2];
        sprintf(level, "%d", _level);
        auto lbLevel = Label::createWithSystemFont(level, FONT_ARIAL, 20);
        lbLevel->setAnchorPoint(Vec2(0.5, 1.0));
        lbLevel->setPosition(this->getContentSize().width/2, 0);
        this->addChild(lbLevel);
    }
}


// 显示消息框
void TownSprite::showDialog()
{
    TownDialog* dialog = TownDialog::create(this);
    this->getParent()->getParent()->addChild(dialog, 3);
}


// 更新
void TownSprite::update(float dt)
{
    if (_type != TOWN_TYPE_LIBERATE) return;
    if (_lastHarvest == 0) return;
    if (bubble != nullptr) return;
    
    int stamp = GM()->getTimeStamp();
    if (stamp - _lastHarvest > 60) {
        bubble = HarvestBubble::create(HARVEST_TYPE_BOTH);
        bubble->setPosition(this->getPosition() + Vec2(0, this->getContentSize().height/2 + 20));
        this->getParent()->addChild(bubble, 2);
        bubble->_callback = CC_CALLBACK_0(TownSprite::harvest, this);
    }
}


// 收获资源
void TownSprite::harvest()
{
//    CCLOG("harvest");

    int stamp = GM()->getTimeStamp();
    int diff = stamp - _lastHarvest;
    int gold = (diff * _goldProduct) / 3600;
    int wood = (diff * _woodProduct) / 3600;
    
    WorldMapLayer* parent = (WorldMapLayer*)this->getParent();
    WorldHudLayer* hud = (WorldHudLayer*)parent->_hudLayer;
    hud->addGold(gold);
    hud->addWood(wood);
    
    _lastHarvest = stamp;
    DM()->updateTownHarvest(_id, _lastHarvest);
    bubble = nullptr;
}


bool TownSprite::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    Vec2 pos = this->getParent()->convertToNodeSpace(pTouch->getLocation());
    
    Vec2 center = this->getPosition();
    CCSize size = this->getContentSize();
    if(GM()->isPointInRect(center - Vec2(0, size.height/6.0), Size(size.width, size.height*2.0/3.0), pos)) {
        this->setScale(0.9f);
        _delta = 0.0;
        return true;
    }
    return false;
}


void TownSprite::onTouchMoved(Touch* pTouch, Event* pEvent)
{
    _delta += GM()->getDistance(Vec2(0, 0), pTouch->getDelta());
}


void TownSprite::onTouchEnded(Touch* pTouch, Event* pEvent)
{
    this->setScale(1.0f);
    
    if (_delta <= LIMIT_DELTA) {
        moveToCenter();
        showDialog();
    }
}


// 将城池移动到屏幕中心, 稍微靠下的位置
void TownSprite::moveToCenter()
{
    Vec2 pos = this->getPosition();
    ((WorldMapLayer*)this->getParent())->moveToCenter(pos, 0.2);
}

