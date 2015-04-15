#include "HeroHotelDialog.h"


HeroHotelDialog* HeroHotelDialog::create()
{
    HeroHotelDialog *pRet = new(std::nothrow) HeroHotelDialog();
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


bool HeroHotelDialog::init()
{
    if ( !Layer::init() ) {
        return false;
    }
    
    this->setScale(0.0f);
    showDialog();

    return true;
}


void HeroHotelDialog::showDialog()
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

    auto ui = GUIReader::getInstance()->widgetFromJsonFile(UI_DIALOG_HEROHOTEL);
    this->addChild(ui, 1, "UI");
    
    // 关闭按钮
    auto btnClose = Helper::seekWidgetByName(ui, "CloseButton");
    btnClose->addTouchEventListener(CC_CALLBACK_2(HeroHotelDialog::closeCallback, this));
    
    // 信息按钮
    auto btnInfo = Helper::seekWidgetByName(ui, "AragornInfoButton");
    btnInfo->addTouchEventListener(CC_CALLBACK_2(HeroHotelDialog::infoCallback, this));
    
    // 参战按钮
    auto btnBattle = Helper::seekWidgetByName(ui, "AragornButton");
    btnBattle->addTouchEventListener(CC_CALLBACK_2(HeroHotelDialog::battleCallback, this));
    
    showInfo();
}


void HeroHotelDialog::showInfo()
{
    auto ui = (Widget*)this->getChildByName("UI");
    
    // 获取英雄信息
    ValueMap& map = DM()->getHero(1);
    
    auto lbLevel = (Text*)Helper::seekWidgetByName(ui, "AragornLevel");
    lbLevel->setString(map["Level"].asString());
    
}


void HeroHotelDialog::hideDialog()
{
    // Action
    auto scale = ScaleTo::create(0.3f, 0.0f);
    auto ease = EaseBackIn::create(scale);
    auto func = CallFunc::create(CC_CALLBACK_0(HeroHotelDialog::removeDialog, this));
    auto act = Sequence::create(ease, func, nullptr);
    this->runAction(act);
}


void HeroHotelDialog::removeDialog()
{
    this->removeFromParent();
}


void HeroHotelDialog::closeCallback(Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED) {
        hideDialog();
    }
}


// 显示英雄信息
void HeroHotelDialog::infoCallback(Ref* sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED) {
        auto dialog = HeroInfoDialog::create(HERO_TYPE_ARAGORN);
        this->getParent()->addChild(dialog, 999);
    }
}

// 让英雄参战
void HeroHotelDialog::battleCallback(Ref* sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED) {
        auto notice = Notice::create("该英雄已进入参战状态~~~");
        this->getParent()->addChild(notice, 999);
        
        DM()->updateHeroExp(1, 100);
    }
}

