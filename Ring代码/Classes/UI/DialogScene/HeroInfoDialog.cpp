#include "HeroInfoDialog.h"


HeroInfoDialog* HeroInfoDialog::create(int ID)
{
    HeroInfoDialog *pRet = new(std::nothrow) HeroInfoDialog();
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


bool HeroInfoDialog::init(int ID)
{
    if ( !Layer::init() ) {
        return false;
    }
    
    _id = ID;
    
    this->setScale(0.0f);
    showDialog();
    
    schedule(schedule_selector(HeroInfoDialog::update), 3.0f);
    
    return true;
}


void HeroInfoDialog::showDialog()
{
    // Action
    auto scale = ScaleTo::create(0.3f, 1.0f);
    auto act = EaseBackOut::create(scale);
    this->runAction(act);

    auto ui = GUIReader::getInstance()->widgetFromJsonFile(UI_DIALOG_HEROINFO);
    this->addChild(ui, 1, "UI");
    
    // 关闭按钮
    auto btnClose = Helper::seekWidgetByName(ui, "CloseButton");
    btnClose->addTouchEventListener(CC_CALLBACK_2(HeroInfoDialog::closeCallback, this));
    
    // 属性按钮
    auto btnBase = Helper::seekWidgetByName(ui, "BaseButton");
    btnBase->addTouchEventListener(CC_CALLBACK_2(HeroInfoDialog::baseCallback, this));
    
    // 技能按钮
    auto btnSkill = Helper::seekWidgetByName(ui, "SkillButton");
    btnSkill->addTouchEventListener(CC_CALLBACK_2(HeroInfoDialog::skillCallback, this));
    
    showInfo();
}


void HeroInfoDialog::showInfo()
{
    auto ui = (Widget*)this->getChildByName("UI");
    baseBoard = (ImageView*)Helper::seekWidgetByName(ui, "BaseBoard");
    skillBoard = (ImageView*)Helper::seekWidgetByName(ui, "SkillBoard");
    baseBoard->setVisible(true);
    skillBoard->setVisible(false);
    
    // 获取数据
    ValueMap& map = DM()->getHero(_id);
    ValueMap& BSkill = DM()->getSkillInfo(map["BSkillID"].asInt());
    ValueMap& ZSkill = DM()->getSkillInfo(map["ZSkillID"].asInt());
    ValueMap& ZZSkill = DM()->getSkillInfo(map["ZZSkillID"].asInt());
    
    // 基本属性
    string t = map["Name"].asString() + "(等级" + map["Level"].asString() + ")";
    auto title = (Text*)Helper::seekWidgetByName(ui, "Title");
    auto description = (Text*)Helper::seekWidgetByName(ui, "Description");
    auto healthPoint = (Text*)Helper::seekWidgetByName(ui, "HealthPoint");
    auto damage = (Text*)Helper::seekWidgetByName(ui, "Damage");
    auto atkspeed = (Text*)Helper::seekWidgetByName(ui, "AttackSpeed");
    auto shootrange = (Text*)Helper::seekWidgetByName(ui, "ShootRange");
    auto hpUp = (Text*)Helper::seekWidgetByName(ui, "HealthPointUp");
    auto damageUp = (Text*)Helper::seekWidgetByName(ui, "DamageUp");
    auto exp = (Text*)Helper::seekWidgetByName(ui, "Exp");
    title->setString(t);
    description->setString(map["Description"].asString());
    healthPoint->setString(map["HealthPoint"].asString());
    damage->setString(map["Damage"].asString());
    atkspeed->setString(map["AttackSpeed"].asString());
    shootrange->setString(map["ShootRange"].asString());
    hpUp->setString(map["HealthPointUP"].asString());
    damageUp->setString(map["DamageUP"].asString());
    exp->setString(map["Exp"].asString() + "/" + map["ExpRequire"].asString());
    
    // 技能
    auto bname = (Text*)Helper::seekWidgetByName(ui, "BSkillName");
    auto zname = (Text*)Helper::seekWidgetByName(ui, "ZSkillName");
    auto zzname = (Text*)Helper::seekWidgetByName(ui, "ZZSkillName");
    auto bdescription = (Text*)Helper::seekWidgetByName(ui, "BSkillDescription");
    auto zdescription = (Text*)Helper::seekWidgetByName(ui, "ZSkillDescription");
    auto zzdescription = (Text*)Helper::seekWidgetByName(ui, "ZZSkillDescription");
    bname->setString(BSkill["Name"].asString());
    zname->setString(ZSkill["Name"].asString());
    zzname->setString(ZZSkill["Name"].asString());
    bdescription->setString(BSkill["Description"].asString());
    zdescription->setString(ZSkill["Description"].asString());
    zzdescription->setString(ZZSkill["Description"].asString());
    
    // 技能图片
    auto bimage = Helper::seekWidgetByName(ui, "BImage");
    auto zimage = Helper::seekWidgetByName(ui, "ZImage");
    auto zzimage = Helper::seekWidgetByName(ui, "ZZImage");
    auto image1 = Sprite::create(IMG_SKILL_BSKILL);
    auto image2 = Sprite::create(IMG_SKILL_ZSKILL);
    auto image3 = Sprite::create(IMG_SKILL_ZZSKILL);
    bimage->addChild(image1);
    zimage->addChild(image2);
    zzimage->addChild(image3);
    
    
    // 英雄动画
    auto image = Helper::seekWidgetByName(ui, "Image");
    arm = Armature::create(ANIM_NAME_ARAGORN);
    image->addChild(arm);
    arm->getAnimation()->play("idle0");

}


void HeroInfoDialog::hideDialog()
{
    // Action
    auto scale = ScaleTo::create(0.3f, 0.0f);
    auto ease = EaseBackIn::create(scale);
    auto func = CallFunc::create(CC_CALLBACK_0(HeroInfoDialog::removeDialog, this));
    auto act = Sequence::create(ease, func, nullptr);
    this->runAction(act);
}


void HeroInfoDialog::removeDialog()
{
    this->removeFromParent();
}


void HeroInfoDialog::closeCallback(Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED) {
        auto btn = (Button*)sender;
        btn->setTouchEnabled(false);
        hideDialog();
    }
}

void HeroInfoDialog::baseCallback(Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED) {
        baseBoard->setVisible(true);
        skillBoard->setVisible(false);
    }
}

void HeroInfoDialog::skillCallback(Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED) {
        baseBoard->setVisible(false);
        skillBoard->setVisible(true);
    }
}


void HeroInfoDialog::update(float dt)
{
    int type = cocos2d::random(0, 9);
    int id = cocos2d::random(0, 7);
    
    // run
    if (type <= 3) {
        arm->getAnimation()->play("run" + GM()->getIntToStr(id));
    }
    // atk
    else if(type <= 7) {
        arm->getAnimation()->play("atk" + GM()->getIntToStr(id));
    }
    else {
        arm->getAnimation()->play("idle0");
    }
}



