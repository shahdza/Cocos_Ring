#ifndef __Hero_H__
#define __Hero_H__

#include "Public.h"
#include "BaseSprite.h"


static const int STATE_IDLE     = 0;
static const int STATE_RUN      = 1;
static const int STATE_ATK      = 2;
static const int STATE_SKILL    = 3;
static const int STATE_DEATH    = 4;

class Hero : public BaseSprite
{
public:
    virtual bool init(int ID, Vec2 pos);
    static Hero* create(int ID, Vec2 pos);

public:
    void loadData();    // 加载数据
    void showUI();      // 显示UI
    void addHPBar();    // 加血条
    
    void setSelect(bool select);

    virtual void idle();
    virtual void atk(BaseSprite* target);   // 攻击
    virtual void hurt(int x);           // 受伤
    virtual bool isDeath();             // 是否死亡
    virtual void putSkill(int type);    // 释放技能
    virtual void finishSkill(Armature* arm, int state); // 技能结束
    
    void update(float dt);
    
    void addTouch();
    virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
    virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch, Event* pEvent);
    
public:
    int _id;
    int _heroID;
    int _type;
    int _level;
    int _name;
    
    int _healthPoint;
    int _totalHP;
    int _damage;
    int _attackSpeed;
    int _shootRange;
    
    float _delta;
    LoadingBar* _hpBar; // 血条
    
    bool _isSelect;
    bool _isbroken;
    int _dir;
    Armature* _arm;
    Armature* _skill1;
    Armature* _skill2;
    
    int _state;         // 状态
    Vec2 _targetPos;
    BaseSprite* _target;
    
    float _expReward;
};

#endif // __Hero_H__
