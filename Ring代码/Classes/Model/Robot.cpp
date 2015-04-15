#include "Robot.h"


Robot* Robot::create(int type)
{
    Robot *pRet = new(std::nothrow) Robot();
    if (pRet && pRet->init(type)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}


bool Robot::init(int type)
{
    if ( !Sprite::init() ) {
        return false;
    }
    
    _type = type;
    showUI();
    idle();

    return true;
}


void Robot::showUI()
{
    switch (_type) {
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
    
    this->addChild(arm);
    
    _pos = GM()->getSpaceTiled();
    this->setPosition(GM()->getMapPos(_pos));
    this->setLocalZOrder((int)_pos.x + (int)_pos.y);
    
    this->setScale(0.5);
    if (_type == SOILDER_TYPE_FIGHTER) this->setScale(0.8);
}

// 悠闲
void Robot::idle()
{
    arm->getAnimation()->stop();
    
    MoveBy* move = nullptr;
    CallFunc* func = CallFunc::create(CC_CALLBACK_0(Robot::idle, this));
    
    ValueVector vv = GM()->getNextSpace(_pos);
    int n = vv.size();
    
    int x = random(0, n-1);
    for (int i = 0; i < n; i++) {
        if (i == x) {
            ValueMap& map = vv.at(i).asValueMap();
            Vec2 delta = GM()->getMapDelta(map["dir"].asInt());
            move = MoveBy::create(2.0f, delta);
            
            _pos.x = map["x"].asInt();
            _pos.y = map["y"].asInt();
            arm->getAnimation()->play("run" + map["dir"].asString());
            break;
        }
    }
    
    if (move != nullptr) {
        this->runAction(Sequence::create(move, func, nullptr));
        this->setLocalZOrder((int)_pos.x + (int)_pos.y);
    }
}

