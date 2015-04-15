#include "TownDialog.h"


TownDialog* TownDialog::create(TownSprite* town)
{
    TownDialog *pRet = new(std::nothrow) TownDialog();
    if (pRet && pRet->init(town)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool TownDialog::init(TownSprite* town)
{
    if ( !Layer::init() ) {
        return false;
    }
    
    _town = town;
    showDialog();
    addTouch();
    
    return true;
}



void TownDialog::showDialog()
{
    Widget* ui;
    if (_town->_type == TOWN_TYPE_HOME) {
        ui = GUIReader::getInstance()->widgetFromJsonFile(UI_DIALOG_HOME);
        auto btnEnter = (Button*)Helper::seekWidgetByName(ui, "EnterButton");
        btnEnter->addTouchEventListener(CC_CALLBACK_2(TownDialog::btnCallback, this));
    }
    else if(_town->_type == TOWN_TYPE_CHAPTER) {
        ui = GUIReader::getInstance()->widgetFromJsonFile(UI_DIALOG_CHAPTER);
        auto btnSeek = (Button*)Helper::seekWidgetByName(ui, "SeekButton");
        auto btnFight = (Button*)Helper::seekWidgetByName(ui, "FightButton");
        btnSeek->addTouchEventListener(CC_CALLBACK_2(TownDialog::btnCallback, this));
        btnFight->addTouchEventListener(CC_CALLBACK_2(TownDialog::btnCallback, this));
        
        // 加载数据
        auto lbGoldReward = (Text*)Helper::seekWidgetByName(ui, "GoldReward");
        auto lbWoodReward = (Text*)Helper::seekWidgetByName(ui, "WoodReward");
        auto lbRingReward = (Text*)Helper::seekWidgetByName(ui, "RingReward");
        lbGoldReward->setString(GM()->getIntToStr(_town->_goldReward));
        lbWoodReward->setString(GM()->getIntToStr(_town->_woodReward));
        lbRingReward->setString(GM()->getIntToStr(_town->_ringReward));
    }
    else if(_town->_type == TOWN_TYPE_LIBERATE) {
        ui = GUIReader::getInstance()->widgetFromJsonFile(UI_DIALOG_LIBERATE);
        
        // 加载数据
        auto lbGoldProduct = (Text*)Helper::seekWidgetByName(ui, "GoldProduct");
        auto lbWoodProduct = (Text*)Helper::seekWidgetByName(ui, "WoodProduct");
        lbGoldProduct->setString(GM()->getIntToStr(_town->_goldProduct));
        lbWoodProduct->setString(GM()->getIntToStr(_town->_woodProduct));
    }
    
    this->addChild(ui, 1, "UI");
    
    auto size = Director::getInstance()->getWinSize();
    auto image = (ImageView*)Helper::seekWidgetByName(ui, "Image");
    
    // Action
    image->setScale(0.0);
    auto move = MoveTo::create(0.0, Vec2(size.width/2, size.height/3 + image->getContentSize().height/2));
    auto scale = ScaleTo::create(0.2, 1.0);
    image->runAction(scale);
    image->runAction(move);
}


void TownDialog::hideDialog()
{
    auto ui = (Widget*)this->getChildByName("UI");

    // Action
    auto image = (ImageView*)Helper::seekWidgetByName(ui, "Image");
    auto scale = ScaleTo::create(0.2, 0.0);
    auto func = CallFunc::create(CC_CALLBACK_0(TownDialog::removeDialog, this));
    auto seq = Sequence::create(scale, func, nullptr);
    image->runAction(seq);
}


void TownDialog::removeDialog()
{
    this->removeFromParent();
}


void TownDialog::addTouch()
{
    auto dispatcher = this->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(TownDialog::onTouchBegan, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}


bool TownDialog::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    hideDialog();
    return true;
}


void TownDialog::btnCallback(Ref *sender, Widget::TouchEventType type)
{
    if(type == Widget::TouchEventType::ENDED) {
        auto btn = (Button*)sender;
        btn->setTouchEnabled(false);
        auto name = btn->getName();
        if (name == "EnterButton") {
            GM()->enterHomeScene();
        }
        else if(name == "SeekButton") {
            GM()->enterChapterScene(_town->_id, CHAPTER_TYPE_SEEK);
        }
        else if(name == "FightButton") {
            GM()->enterChapterScene(_town->_id, CHAPTER_TYPE_FIGHT);
        }
    }
}

