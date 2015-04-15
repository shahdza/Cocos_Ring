#include "SoilderInfoDialog.h"


SoilderInfoDialog* SoilderInfoDialog::create(int ID)
{
    SoilderInfoDialog *pRet = new(std::nothrow) SoilderInfoDialog();
    if (pRet && pRet->init(ID)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool SoilderInfoDialog::init(int ID)
{
    if ( !Layer::init() ) {
        return false;
    }
    
    _id = ID;
    
    this->setScale(0.0f);
    showDialog();
    
    schedule(schedule_selector(SoilderInfoDialog::update), 3.0f);
    
    return true;
}


void SoilderInfoDialog::showDialog()
{
    // Action
    auto scale = ScaleTo::create(0.3f, 1.0f);
    auto act = EaseBackOut::create(scale);
    this->runAction(act);

    auto ui = GUIReader::getInstance()->widgetFromJsonFile(UI_DIALOG_SOILDER_INFO);
    this->addChild(ui, 1, "UI");
    
    // 关闭按钮
    auto btnClose = Helper::seekWidgetByName(ui, "CloseButton");
    btnClose->addTouchEventListener(CC_CALLBACK_2(SoilderInfoDialog::btnCallback, this));
    
    showInfo();
}


void SoilderInfoDialog::showInfo()
{
    auto ui = (Widget*)this->getChildByName("UI");
    ValueMap& map = DM()->getSoilder(_id);
    
    string t = map["Name"].asString() + "(等级" + map["Level"].asString() + ")";
    auto title = (Text*)Helper::seekWidgetByName(ui, "Title");
    auto description = (Text*)Helper::seekWidgetByName(ui, "Description");
    auto healthPoint = (Text*)Helper::seekWidgetByName(ui, "HealthPoint");
    auto damage = (Text*)Helper::seekWidgetByName(ui, "Damage");
    auto atkspeed = (Text*)Helper::seekWidgetByName(ui, "AttackSpeed");
    auto shootrange = (Text*)Helper::seekWidgetByName(ui, "ShootRange");
    title->setString(t);
    description->setString(map["Description"].asString());
    healthPoint->setString(map["HealthPoint"].asString());
    damage->setString(map["Damage"].asString());
    atkspeed->setString(map["AttackSpeed"].asString());
    shootrange->setString(map["ShootRange"].asString());

    // 士兵动画
    switch (_id) {
        case SOILDER_TYPE_FIGHTER: {
            arm = Armature::create(ANIM_NAME_FIGHTER);
        }
            break;
        case SOILDER_TYPE_BOWMAN: {
            arm = Armature::create(ANIM_NAME_BOWMAN);
        }
            break;
        case SOILDER_TYPE_GUNNER: {
            arm = Armature::create(ANIM_NAME_GUNNER);
        }
            break;
        case SOILDER_TYPE_MEAT: {
            arm = Armature::create(ANIM_NAME_MEATSHIELD);
        }
            break;
        default:
            break;
    }
    
    arm->setPosition(Vec2(250, 300));
    arm->setScale(2.0f);
    ui->addChild(arm);
    
    arm->getAnimation()->play("run1");
}


void SoilderInfoDialog::hideDialog()
{
    // Action
    auto scale = ScaleTo::create(0.3f, 0.0f);
    auto ease = EaseBackIn::create(scale);
    auto func = CallFunc::create(CC_CALLBACK_0(SoilderInfoDialog::removeDialog, this));
    auto act = Sequence::create(ease, func, nullptr);
    this->runAction(act);
}


void SoilderInfoDialog::removeDialog()
{
    this->removeFromParent();
}


void SoilderInfoDialog::btnCallback(Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED) {
        auto btn = (Button*)sender;
        btn->setTouchEnabled(false);
        hideDialog();
    }
}


void SoilderInfoDialog::update(float dt)
{
    
    int type = cocos2d::random(0, 1);
    int id = cocos2d::random(0, 7);
    
    // run
    if (type == 0) {
        arm->getAnimation()->play("run" + GM()->getIntToStr(id));
    }
    // atk
    else {
        arm->getAnimation()->play("atk" + GM()->getIntToStr(id));
    }
}



