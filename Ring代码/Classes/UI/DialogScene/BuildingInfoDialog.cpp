#include "BuildingInfoDialog.h"


BuildingInfoDialog* BuildingInfoDialog::create(BuildingSprite* buildingSprite)
{
    BuildingInfoDialog *pRet = new(std::nothrow) BuildingInfoDialog();
    if (pRet && pRet->init(buildingSprite)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool BuildingInfoDialog::init(BuildingSprite* buildingSprite)
{
    if ( !Layer::init() ) {
        return false;
    }
    
    _buildingSprite = buildingSprite;
    
    this->setScale(0.0f);
    showDialog();
    
    return true;
}


void BuildingInfoDialog::showDialog()
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

    auto ui = GUIReader::getInstance()->widgetFromJsonFile(UI_DIALOG_BUILDING_INFO);
    this->addChild(ui, 1, "UI");
    
    // 关闭按钮
    auto btnClose = Helper::seekWidgetByName(ui, "CloseButton");
    btnClose->addTouchEventListener(CC_CALLBACK_2(BuildingInfoDialog::btnCallback, this));
    
    showInfo();
}


void BuildingInfoDialog::showInfo()
{
    auto ui = (Widget*)this->getChildByName("UI");
    
    string t = _buildingSprite->_name + "(等级" + GM()->getIntToStr(_buildingSprite->_level) + ")";
    auto title = (Text*)Helper::seekWidgetByName(ui, "Title");
    auto description = (Text*)Helper::seekWidgetByName(ui, "Description");
    auto healthPoint = (Text*)Helper::seekWidgetByName(ui, "HealthPoint");
    auto image = (ImageView*)Helper::seekWidgetByName(ui, "BuildingImage");
    
    title->setString(t);
    description->setString(_buildingSprite->_description);
    healthPoint->setString(GM()->getIntToStr(_buildingSprite->_healthPoint));
    image->loadTexture(GM()->getBuildingIMG(_buildingSprite->_type));
    
    switch (_buildingSprite->_type) {
        case BUILDING_TYPE_ArrowTower:
        case BUILDING_TYPE_Cannon:
        case BUILDING_TYPE_Laser: {
            auto lbDamage = (Text*)Helper::seekWidgetByName(ui, "lbDamage");
            auto lbAttackSpeed = (Text*)Helper::seekWidgetByName(ui, "lbAttackSpeed");
            auto lbShootRange = (Text*)Helper::seekWidgetByName(ui, "lbShootRange");
            auto damage = (Text*)Helper::seekWidgetByName(ui, "Damage");
            auto attackSpeed = (Text*)Helper::seekWidgetByName(ui, "AttackSpeed");
            auto shootRange = (Text*)Helper::seekWidgetByName(ui, "ShootRange");
            
            lbDamage->setVisible(true);
            lbAttackSpeed->setVisible(true);
            lbShootRange->setVisible(true);
            damage->setString(GM()->getIntToStr(_buildingSprite->_damage));
            attackSpeed->setString(GM()->getIntToStr(_buildingSprite->_attackSpeed));
            shootRange->setString(GM()->getIntToStr(_buildingSprite->_shootRange));
        }
            break;
        case BUILDING_TYPE_MineFactory: {
            auto lbGoldProduct = (Text*)Helper::seekWidgetByName(ui, "lbGoldProduct");
            auto goldProduct = (Text*)Helper::seekWidgetByName(ui, "GoldProduct");
            
            lbGoldProduct->setVisible(true);
            goldProduct->setString(GM()->getIntToStr(_buildingSprite->_goldProduct));
        }
            break;
        case BUILDING_TYPE_WoodFactory: {
            auto lbWoodProduct = (Text*)Helper::seekWidgetByName(ui, "lbWoodProduct");
            auto WoodProduct = (Text*)Helper::seekWidgetByName(ui, "WoodProduct");
            
            lbWoodProduct->setVisible(true);
            WoodProduct->setString(GM()->getIntToStr(_buildingSprite->_woodProduct));
        }
            break;
        case BUILDING_TYPE_BaseTower: {
            auto lbGoldCapacity = (Text*)Helper::seekWidgetByName(ui, "lbGoldCapacity");
            auto lbWoodCapacity = (Text*)Helper::seekWidgetByName(ui, "lbWoodCapacity");
            auto goldCapacity = (Text*)Helper::seekWidgetByName(ui, "GoldCapacity");
            auto woodCapacity = (Text*)Helper::seekWidgetByName(ui, "WoodCapacity");
            
            lbGoldCapacity->setVisible(true);
            lbWoodCapacity->setVisible(true);
            goldCapacity->setString(GM()->getIntToStr(_buildingSprite->_goldCapacity));
            woodCapacity->setString(GM()->getIntToStr(_buildingSprite->_woodCapacity));
            
            // BuildingLimit
            auto scrollView = (ScrollView*)Helper::seekWidgetByName(ui, "ScrollView");
            auto mineFactory = (Text*)Helper::seekWidgetByName(ui, "MineFactoryLimit");
            auto woodFactory = (Text*)Helper::seekWidgetByName(ui, "WoodFactoryLimit");
            auto arrowTower = (Text*)Helper::seekWidgetByName(ui, "ArrowTowerLimit");
            auto cannon = (Text*)Helper::seekWidgetByName(ui, "CannonLimit");
            auto laser = (Text*)Helper::seekWidgetByName(ui, "LaserLimit");
            
            auto baseLevel = DM()->getBaseTowerLevel();
            auto limitMap = DM()->getBuildingLimit(baseLevel);
        
            scrollView->setVisible(true);
            mineFactory->setString("x" + limitMap["MineFactoryCapacity"].asString());
            woodFactory->setString("x" + limitMap["WoodFactoryCapacity"].asString());
            arrowTower->setString("x" + limitMap["ArrowTowerCapacity"].asString());
            cannon->setString("x" + limitMap["CannonCapacity"].asString());
            laser->setString("x" + limitMap["LaserCapacity"].asString());
        }
            break;
        default:
            break;
    }
}


void BuildingInfoDialog::hideDialog()
{
    // Action
    auto scale = ScaleTo::create(0.3f, 0.0f);
    auto ease = EaseBackIn::create(scale);
    auto func = CallFunc::create(CC_CALLBACK_0(BuildingInfoDialog::removeDialog, this));
    auto act = Sequence::create(ease, func, nullptr);
    this->runAction(act);
}


void BuildingInfoDialog::removeDialog()
{
    this->removeFromParent();
}


void BuildingInfoDialog::btnCallback(Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED) {
        auto btn = (Button*)sender;
        btn->setTouchEnabled(false);
        hideDialog();
    }
}

