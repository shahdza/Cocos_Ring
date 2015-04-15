#include "Notice.h"


Notice* Notice::create(string text)
{
    Notice *pRet = new(std::nothrow) Notice();
    if (pRet && pRet->init(text)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool Notice::init(string text)
{
    if ( !Node::init() )
    {
        return false;
    }
    
    showUI(text);
    
    return true;
}


void Notice::showUI(string text)
{
    auto WIN_SIZE = Director::getInstance()->getWinSize();
    
    auto label = Label::createWithSystemFont(text, FONT_ARIAL, 24);
    label->setPosition(WIN_SIZE.width/2, WIN_SIZE.height/2);
    label->setOpacity(0);
    label->setColor(Color3B::RED);
    this->addChild(label);
    
    // action
    auto moveUp1 = MoveBy::create(0.25f, Vec2(0, WIN_SIZE.height/6));
    auto moveUp2 = MoveBy::create(0.25f, Vec2(0, WIN_SIZE.height/6));
    auto fadeIn = FadeIn::create(0.25f);
    auto fadeOut = FadeOut::create(0.25f);
    auto delay = DelayTime::create(1.0f);
    auto act1 = Spawn::create(moveUp1, fadeIn, nullptr);
    auto act2 = Spawn::create(moveUp2, fadeOut, nullptr);
    auto func = CallFunc::create(CC_CALLBACK_0(Notice::remove, this));
    label->runAction(Sequence::create(act1, delay, act2, func, nullptr));
}


void Notice::remove()
{
    this->removeFromParent();
}

