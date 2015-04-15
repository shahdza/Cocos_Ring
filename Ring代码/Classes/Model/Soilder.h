#ifndef __Soilder_H__
#define __Soilder_H__

#include "Public.h"
#include "BaseSprite.h"

class Soilder : public BaseSprite
{
public:
    virtual bool init(int soilderID, Vec2 pos, AIManager* ai);
    static Soilder* create(int soilderID, Vec2 pos, AIManager* ai);

public:
    void loadData();    // 加载数据
    void showUI();      // 显示UI
    void addHPBar();    // 加血条

    virtual void run();         // 走路
    virtual void atk();         // 攻击
    virtual void hurt(int x);   // 受伤
    virtual bool isDeath();     // 是否死亡
    
    void update(float dt);
    
public:
    int _soilderID;
    int _type;
    int _level;
    int _name;
    
    int _healthPoint;
    int _totalHP;
    int _damage;
    int _attackSpeed;
    int _shootRange;
    
    bool _isbroken;
    int _dir;
    Armature* arm;
    LoadingBar* _hpBar;         // 血条
    
    
    AIManager* _ai;
    BaseSprite* _target;
};

#endif // __Soilder_H__
