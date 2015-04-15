#include "AIManager.h"


bool AIManager::init()
{
    if ( !Node::init() )
    {
        return false;
    }
    
    _mapLayer = nullptr;
    _hudLayer = nullptr;
    _hero = nullptr;
    
    return true;
}


void AIManager::setHudLayer(BattleHudLayer* hudLayer)
{
    _hudLayer = hudLayer;
}

void AIManager::setMapLayer(BattleMapLayer* mapLayer)
{
    _mapLayer = mapLayer;
}


void AIManager::setSelect(int select)
{
    if (_hero == nullptr) return;
    
    if (select == 0) {
        _hero->setSelect(true);
    }
    else {
        _hero->setSelect(false);
    }
}

// pos点是空地，还是建筑
BaseSprite* AIManager::getTarget(Vec2 pos)
{
    Vec2 p = GM()->getMapPos(pos);
    for (int i = 0; i < _buildings.size(); i++) {
        Building* b = _buildings.at(i);
        // 是否触摸到建筑
        Vec2 centerPoint = GM()->getMapPos(b->_pos);
        CCSize size = CCSize(b->_normal->getContentSize());
        if (GM()->isPointInRect(centerPoint, size, p) ) {
            return b;
        }
    }
    return nullptr;
}


BaseSprite* AIManager::getTargetEnemy(Vec2 pos)
{
    Building* target = nullptr;
    int mindis = INF;
    for (int i = 0; i < _buildings.size(); i++) {
        Building* b = _buildings.at(i);
        if (b->isDeath() == true) continue;
        
        int dis = GM()->getManhadun(pos, b->_pos);
        if (dis < mindis) {
            mindis = dis;
            target = b;
        }
    }
    return target;
}

BaseSprite* AIManager::getTargetFriend(Vec2 pos, int range)
{
    for (int i = 0; i < _soilders.size(); i++) {
        Soilder* target = _soilders.at(i);
        if (target->isDeath() == true) continue;
        if (isWithinShootRange(target->_pos, pos, range)) return target;
    }
    if (_hero != nullptr) {
        if (isWithinShootRange(_hero->_pos, pos, range)) {
            return _hero;
        }
    }
    return nullptr;
}


bool AIManager::isWithinShootRange(cocos2d::Vec2 src, cocos2d::Vec2 des, int range)
{
    Vec2 p1 = GM()->getMapPos(src);
    Vec2 p2 = GM()->getMapPos(des);
    int dis = (int)GM()->getDistance(p1, p2);
    return dis <= range;
}


Vec2 AIManager::getNextPos(Vec2 src, Vec2 des, bool isHero)
{
    Vec2 pos = src;
    int mindis = INF;
    for (int i = 0; i < 9; i++) {
        int x = src.x + DX[i] + EPS;
        int y = src.y + DY[i] + EPS;
        if (x < 0 || x > TILED_TOTAL_X || y < 0 || y > TILED_TOTAL_Y) continue;
        if (isHero && GM()->isCovered(Vec2(x, y))) continue;
        int dis = GM()->getManhadun(Vec2(x, y), des);
        if (dis < mindis) {
            mindis = dis;
            pos = Vec2(DX[i], DY[i]);
        }
    }
    return pos;
}

// 游戏结束
void AIManager::gameOver(int state)
{
    int c1 = 0, c2 = 0,  c3 = 0, c4 = 0;
    int exp = 0;
    
    for (int i = 0; i < _buildings.size(); i++) {
        Building* b = _buildings.at(i);
        b->unscheduleAllCallbacks();
    }
    
    for (int i = 0; i < _soilders.size(); i++) {
        Soilder* s = _soilders.at(i);
        s->unscheduleAllCallbacks();
        s->arm->getAnimation()->stop();
        if (s->_isbroken) {
            if (s->_type == 1) c1++;
            if (s->_type == 2) c2++;
            if (s->_type == 3) c3++;
            if (s->_type == 4) c4++;
        }
    }
    
    if (_hero != nullptr) {
        _hero->unscheduleAllCallbacks();
        _hero->idle();
        exp = (int)_hero->_expReward;
    }
    
    // 显示gameover对话框
    auto gameover = GameOverDialog::create(state, c1, c2, c3, c4, exp);
    auto maplayer = (BattleMapLayer*)this->getParent();
    maplayer->getParent()->addChild(gameover, 99);
}

