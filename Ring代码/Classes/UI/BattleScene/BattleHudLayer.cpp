#include "BattleHudLayer.h"


bool BattleHudLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    loadData();
    showUI();
    
    return true;
}

void BattleHudLayer::loadData()
{
    ValueMap& data = DM()->getTownInfo(GM()->_townID);
    ValueMap& s1 = DM()->getSoilder(1);
    ValueMap& s2 = DM()->getSoilder(2);
    ValueMap& s3 = DM()->getSoilder(3);
    ValueMap& s4 = DM()->getSoilder(4);
    
    _name = data["Name"].asString();
    _level = data["Level"].asInt();
    _goldReward = data["GoldReward"].asInt();
    _woodReward = data["WoodReward"].asInt();
    _ringReward = data["RingReward"].asInt();
    
    _count[1] = s1["Count"].asInt();
    _count[2] = s2["Count"].asInt();
    _count[3] = s3["Count"].asInt();
    _count[4] = s4["Count"].asInt();
    
    skill1 = 1;
    skill2 = 1;
}

void BattleHudLayer::showUI()
{
    auto ui = GUIReader::getInstance()->widgetFromJsonFile(UI_DIALOG_BATTLEHUD);
    this->addChild(ui, 0, "UI");
    
    // select
    auto btn0 = (Button*)Helper::seekWidgetByName(ui, "Button0");
    auto btn1 = (Button*)Helper::seekWidgetByName(ui, "Button1");
    auto btn2 = (Button*)Helper::seekWidgetByName(ui, "Button2");
    auto btn3 = (Button*)Helper::seekWidgetByName(ui, "Button3");
    auto btn4 = (Button*)Helper::seekWidgetByName(ui, "Button4");
    btn0->addTouchEventListener(CC_CALLBACK_2(BattleHudLayer::selectCallback, this));
    btn1->addTouchEventListener(CC_CALLBACK_2(BattleHudLayer::selectCallback, this));
    btn2->addTouchEventListener(CC_CALLBACK_2(BattleHudLayer::selectCallback, this));
    btn3->addTouchEventListener(CC_CALLBACK_2(BattleHudLayer::selectCallback, this));
    btn4->addTouchEventListener(CC_CALLBACK_2(BattleHudLayer::selectCallback, this));
    btn0->setBright(true);
    btn1->setBright(false);
    btn2->setBright(false);
    btn3->setBright(false);
    btn4->setBright(false);
    _select = 0;
    
    // skill
    auto skill1 = (Button*)Helper::seekWidgetByName(ui, "Skill1");
    auto skill2 = (Button*)Helper::seekWidgetByName(ui, "Skill2");
    skill1->addTouchEventListener(CC_CALLBACK_2(BattleHudLayer::skillCallback, this));
    skill2->addTouchEventListener(CC_CALLBACK_2(BattleHudLayer::skillCallback, this));
    
    // retreat
    auto retreat = (Button*)Helper::seekWidgetByName(ui, "RetreatButton");
    retreat->addTouchEventListener(CC_CALLBACK_2(BattleHudLayer::retreatCallback, this));

    showInfo();
}


void BattleHudLayer::showInfo()
{
    auto ui = (Widget*)this->getChildByName("UI");
    
    // 城池属性
    auto level = (Text*)Helper::seekWidgetByName(ui, "Level");
    auto name = (Text*)Helper::seekWidgetByName(ui, "Name");
    auto goldreward = (Text*)Helper::seekWidgetByName(ui, "GoldReward");
    auto woodreward = (Text*)Helper::seekWidgetByName(ui, "WoodReward");
    auto ringreward = (Text*)Helper::seekWidgetByName(ui, "RingReward");
    
    level->setString(GM()->getIntToStr(_level));
    name->setString(_name);
    goldreward->setString(GM()->getIntToStr(_goldReward));
    woodreward->setString(GM()->getIntToStr(_woodReward));
    ringreward->setString(GM()->getIntToStr(_ringReward));
    
    // 士兵数量
    auto fighterCount = (Text*)Helper::seekWidgetByName(ui, "FighterCount");
    auto bowmanCount = (Text*)Helper::seekWidgetByName(ui, "BowmanCount");
    auto gunnerCount = (Text*)Helper::seekWidgetByName(ui, "GunnerCount");
    auto meatCount = (Text*)Helper::seekWidgetByName(ui, "MeatCount");
    fighterCount->setString("x" + GM()->getIntToStr(_count[1]));
    bowmanCount->setString("x" + GM()->getIntToStr(_count[2]));
    gunnerCount->setString("x" + GM()->getIntToStr(_count[3]));
    meatCount->setString("x" + GM()->getIntToStr(_count[4]));
}


// 放置士兵
bool BattleHudLayer::updateCount()
{
    if (_select == 0) return false;
    if (_count[_select] <= 0) return false;
    
    auto ui = (Widget*)this->getChildByName("UI");
    Text* label = nullptr;
    
    if (_select == 1)       label = (Text*)Helper::seekWidgetByName(ui, "FighterCount");
    else if(_select == 2)   label = (Text*)Helper::seekWidgetByName(ui, "BowmanCount");
    else if(_select == 3)   label = (Text*)Helper::seekWidgetByName(ui, "GunnerCount");
    else if(_select == 4)   label = (Text*)Helper::seekWidgetByName(ui, "MeatCount");
    
    if (label == nullptr) return false;
    
    _count[_select] = _count[_select] - 1;
    label->setString("x" + GM()->getIntToStr(_count[_select]));
    
    return true;
}


void BattleHudLayer::setMapLayer(Layer* layer)
{
    _mapLayer = (BattleMapLayer*)layer;
}


void BattleHudLayer::selectCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        auto ui = (Widget*)this->getChildByName("UI");
        auto btn = (Button*)sender;
        auto name = btn->getName();
        
        auto btn0 = (Button*)Helper::seekWidgetByName(ui, "Button0");
        auto btn1 = (Button*)Helper::seekWidgetByName(ui, "Button1");
        auto btn2 = (Button*)Helper::seekWidgetByName(ui, "Button2");
        auto btn3 = (Button*)Helper::seekWidgetByName(ui, "Button3");
        auto btn4 = (Button*)Helper::seekWidgetByName(ui, "Button4");
        btn0->setBright(false);
        btn1->setBright(false);
        btn2->setBright(false);
        btn3->setBright(false);
        btn4->setBright(false);
        btn->setBright(true);
        
        if (name == "Button0") _select = 0;
        if (name == "Button1") _select = 1;
        if (name == "Button2") _select = 2;
        if (name == "Button3") _select = 3;
        if (name == "Button4") _select = 4;
        
        _mapLayer->_ai->setSelect(_select);
    }
}

void BattleHudLayer::skillCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        auto btn = (Button*)sender;
        auto name = btn->getName();
        
        BattleScene* scene = (BattleScene*)this->getParent();
        BattleMapLayer* layer = scene->_mapLayer;

        if (!layer->_ai->isHeroEnter()) {
            auto notice = Notice::create("英雄还未登场呢~~~");
            this->getParent()->addChild(notice, 999);
        }

        else {
            // 技能1
            if (name == "Skill1") {
                if (skill1 > 0) {
                    skill1--;
                    if (skill1 == 0) btn->setColor(Color3B::GRAY);
                    layer->_ai->_hero->putSkill(1);
                }
                else {
                    auto notice = Notice::create("无法再释放该技能~~~");
                    this->getParent()->addChild(notice, 999);
                }
            }
            // 技能2
            else {
                if (skill2 > 0) {
                    skill2--;
                    if (skill2 == 0) btn->setColor(Color3B::GRAY);
                    layer->_ai->_hero->putSkill(2);
                }
                else {
                    auto notice = Notice::create("无法再释放该技能~~~");
                    this->getParent()->addChild(notice, 999);
                }
            }
        }
        
    }
}

void BattleHudLayer::retreatCallback(Ref* sender, Widget::TouchEventType type)
{
    if (type == Widget::TouchEventType::ENDED) {
        auto btn = (Button*)sender;
        // 显示战斗失败
        _mapLayer->_ai->gameOver(GAME_OVER_FAILED);
    }
}
