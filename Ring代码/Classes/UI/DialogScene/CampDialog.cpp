#include "CampDialog.h"


CampDialog::CampDialog() :
fighter(DM()->getSoilder(SOILDER_TYPE_FIGHTER)),
bowman(DM()->getSoilder(SOILDER_TYPE_BOWMAN)),
gunner(DM()->getSoilder(SOILDER_TYPE_GUNNER)),
meat(DM()->getSoilder(SOILDER_TYPE_MEAT)),
campLevel(DM()->getCampLevel()),
labLevel(DM()->getLabLevel()),
limit(DM()->getSoilderLimit(campLevel)),
gold(DM()->getGoldCount()),
wood(DM()->getWoodCount())
{

}

CampDialog* CampDialog::create()
{
    CampDialog *pRet = new(std::nothrow) CampDialog();
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool CampDialog::init()
{
    if ( !Layer::init() ) {
        return false;
    }
    
    this->setScale(0.0f);
    showDialog();

    return true;
}


void CampDialog::showDialog()
{
    // Action
    auto scale = ScaleTo::create(0.3f, 1.0f);
    auto act = EaseBackOut::create(scale);
    this->runAction(act);
    

    // 阴影遮罩
    auto WIN_SIZE = Director::getInstance()->getWinSize();
    auto bg = Sprite::create(IMG_GRAY_BG);
    bg->setScale(WIN_SIZE.width/1000.0, WIN_SIZE.height/1000.0);
    bg->setPosition(WIN_SIZE/2);
    this->addChild(bg, -1);
    bg->setOpacity(128);

    auto ui = GUIReader::getInstance()->widgetFromJsonFile(UI_DIALOG_CAMP);
    this->addChild(ui, 1, "UI");
    
    // 关闭按钮
    auto btnClose = Helper::seekWidgetByName(ui, "CloseButton");
    btnClose->addTouchEventListener(CC_CALLBACK_2(CampDialog::closeCallback, this));
    
    // 信息按钮
    auto btnFighterInfo = Helper::seekWidgetByName(ui, "FighterInfoButton");
    auto btnBowmanInfo = Helper::seekWidgetByName(ui, "BowmanInfoButton");
    auto btnGunnerInfo = Helper::seekWidgetByName(ui, "GunnerInfoButton");
    auto btnMeatInfo = Helper::seekWidgetByName(ui, "MeatShieldInfoButton");
    btnFighterInfo->addTouchEventListener(CC_CALLBACK_2(CampDialog::infoCallback, this));
    btnBowmanInfo->addTouchEventListener(CC_CALLBACK_2(CampDialog::infoCallback, this));
    btnGunnerInfo->addTouchEventListener(CC_CALLBACK_2(CampDialog::infoCallback, this));
    btnMeatInfo->addTouchEventListener(CC_CALLBACK_2(CampDialog::infoCallback, this));
    
    // 购买按钮
    auto btnFighterBuy = Helper::seekWidgetByName(ui, "BuyFighterButton");
    auto btnBowmanBuy = Helper::seekWidgetByName(ui, "BuyBowmanButton");
    auto btnGunnerBuy = Helper::seekWidgetByName(ui, "BuyGunnerButton");
    auto btnMeatBuy = Helper::seekWidgetByName(ui, "BuyMeatShieldButton");
    btnFighterBuy->addTouchEventListener(CC_CALLBACK_2(CampDialog::buyCallback, this));
    btnBowmanBuy->addTouchEventListener(CC_CALLBACK_2(CampDialog::buyCallback, this));
    btnGunnerBuy->addTouchEventListener(CC_CALLBACK_2(CampDialog::buyCallback, this));
    btnMeatBuy->addTouchEventListener(CC_CALLBACK_2(CampDialog::buyCallback, this));
    
    showInfo();
}


void CampDialog::showInfo()
{
    auto ui = (Widget*)this->getChildByName("UI");
    
    // 资源数量
    auto lbgold = (Text*)Helper::seekWidgetByName(ui, "GoldCount");
    auto lbwood = (Text*)Helper::seekWidgetByName(ui, "WoodCount");
    lbgold->setString(GM()->getIntToStr(gold));
    lbwood->setString(GM()->getIntToStr(wood));
    
    
    // 人类士兵
    if (labLevel < 1) {
        auto soilder = Helper::seekWidgetByName(ui, "Soilder_Fighter");
        auto btnInfo = Helper::seekWidgetByName(ui, "FighterInfoButton");
        auto btnBuy = Helper::seekWidgetByName(ui, "BuyFighterButton");
        auto vec = soilder->getChildren();
        soilder->setColor(Color3B::GRAY);
        for (int i = 0; i < vec.size(); i++) {
            vec.at(i)->setColor(Color3B::GRAY);
        }
        btnInfo->setEnabled(false);
        btnBuy->setEnabled(false);
        
    }
    else {
        auto fighter_level = (Text*)Helper::seekWidgetByName(ui, "FighterLevel");
        auto fighter_count = (Text*)Helper::seekWidgetByName(ui, "FighterCount");
        fighter_level->setString(fighter["Level"].asString());
        fighter_count->setString(fighter["Count"].asString() + "/" + GM()->getIntToStr(limit));
    }
    
    
    // 精灵弓箭手
    if (labLevel < 2) {
        auto soilder = Helper::seekWidgetByName(ui, "Soilder_Bowman");
        auto btnInfo = Helper::seekWidgetByName(ui, "BowmanInfoButton");
        auto btnBuy = Helper::seekWidgetByName(ui, "BuyBowmanButton");
        auto no = Helper::seekWidgetByName(ui, "NoBowman");
        auto vec = soilder->getChildren();
        soilder->setColor(Color3B::GRAY);
        for (int i = 0; i < vec.size(); i++) {
            vec.at(i)->setColor(Color3B::GRAY);
        }
        btnInfo->setEnabled(false);
        btnBuy->setEnabled(false);
        no->setColor(Color3B::RED);
        no->setVisible(true);
    }
    else {
        auto bowman_level = (Text*)Helper::seekWidgetByName(ui, "BowmanLevel");
        auto bowman_count = (Text*)Helper::seekWidgetByName(ui, "BowmanCount");
        bowman_level->setString(bowman["Level"].asString());
        bowman_count->setString(bowman["Count"].asString() + "/" + GM()->getIntToStr(limit));
    }
    
    // 矮人炮手
    if (labLevel < 3) {
        auto soilder = Helper::seekWidgetByName(ui, "Soilder_Gunner");
        auto btnInfo = Helper::seekWidgetByName(ui, "GunnerInfoButton");
        auto btnBuy = Helper::seekWidgetByName(ui, "BuyGunnerButton");
        auto no = Helper::seekWidgetByName(ui, "NoGunner");
        auto vec = soilder->getChildren();
        soilder->setColor(Color3B::GRAY);
        for (int i = 0; i < vec.size(); i++) {
            vec.at(i)->setColor(Color3B::GRAY);
        }
        btnInfo->setEnabled(false);
        btnBuy->setEnabled(false);
        no->setColor(Color3B::RED);
        no->setVisible(true);
        
    }
    else {
        auto gunner_level = (Text*)Helper::seekWidgetByName(ui, "GunnerLevel");
        auto gunner_count = (Text*)Helper::seekWidgetByName(ui, "GunnerCount");
        gunner_level->setString(gunner["Level"].asString());
        gunner_count->setString(gunner["Count"].asString() + "/" + GM()->getIntToStr(limit));
    }
    
    // 兽人肉盾
    if (labLevel < 4) {
        auto soilder = Helper::seekWidgetByName(ui, "Soilder_MeatShield");
        auto btnInfo = Helper::seekWidgetByName(ui, "MeatShieldInfoButton");
        auto btnBuy = Helper::seekWidgetByName(ui, "BuyMeatShieldButton");
        auto no = Helper::seekWidgetByName(ui, "NoMeatShield");
        auto vec = soilder->getChildren();
        soilder->setColor(Color3B::GRAY);
        for (int i = 0; i < vec.size(); i++) {
            vec.at(i)->setColor(Color3B::GRAY);
        }
        btnInfo->setEnabled(false);
        btnBuy->setEnabled(false);
        no->setColor(Color3B::RED);
        no->setVisible(true);
    }
    else {
        auto meat_level = (Text*)Helper::seekWidgetByName(ui, "MeatShieldLevel");
        auto meat_count = (Text*)Helper::seekWidgetByName(ui, "MeatShieldCount");
        meat_level->setString(meat["Level"].asString());
        meat_count->setString(meat["Count"].asString() + "/" + GM()->getIntToStr(limit));
    }
}


void CampDialog::hideDialog()
{
    // Action
    auto scale = ScaleTo::create(0.3f, 0.0f);
    auto ease = EaseBackIn::create(scale);
    auto func = CallFunc::create(CC_CALLBACK_0(CampDialog::removeDialog, this));
    auto act = Sequence::create(ease, func, nullptr);
    this->runAction(act);
}


void CampDialog::removeDialog()
{
    this->removeFromParent();
}


void CampDialog::closeCallback(Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED) {
        auto btn = (Button*)sender;
        btn->setTouchEnabled(false);
        hideDialog();
    }
}


void CampDialog::infoCallback(Ref* sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED) {
        auto btn = (Button*)sender;
        string name = btn->getName();
        
        if (name == "FighterInfoButton") {
            auto dialog = SoilderInfoDialog::create(1);
            this->getParent()->addChild(dialog, 999);
        }
        
        else if(name == "BowmanInfoButton") {
            auto dialog = SoilderInfoDialog::create(2);
            this->getParent()->addChild(dialog, 999);
        }
        
        else if(name == "GunnerInfoButton") {
            auto dialog = SoilderInfoDialog::create(3);
            this->getParent()->addChild(dialog, 999);
        }
        
        else if(name == "MeatShieldInfoButton") {
            auto dialog = SoilderInfoDialog::create(4);
            this->getParent()->addChild(dialog, 999);
        }
    }
}


void CampDialog::buyCallback(Ref* sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED) {
        auto ui = (Widget*)this->getChildByName("UI");
        auto btn = (Button*)sender;
        string name = btn->getName();
        
        
        // 人类士兵1
        if (name == "BuyFighterButton") {
            // 检测容量
            if (fighter["Count"].asInt() >= limit) {
                auto notice = Notice::create("提升兵营等级，可招募更多士兵");
                this->getParent()->addChild(notice, 999);
            }
            // 检测金币数
            else if(gold < 100) {
                auto notice = Notice::create("金币不足");
                this->getParent()->addChild(notice, 999);
            }
            // 跟新数据
            else {
                // 金币数量
                gold -= 100;
                auto lbgold = (Text*)Helper::seekWidgetByName(ui, "GoldCount");
                lbgold->setString(GM()->getIntToStr(gold));
                // hudLayer的金币数量，更新数据库
                auto homeScene = (HomeScene*)this->getParent();
                auto hudLayer = homeScene->_hudLayer;
                hudLayer->addGold(-100);
                
                // 士兵数量
                DM()->updateSoilderCount(SOILDER_TYPE_FIGHTER, 1);
                
                auto count = (Text*)Helper::seekWidgetByName(ui, "FighterCount");
                count->setString(fighter["Count"].asString() + "/" + GM()->getIntToStr(limit));
            }
        }
        
        // 精灵弓箭手2
        else if(name == "BuyBowmanButton") {
            // 检测容量
            if (bowman["Count"].asInt() >= limit) {
                auto notice = Notice::create("提升兵营等级，可招募更多士兵");
                this->getParent()->addChild(notice, 999);
            }
            // 检测金币数
            else if(gold < 200) {
                auto notice = Notice::create("金币不足");
                this->getParent()->addChild(notice, 999);
            }
            // 跟新数据
            else {
                // 金币数量
                gold -= 200;
                auto lbgold = (Text*)Helper::seekWidgetByName(ui, "GoldCount");
                lbgold->setString(GM()->getIntToStr(gold));
                // hudLayer的金币数量，更新数据库
                auto homeScene = (HomeScene*)this->getParent();
                auto hudLayer = homeScene->_hudLayer;
                hudLayer->addGold(-200);
                
                // 士兵数量
                DM()->updateSoilderCount(SOILDER_TYPE_BOWMAN, 1);
                
                auto count = (Text*)Helper::seekWidgetByName(ui, "BowmanCount");
                count->setString(bowman["Count"].asString() + "/" + GM()->getIntToStr(limit));
            }
        }
        
        // 矮人炮手3
        else if(name == "BuyGunnerButton") {
            // 检测容量
            if (gunner["Count"].asInt() >= limit) {
                auto notice = Notice::create("提升兵营等级，可招募更多士兵");
                this->getParent()->addChild(notice, 999);
            }
            // 检测金币数
            else if(gold < 350) {
                auto notice = Notice::create("金币不足");
                this->getParent()->addChild(notice, 999);
            }
            // 跟新数据
            else {
                // 金币数量
                gold -= 350;
                auto lbgold = (Text*)Helper::seekWidgetByName(ui, "GoldCount");
                lbgold->setString(GM()->getIntToStr(gold));
                // hudLayer的金币数量，更新数据库
                auto homeScene = (HomeScene*)this->getParent();
                auto hudLayer = homeScene->_hudLayer;
                hudLayer->addGold(-350);
                
                // 士兵数量
                DM()->updateSoilderCount(SOILDER_TYPE_GUNNER, 1);
                
                auto count = (Text*)Helper::seekWidgetByName(ui, "GunnerCount");
                count->setString(gunner["Count"].asString() + "/" + GM()->getIntToStr(limit));
            }
        }
        
        // 兽人肉盾4
        else if(name == "BuyMeatShieldButton") {
            // 检测容量
            if (meat["Count"].asInt() >= limit) {
                auto notice = Notice::create("提升兵营等级，可招募更多士兵");
                this->getParent()->addChild(notice, 999);
            }
            // 检测金币数
            else if(gold < 500) {
                auto notice = Notice::create("金币不足");
                this->getParent()->addChild(notice, 999);
            }
            // 跟新数据
            else {
                // 金币数量
                gold -= 500;
                auto lbgold = (Text*)Helper::seekWidgetByName(ui, "GoldCount");
                lbgold->setString(GM()->getIntToStr(gold));
                // hudLayer的金币数量，更新数据库
                auto homeScene = (HomeScene*)this->getParent();
                auto hudLayer = homeScene->_hudLayer;
                hudLayer->addGold(-500);
                
                // 士兵数量
                DM()->updateSoilderCount(SOILDER_TYPE_MEAT, 1);
                
                auto count = (Text*)Helper::seekWidgetByName(ui, "MeatShieldCount");
                count->setString(meat["Count"].asString() + "/" + GM()->getIntToStr(limit));
            }
        }
    }
}

