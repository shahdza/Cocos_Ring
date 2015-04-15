#include "GameOverDialog.h"


GameOverDialog* GameOverDialog::create(int state, int c1, int c2, int c3, int c4, int exp)
{
    GameOverDialog *pRet = new(std::nothrow) GameOverDialog();
    if (pRet && pRet->init(state, c1, c2, c3, c4, exp)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool GameOverDialog::init(int state, int c1, int c2, int c3, int c4, int exp)
{
    if ( !Layer::init() ) {
        return false;
    }
    
    _state = state;
    _c1 = c1;
    _c2 = c2;
    _c3 = c3;
    _c4 = c4;
    _exp = exp;
    
    this->setScale(0.0f);
    
    showDialog();
    updateData();
    
    return true;
}


void GameOverDialog::showDialog()
{
    // Action
    auto scale = ScaleTo::create(0.3f, 1.0f);
    auto act = EaseBackOut::create(scale);
    this->runAction(act);

    auto ui = GUIReader::getInstance()->widgetFromJsonFile(UI_DIALOG_GAMEOVER);
    this->addChild(ui, 1, "UI");
    
    // 阴影遮罩
    auto WIN_SIZE = Director::getInstance()->getWinSize();
    auto bg = Sprite::create(IMG_GRAY_BG);
    bg->setScale(WIN_SIZE.width/1000.0, WIN_SIZE.height/1000.0);
    bg->setPosition(WIN_SIZE/2);
    this->addChild(bg, -1);
    bg->setOpacity(128);
    
    
    // 关闭按钮
    auto btnClose = Helper::seekWidgetByName(ui, "BackButton");
    btnClose->addTouchEventListener(CC_CALLBACK_2(GameOverDialog::backCallback, this));
    
    // 界面控制
    if (_state == GAME_OVER_SUCCESS) {
        auto success = Helper::seekWidgetByName(ui, "SuccessImage");
        auto star = Helper::seekWidgetByName(ui, "Star");
        success->setVisible(true);
        star->setVisible(true);
        
        auto act = RotateBy::create(1.0f, 90.0);
        star->runAction(RepeatForever::create(act));
    }
    else {
        auto failed = Helper::seekWidgetByName(ui, "FailedImage");
        failed->setVisible(true);
    }
    
    showInfo();
}


void GameOverDialog::showInfo()
{
    auto ui = (Widget*)this->getChildByName("UI");
    
    int townID = GM()->_townID;
    ValueMap& town = DM()->getTownInfo(townID);
    
    auto goldreward = (Text*)Helper::seekWidgetByName(ui, "GoldReward");
    auto woodreward = (Text*)Helper::seekWidgetByName(ui, "WoodReward");
    auto ringreward = (Text*)Helper::seekWidgetByName(ui, "RingReward");
    auto expReward = (Text*)Helper::seekWidgetByName(ui, "Exp");
    auto fighterCount = (Text*)Helper::seekWidgetByName(ui, "FighterCount");
    auto bowmanCount = (Text*)Helper::seekWidgetByName(ui, "BowmanCount");
    auto gunnerCount = (Text*)Helper::seekWidgetByName(ui, "GunnerCount");
    auto meatCount = (Text*)Helper::seekWidgetByName(ui, "MeatCount");
    
    if (_state == GAME_OVER_SUCCESS) {
        goldreward->setString(town["GoldReward"].asString());
        woodreward->setString(town["WoodReward"].asString());
        ringreward->setString(town["RingReward"].asString());
    }
    else {
        goldreward->setString("0");
        woodreward->setString("0");
        ringreward->setString("0");
    }
    expReward->setString(GM()->getIntToStr(_exp));
    fighterCount->setString(GM()->getIntToStr(_c1));
    bowmanCount->setString(GM()->getIntToStr(_c2));
    gunnerCount->setString(GM()->getIntToStr(_c3));
    meatCount->setString(GM()->getIntToStr(_c4));
}


void GameOverDialog::hideDialog()
{
    // Action
    auto scale = ScaleTo::create(0.3f, 0.0f);
    auto ease = EaseBackIn::create(scale);
    auto func = CallFunc::create(CC_CALLBACK_0(GameOverDialog::removeDialog, this));
    auto act = Sequence::create(ease, func, nullptr);
    this->runAction(act);
}


void GameOverDialog::removeDialog()
{
    this->removeFromParent();
}


void GameOverDialog::backCallback(Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED) {
        auto btn = (Button*)sender;
        btn->setTouchEnabled(false);
        GM()->enterHomeScene();
    }
}


void GameOverDialog::updateData()
{
    // 更新英雄经验
    DM()->updateHeroExp(1, _exp);
    
    // 更新士兵数量
    DM()->updateSoilderCount(SOILDER_TYPE_FIGHTER, -_c1);
    DM()->updateSoilderCount(SOILDER_TYPE_BOWMAN, -_c2);
    DM()->updateSoilderCount(SOILDER_TYPE_GUNNER, -_c3);
    DM()->updateSoilderCount(SOILDER_TYPE_MEAT, -_c4);
    
    // 更新解放城池（战斗胜利）
    // 同时更新金币、木材
    if (_state == GAME_OVER_SUCCESS) {
        
        int townID = GM()->_townID;
        ValueMap& town = DM()->getTownInfo(townID);
        int gold = DM()->getGoldCount();
        int wood = DM()->getWoodCount();
        int goldcapacity = DM()->getGoldCapacity();
        int woodcapacity = DM()->getWoodCapacity();
        
        int goldreward = town["GoldReward"].asInt();
        int woodreward = town["WoodReward"].asInt();
        int ringreward = town["RingReward"].asInt();
        
        DM()->updateGold(GM()->getMin(gold + goldreward, goldcapacity));
        DM()->updateWood(GM()->getMin(wood + woodreward, woodcapacity));
        DM()->updateRing(ringreward);
        DM()->updateTownType(townID, TOWN_TYPE_LIBERATE);
    }
}


