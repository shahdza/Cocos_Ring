#include "WorldHudLayer.h"


WorldHudLayer::WorldHudLayer()
{
    
}


WorldHudLayer::~WorldHudLayer()
{
    
}


bool WorldHudLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    loadData();
    showUI();
    
    return true;
}


void WorldHudLayer::loadData()
{
    ValueMap data = DM()->_player.at(1).asValueMap();
    
    _name = data["Name"].asString();
    _level = data["Level"].asInt();
    _exp = data["Exp"].asInt();
    _expRequire = DM()->getPlayerExpRequire(_level);
    _ringCount = data["RingCount"].asInt();
    _goldCount = data["GoldCount"].asInt();
    _woodCount = data["WoodCount"].asInt();
    _goldCapacity = data["GoldCapacity"].asInt();
    _woodCapacity = data["WoodCapacity"].asInt();
    
//    CCLOG("%s %d %d %d", _name.c_str(), _level, _exp, _expRequire);
//    CCLOG("(%d,%d,%d) (%d,%d)", _goldCount, _woodCount, _ringCount, _goldCapacity, _woodCapacity);
}


void WorldHudLayer::showUI()
{
    auto ui = GUIReader::getInstance()->widgetFromJsonFile(UI_LAYER_WORLDHUD);
    this->addChild(ui, 0, "UI");
    
    // HomeButton
    auto btnEnter = (Button*)Helper::seekWidgetByName(ui, "HomeButton");
    btnEnter->addTouchEventListener(CC_CALLBACK_2(WorldHudLayer::btnCallback, this));

    // player
    auto playerName = (Text*)Helper::seekWidgetByName(ui, "PlayerName");
    auto playerLevel = (Text*)Helper::seekWidgetByName(ui, "PlayerLevel");
    auto playerBar = (LoadingBar*)Helper::seekWidgetByName(ui, "PlayerBar");
    playerName->setString(_name);
    playerLevel->setString(GM()->getIntToStr(_level));
    playerBar->setPercent(100.0 * _exp / _expRequire);
    // gold
    auto goldCount = (Text*)Helper::seekWidgetByName(ui, "GoldCount");
    auto goldCapacity = (Text*)Helper::seekWidgetByName(ui, "GoldCapacity");
    auto goldBar = (LoadingBar*)Helper::seekWidgetByName(ui, "GoldBar");
    goldCount->setString(GM()->getIntToStr(_goldCount));
    goldCapacity->setString(GM()->getIntToStr(_goldCapacity));
    goldBar->setPercent(100.0 * _goldCount / _goldCapacity);
    // wood
    auto woodCount = (Text*)Helper::seekWidgetByName(ui, "WoodCount");
    auto woodCapacity = (Text*)Helper::seekWidgetByName(ui, "WoodCapacity");
    auto woodBar = (LoadingBar*)Helper::seekWidgetByName(ui, "WoodBar");
    woodCount->setString(GM()->getIntToStr(_woodCount));
    woodCapacity->setString(GM()->getIntToStr(_woodCapacity));
    woodBar->setPercent(100.0 * _woodCount / _woodCapacity);
    // ring
    auto ringCount = (Text*)Helper::seekWidgetByName(ui, "RingCount");
    ringCount->setString(GM()->getIntToStr(_ringCount));
}

void WorldHudLayer::addGold(int add)
{
    auto ui = (Widget*)this->getChildByName("UI");
    auto goldCount = (Text*)Helper::seekWidgetByName(ui, "GoldCount");
    auto goldCapacity = (Text*)Helper::seekWidgetByName(ui, "GoldCapacity");
    auto goldBar = (LoadingBar*)Helper::seekWidgetByName(ui, "GoldBar");
    
    _goldCount = GM()->getMin(_goldCount + add, _goldCapacity);
    DM()->updateGold(_goldCount);
    
    goldCount->setString(GM()->getIntToStr(_goldCount));
    goldCapacity->setString(GM()->getIntToStr(_goldCapacity));
    goldBar->setPercent(100.0 * _goldCount / _goldCapacity);
}


void WorldHudLayer::addWood(int add)
{
    auto ui = (Widget*)this->getChildByName("UI");
    auto woodCount = (Text*)Helper::seekWidgetByName(ui, "WoodCount");
    auto woodCapacity = (Text*)Helper::seekWidgetByName(ui, "WoodCapacity");
    auto woodBar = (LoadingBar*)Helper::seekWidgetByName(ui, "WoodBar");
    
    _woodCount = GM()->getMin(_woodCount + add, _woodCapacity);
    DM()->updateWood(_woodCount);
    
    woodCount->setString(GM()->getIntToStr(_woodCount));
    woodCapacity->setString(GM()->getIntToStr(_woodCapacity));
    woodBar->setPercent(100.0 * _woodCount / _woodCapacity);
}


void WorldHudLayer::setMapLayer(Layer* layer)
{
    _mapLayer = layer;
}


void WorldHudLayer::btnCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        GM()->enterHomeScene();
    }
}

