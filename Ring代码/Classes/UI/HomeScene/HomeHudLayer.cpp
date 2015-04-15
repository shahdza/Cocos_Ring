#include "HomeHudLayer.h"


HomeHudLayer::HomeHudLayer()
{

}

HomeHudLayer::~HomeHudLayer()
{

}

bool HomeHudLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    loadData();
    showUI();
    
    return true;
}

void HomeHudLayer::loadData()
{
    ValueMap data = DM()->_player.at(1).asValueMap();
    
    _name = data["Name"].asString();
    _level = data["Level"].asInt();
    _exp = data["Exp"].asInt();
    _expRequire = DM()->getPlayerExpRequire(_level);
    if (_expRequire == -1) _expRequire = 1;
    _ringCount = data["RingCount"].asInt();
    _goldCount = data["GoldCount"].asInt();
    _woodCount = data["WoodCount"].asInt();
    _goldCapacity = data["GoldCapacity"].asInt();
    _woodCapacity = data["WoodCapacity"].asInt();
    
//    CCLOG("%s %d %d %d", _name.c_str(), _level, _exp, _expRequire);
//    CCLOG("(%d,%d,%d) (%d,%d)", _goldCount, _woodCount, _ringCount, _goldCapacity, _woodCapacity);
}

void HomeHudLayer::showUI()
{
    auto ui = GUIReader::getInstance()->widgetFromJsonFile(UI_LAYER_HOMEHUD);
    this->addChild(ui, 0, "UI");
    
    // WorldButton
    auto btnWorld = (Button*)Helper::seekWidgetByName(ui, "WorldButton");
    btnWorld->addTouchEventListener(CC_CALLBACK_2(HomeHudLayer::btnCallback, this));
    // BuildButton
    auto btnBuild = (Button*)Helper::seekWidgetByName(ui, "BuildButton");
    btnBuild->addTouchEventListener(CC_CALLBACK_2(HomeHudLayer::btnCallback, this));
    
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

void HomeHudLayer::setMapLayer(Layer* layer)
{
    _mapLayer = layer;
}


void HomeHudLayer::addPlayerExp(int add)
{
    DM()->updatePlayerExp(add);
    loadData();

    // player
    auto ui = (Widget*)this->getChildByName("UI");
    auto playerLevel = (Text*)Helper::seekWidgetByName(ui, "PlayerLevel");
    auto playerBar = (LoadingBar*)Helper::seekWidgetByName(ui, "PlayerBar");
    playerLevel->setString(GM()->getIntToStr(_level));
    playerBar->setPercent(100.0 * _exp / _expRequire);
}


void HomeHudLayer::addGold(int add)
{
    _goldCount = GM()->getMin(_goldCount + add, _goldCapacity);
    DM()->updateGold(_goldCount);
    
    auto ui = (Widget*)this->getChildByName("UI");
    auto goldCount = (Text*)Helper::seekWidgetByName(ui, "GoldCount");
    auto goldCapacity = (Text*)Helper::seekWidgetByName(ui, "GoldCapacity");
    auto goldBar = (LoadingBar*)Helper::seekWidgetByName(ui, "GoldBar");
    
    goldCount->setString(GM()->getIntToStr(_goldCount));
    goldCapacity->setString(GM()->getIntToStr(_goldCapacity));
    goldBar->setPercent(100.0 * _goldCount / _goldCapacity);
}


void HomeHudLayer::addWood(int add)
{
    _woodCount = GM()->getMin(_woodCount + add, _woodCapacity);
    DM()->updateWood(_woodCount);
    
    auto ui = (Widget*)this->getChildByName("UI");
    auto woodCount = (Text*)Helper::seekWidgetByName(ui, "WoodCount");
    auto woodCapacity = (Text*)Helper::seekWidgetByName(ui, "WoodCapacity");
    auto woodBar = (LoadingBar*)Helper::seekWidgetByName(ui, "WoodBar");
    
    woodCount->setString(GM()->getIntToStr(_woodCount));
    woodCapacity->setString(GM()->getIntToStr(_woodCapacity));
    woodBar->setPercent(100.0 * _woodCount / _woodCapacity);
}


void HomeHudLayer::setGoldCapacity(int capacity)
{
    _goldCapacity = capacity;
    DM()->updateGoldCapacity(_goldCapacity);
    
    auto ui = (Widget*)this->getChildByName("UI");
    auto goldCount = (Text*)Helper::seekWidgetByName(ui, "GoldCount");
    auto goldCapacity = (Text*)Helper::seekWidgetByName(ui, "GoldCapacity");
    auto goldBar = (LoadingBar*)Helper::seekWidgetByName(ui, "GoldBar");
    
    goldCount->setString(GM()->getIntToStr(_goldCount));
    goldCapacity->setString(GM()->getIntToStr(_goldCapacity));
    goldBar->setPercent(100.0 * _goldCount / _goldCapacity);
}


void HomeHudLayer::setWoodCapacity(int capacity)
{
    _woodCapacity = capacity;
    DM()->updateWoodCapacity(_woodCapacity);
    
    auto ui = (Widget*)this->getChildByName("UI");
    auto woodCount = (Text*)Helper::seekWidgetByName(ui, "WoodCount");
    auto woodCapacity = (Text*)Helper::seekWidgetByName(ui, "WoodCapacity");
    auto woodBar = (LoadingBar*)Helper::seekWidgetByName(ui, "WoodBar");
    
    woodCount->setString(GM()->getIntToStr(_woodCount));
    woodCapacity->setString(GM()->getIntToStr(_woodCapacity));
    woodBar->setPercent(100.0 * _woodCount / _woodCapacity);
}


void HomeHudLayer::btnCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        Button* btn = (Button*)sender;
        string name = btn->getName();
        if (name == "WorldButton") {
            GM()->enterWorldScene();
        }
        else if(name == "BuildButton") {
            // CCLOG("BuildButton");
            auto buildDialog = NewBuildDialog::create();
            this->getParent()->addChild(buildDialog, 99);
        }
    }
}

