#include "LabDialog.h"


LabDialog::LabDialog() :
fighter(DM()->getSoilder(SOILDER_TYPE_FIGHTER)),
bowman(DM()->getSoilder(SOILDER_TYPE_BOWMAN)),
gunner(DM()->getSoilder(SOILDER_TYPE_GUNNER)),
meat(DM()->getSoilder(SOILDER_TYPE_MEAT)),
labLevel(DM()->getLabLevel()),
gold(DM()->getGoldCount()),
wood(DM()->getWoodCount())
{
}

LabDialog* LabDialog::create()
{
    LabDialog *pRet = new(std::nothrow) LabDialog();
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


bool LabDialog::init()
{
    if ( !Layer::init() ) {
        return false;
    }
    
    this->setScale(0.0f);
    showDialog();

    return true;
}


void LabDialog::showDialog()
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

    auto ui = GUIReader::getInstance()->widgetFromJsonFile(UI_DIALOG_LAB);
    this->addChild(ui, 1, "UI");
    
    // 关闭按钮
    auto btnClose = Helper::seekWidgetByName(ui, "CloseButton");
    btnClose->addTouchEventListener(CC_CALLBACK_2(LabDialog::closeCallback, this));
    
    // 信息按钮
    auto btnFighterInfo = Helper::seekWidgetByName(ui, "FighterInfoButton");
    auto btnBowmanInfo = Helper::seekWidgetByName(ui, "BowmanInfoButton");
    auto btnGunnerInfo = Helper::seekWidgetByName(ui, "GunnerInfoButton");
    auto btnMeatInfo = Helper::seekWidgetByName(ui, "MeatShieldInfoButton");
    btnFighterInfo->addTouchEventListener(CC_CALLBACK_2(LabDialog::infoCallback, this));
    btnBowmanInfo->addTouchEventListener(CC_CALLBACK_2(LabDialog::infoCallback, this));
    btnGunnerInfo->addTouchEventListener(CC_CALLBACK_2(LabDialog::infoCallback, this));
    btnMeatInfo->addTouchEventListener(CC_CALLBACK_2(LabDialog::infoCallback, this));
    
    // 购买按钮
    auto btnFighterUp = Helper::seekWidgetByName(ui, "UpFighterButton");
    auto btnBowmanUp = Helper::seekWidgetByName(ui, "UpBowmanButton");
    auto btnGunnerUp = Helper::seekWidgetByName(ui, "UpGunnerButton");
    auto btnMeatUp = Helper::seekWidgetByName(ui, "UpMeatShieldButton");
    btnFighterUp->addTouchEventListener(CC_CALLBACK_2(LabDialog::upCallback, this));
    btnBowmanUp->addTouchEventListener(CC_CALLBACK_2(LabDialog::upCallback, this));
    btnGunnerUp->addTouchEventListener(CC_CALLBACK_2(LabDialog::upCallback, this));
    btnMeatUp->addTouchEventListener(CC_CALLBACK_2(LabDialog::upCallback, this));
    
    showInfo();
}


void LabDialog::showInfo()
{
    auto ui = (Widget*)this->getChildByName("UI");
    
    // 资源数量
    auto lbgold = (Text*)Helper::seekWidgetByName(ui, "GoldCount");
    auto lbwood = (Text*)Helper::seekWidgetByName(ui, "WoodCount");
    lbgold->setString(GM()->getIntToStr(gold));
    lbwood->setString(GM()->getIntToStr(wood));
    
    // 人类士兵
    auto fighter_level = (Text*)Helper::seekWidgetByName(ui, "FighterLevel");
    auto fighter_goldRequire = (Text*)Helper::seekWidgetByName(ui, "FighterGoldRequire");
    fighter_level->setString(fighter["Level"].asString());
    fighter_goldRequire->setString(fighter["GoldRequire"].asString());

    if (labLevel < 1) {
        auto soilder = Helper::seekWidgetByName(ui, "Soilder_Fighter");
        auto btnInfo = Helper::seekWidgetByName(ui, "FighterInfoButton");
        auto btnUp = Helper::seekWidgetByName(ui, "UpFighterButton");
        auto vec = soilder->getChildren();
        soilder->setColor(Color3B::GRAY);
        for (int i = 0; i < vec.size(); i++) {
            vec.at(i)->setColor(Color3B::GRAY);
        }
        btnInfo->setEnabled(false);
        btnUp->setEnabled(false);
    }
    
    
    // 精灵弓箭手
    auto bowman_level = (Text*)Helper::seekWidgetByName(ui, "BowmanLevel");
    auto bowman_goldRequire = (Text*)Helper::seekWidgetByName(ui, "BowmanGoldRequire");
    bowman_level->setString(bowman["Level"].asString());
    bowman_goldRequire->setString(bowman["GoldRequire"].asString());
    
    if (labLevel < 2) {
        auto soilder = Helper::seekWidgetByName(ui, "Soilder_Bowman");
        auto btnInfo = Helper::seekWidgetByName(ui, "BowmanInfoButton");
        auto btnUp = Helper::seekWidgetByName(ui, "UpBowmanButton");
        auto vec = soilder->getChildren();
        soilder->setColor(Color3B::GRAY);
        for (int i = 0; i < vec.size(); i++) {
            vec.at(i)->setColor(Color3B::GRAY);
        }
        btnInfo->setEnabled(false);
        btnUp->setEnabled(false);
        
        auto no = Helper::seekWidgetByName(ui, "NoBowman");
        no->setColor(Color3B::RED);
        no->setVisible(true);
    }
    
    
    // 矮人炮手
    auto gunner_level = (Text*)Helper::seekWidgetByName(ui, "GunnerLevel");
    auto gunner_goldRequire = (Text*)Helper::seekWidgetByName(ui, "GunnerGoldRequire");
    gunner_level->setString(gunner["Level"].asString());
    gunner_goldRequire->setString(gunner["GoldRequire"].asString());
    
    if (labLevel < 3) {
        auto soilder = Helper::seekWidgetByName(ui, "Soilder_Gunner");
        auto btnInfo = Helper::seekWidgetByName(ui, "GunnerInfoButton");
        auto btnUp = Helper::seekWidgetByName(ui, "UpGunnerButton");
        auto vec = soilder->getChildren();
        soilder->setColor(Color3B::GRAY);
        for (int i = 0; i < vec.size(); i++) {
            vec.at(i)->setColor(Color3B::GRAY);
        }
        btnInfo->setEnabled(false);
        btnUp->setEnabled(false);
        
        auto no = Helper::seekWidgetByName(ui, "NoGunner");
        no->setColor(Color3B::RED);
        no->setVisible(true);
    }
    
    
    // 兽人肉盾
    auto meat_level = (Text*)Helper::seekWidgetByName(ui, "MeatShieldLevel");
    auto meat_goldRequire = (Text*)Helper::seekWidgetByName(ui, "MeatShieldGoldRequire");
    meat_level->setString(meat["Level"].asString());
    meat_goldRequire->setString(meat["GoldRequire"].asString());
    
    if (labLevel < 4) {
        auto soilder = Helper::seekWidgetByName(ui, "Soilder_MeatShield");
        auto btnInfo = Helper::seekWidgetByName(ui, "MeatShieldInfoButton");
        auto btnUp = Helper::seekWidgetByName(ui, "UpMeatShieldButton");
        auto vec = soilder->getChildren();
        soilder->setColor(Color3B::GRAY);
        for (int i = 0; i < vec.size(); i++) {
            vec.at(i)->setColor(Color3B::GRAY);
        }
        btnInfo->setEnabled(false);
        btnUp->setEnabled(false);
        
        auto no = Helper::seekWidgetByName(ui, "NoMeatShield");
        no->setColor(Color3B::RED);
        no->setVisible(true);
    }
}


void LabDialog::hideDialog()
{
    // Action
    auto scale = ScaleTo::create(0.3f, 0.0f);
    auto ease = EaseBackIn::create(scale);
    auto func = CallFunc::create(CC_CALLBACK_0(LabDialog::removeDialog, this));
    auto act = Sequence::create(ease, func, nullptr);
    this->runAction(act);
}


void LabDialog::removeDialog()
{
    this->removeFromParent();
}


void LabDialog::closeCallback(Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED) {
        auto btn = (Button*)sender;
        btn->setTouchEnabled(false);
        hideDialog();
    }
}


void LabDialog::infoCallback(Ref* sender, Widget::TouchEventType type)
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


void LabDialog::upCallback(Ref* sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED) {
        auto ui = (Widget*)this->getChildByName("UI");
        auto btn = (Button*)sender;
        string name = btn->getName();
        
        // 人类士兵1
        if (name == "UpFighterButton") {
            // 检测容量
            if (fighter["LabLevelRequire"].asInt() > labLevel) {
                auto notice = Notice::create("提升研究所等级，可继续进阶士兵");
                this->getParent()->addChild(notice, 999);
            }
            // 检测金币数
            else if(gold < fighter["GoldRequire"].asInt()) {
                auto notice = Notice::create("金币不足");
                this->getParent()->addChild(notice, 999);
            }
            // 跟新数据
            else {
                // 金币数量
                gold -= fighter["GoldRequire"].asInt();
                auto lbgold = (Text*)Helper::seekWidgetByName(ui, "GoldCount");
                lbgold->setString(GM()->getIntToStr(gold));
                // hudLayer的金币数量，更新数据库
                auto homeScene = (HomeScene*)this->getParent();
                auto hudLayer = homeScene->_hudLayer;
                hudLayer->addGold(-fighter["GoldRequire"].asInt());
                
                // 士兵数量
                DM()->updateSoilderLevel(SOILDER_TYPE_FIGHTER);
                
                auto level = (Text*)Helper::seekWidgetByName(ui, "FighterLevel");
                auto goldRequire = (Text*)Helper::seekWidgetByName(ui, "FighterGoldRequire");
                level->setString(fighter["Level"].asString());
                goldRequire->setString(fighter["GoldRequire"].asString());
                
                auto image = (ImageView*)Helper::seekWidgetByName(ui, "FighterLevelImage");
                image->stopAllActions();
                image->setScale(1.0f);
                auto scaleUp = ScaleTo::create(0.1f, 2.0f);
                auto scaleDown = ScaleTo::create(0.1f, 1.0f);
                image->runAction(Sequence::create(scaleUp, scaleDown, nullptr));
            }
        }
        
        // 精灵弓箭手2
        else if(name == "UpBowmanButton") {
            // 检测容量
            if (bowman["LabLevelRequire"].asInt() > labLevel) {
                auto notice = Notice::create("提升研究所等级，可继续进阶士兵");
                this->getParent()->addChild(notice, 999);
            }
            // 检测金币数
            else if(gold < bowman["GoldRequire"].asInt()) {
                auto notice = Notice::create("金币不足");
                this->getParent()->addChild(notice, 999);
            }
            // 跟新数据
            else {
                // 金币数量
                gold -= bowman["GoldRequire"].asInt();
                auto lbgold = (Text*)Helper::seekWidgetByName(ui, "GoldCount");
                lbgold->setString(GM()->getIntToStr(gold));
                // hudLayer的金币数量，更新数据库
                auto homeScene = (HomeScene*)this->getParent();
                auto hudLayer = homeScene->_hudLayer;
                hudLayer->addGold(-bowman["GoldRequire"].asInt());
                
                // 士兵数量
                DM()->updateSoilderLevel(SOILDER_TYPE_BOWMAN);
                
                auto level = (Text*)Helper::seekWidgetByName(ui, "BowmanLevel");
                auto goldRequire = (Text*)Helper::seekWidgetByName(ui, "BowmanGoldRequire");
                level->setString(bowman["Level"].asString());
                goldRequire->setString(bowman["GoldRequire"].asString());
                
                auto image = (ImageView*)Helper::seekWidgetByName(ui, "BowmanLevelImage");
                image->stopAllActions();
                image->setScale(1.0f);
                auto scaleUp = ScaleTo::create(0.15f, 2);
                auto scaleDown = ScaleTo::create(0.15f, 1.0);
                image->runAction(Sequence::create(scaleUp, scaleDown, nullptr));
            }
        }
        
        // 矮人炮手3
        else if(name == "UpGunnerButton") {
            // 检测容量
            if (gunner["LabLevelRequire"].asInt() > labLevel) {
                auto notice = Notice::create("提升研究所等级，可继续进阶士兵");
                this->getParent()->addChild(notice, 999);
            }
            // 检测金币数
            else if(gold < gunner["GoldRequire"].asInt()) {
                auto notice = Notice::create("金币不足");
                this->getParent()->addChild(notice, 999);
            }
            // 跟新数据
            else {
                // 金币数量
                gold -= gunner["GoldRequire"].asInt();
                auto lbgold = (Text*)Helper::seekWidgetByName(ui, "GoldCount");
                lbgold->setString(GM()->getIntToStr(gold));
                // hudLayer的金币数量，更新数据库
                auto homeScene = (HomeScene*)this->getParent();
                auto hudLayer = homeScene->_hudLayer;
                hudLayer->addGold(-gunner["GoldRequire"].asInt());
                
                // 士兵数量
                DM()->updateSoilderLevel(SOILDER_TYPE_GUNNER);
                
                auto level = (Text*)Helper::seekWidgetByName(ui, "GunnerLevel");
                auto goldRequire = (Text*)Helper::seekWidgetByName(ui, "GunnerGoldRequire");
                level->setString(gunner["Level"].asString());
                goldRequire->setString(gunner["GoldRequire"].asString());
                
                auto image = (ImageView*)Helper::seekWidgetByName(ui, "GunnerLevelImage");
                image->stopAllActions();
                image->setScale(1.0f);
                auto scaleUp = ScaleTo::create(0.25f, 1.5);
                auto scaleDown = ScaleTo::create(0.25f, 1.0);
                image->runAction(Sequence::create(scaleUp, scaleDown, nullptr));
            }
        }
        
        // 兽人肉盾4
        else if(name == "UpMeatShieldButton") {
            // 检测容量
            if (meat["LabLevelRequire"].asInt() > labLevel) {
                auto notice = Notice::create("提升研究所等级，可继续进阶士兵");
                this->getParent()->addChild(notice, 999);
            }
            // 检测金币数
            else if(gold < meat["GoldRequire"].asInt()) {
                auto notice = Notice::create("金币不足");
                this->getParent()->addChild(notice, 999);
            }
            // 跟新数据
            else {
                // 金币数量
                gold -= meat["GoldRequire"].asInt();
                auto lbgold = (Text*)Helper::seekWidgetByName(ui, "GoldCount");
                lbgold->setString(GM()->getIntToStr(gold));
                // hudLayer的金币数量，更新数据库
                auto homeScene = (HomeScene*)this->getParent();
                auto hudLayer = homeScene->_hudLayer;
                hudLayer->addGold(-meat["GoldRequire"].asInt());
                
                // 士兵数量
                DM()->updateSoilderLevel(SOILDER_TYPE_MEAT);
                
                auto level = (Text*)Helper::seekWidgetByName(ui, "MeatShieldLevel");
                auto goldRequire = (Text*)Helper::seekWidgetByName(ui, "MeatShieldGoldRequire");
                level->setString(meat["Level"].asString());
                goldRequire->setString(meat["GoldRequire"].asString());
                
                auto image = (ImageView*)Helper::seekWidgetByName(ui, "MeatShieldLevelImage");
                image->stopAllActions();
                image->setScale(1.0f);
                auto scaleUp = ScaleTo::create(0.25f, 1.5);
                auto scaleDown = ScaleTo::create(0.25f, 1.0);
                image->runAction(Sequence::create(scaleUp, scaleDown, nullptr));
            }
        }
    }
}

