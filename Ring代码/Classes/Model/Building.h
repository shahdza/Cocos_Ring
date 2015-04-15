#ifndef __Building_H__
#define __Building_H__

#include "Public.h"
#include "BaseSprite.h"


class Building : public BaseSprite
{
public:
    virtual bool init(int index, AIManager* ai);
    static Building* create(int index, AIManager* ai);
    ~Building() { }
    
public:
    void loadData(int index);       // 加载数据
    void showUI();                  // 显示UI
    void addHPBar();                // 添加血条
    
    virtual void atk();
    virtual void hurt(int x);
    virtual bool isDeath();
    
    void update(float dt);
    
public:
    // 基础属性
    int _index;                 // 内存中的数组下标
    int _id;                    // 编号
    int _BuildingID;            // 建筑编号ID
    
    int _type;                  // 类型
    int _healthPoint;           // 生命值
    int _totalHP;               // 总生命值
    
    // 攻击属性
    bool _isBroken;             // 是否被摧毁
    int _canAttack;             // 是否为攻击设施
    int _damage;                // 攻击力
    int _shootRange;            // 射程范围
    int _damageRange;           // 攻击受伤范围
    
    // 图片
    CCSize _size;               // 尺寸
    Sprite* _normal;            // 正常图片
    Sprite* _broken;            // 毁坏图片
    
    LoadingBar* _hpBar;         // 血条
    
    BaseSprite* _target;
    AIManager* _ai;
};

#endif // __Building_H__
