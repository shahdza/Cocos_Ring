#include "BaseSprite.h"


bool BaseSprite::init()
{
    if ( !Sprite::init() ) {
        return false;
    }
    
    return true;
}

void BaseSprite::atk() { CCLOG("Base atk"); }
void BaseSprite::run() { CCLOG("Base run"); }
void BaseSprite::hurt(int x) { CCLOG("Base hurt"); }
void BaseSprite::idle() { CCLOG("Base idle"); }
bool BaseSprite::isDeath() {  CCLOG("Base isDeath"); return false; }

