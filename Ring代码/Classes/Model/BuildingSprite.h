#ifndef __BuildingSprite_H__
#define __BuildingSprite_H__

#include "Public.h"


class BuildingSprite : public cocos2d::Sprite
{
public:
    virtual bool init(int index);
    static BuildingSprite* create(int index);
    
    void addTouch();
    virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
    virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
    virtual void onTouchEnded(Touch* pTouch, Event* pEvent);
    void detach();

public:
    void loadData(int index);       // 加载数据
    void showUI();                  // 显示UI
    void moveBuilding(Vec2 delta);  // 移动建筑
    void selectedAction();          // 选中动画
    void unselectedAction();        // 去掉选中动画
    void setTiledPos();             // 设置瓦片坐标
    
    void showUpgradePro();          // 显示进度条
    void upgrade();                 // 升级操作
    void upgradeFinished();         // 升级完成
    
    // 木材厂、金矿厂 可收获资源
    void showBubble();
    void harvest();
    void update(float dt);

public:
    // 基础属性
    int _index;                 // 内存中的数组下标
    int _id;                    // 编号
    int _BuildingID;            // 建筑编号ID
    Vec2 _pos;                  // 坐标
    int _buildState;            // 建造状态。1已建成，2正在建造。
    int _lastBuildTime;         // 最后建筑时间。
    int _lastGoldHarvest;       // 金币收获时间。金矿场金币产量
    int _lastWoodHarvest;       // 木材收获时间。木材厂木材产量。
    
    int _type;                  // 类型
    int _level;                 // 等级
    int _healthPoint;           // 生命值
    string _name;               // 建筑名称
    string _description;        // 描述
    
    int _goldRequire;           // 升级所需金币
    int _woodRequire;           // 升级所需木材
    int _timeRequire;           // 升级所需时间
    int _playerLevelRequire;    // 所需玩家等级
    int _baseLevelRequire;      // 升级所需司令部等级
    int _expReward;             // 升级获得玩家经验
    
    // 生产属性
    int _goldProduct;           // 每小时金币产量
    int _woodProduct;           // 每小时木材产量
    
    // 资源属性
    int _goldCapacity;          // 金币容量
    int _woodCapacity;          // 木材容量
    
    // 攻击属性
    bool _isBroken;             // 是否被摧毁
    bool _canAttack;            // 是否为攻击设施
    int _damage;                // 攻击力
    int _attackSpeed;           // 攻击速度
    int _shootRange;            // 射程范围
    int _damageRange;           // 攻击受伤范围
    Node* _attackTarget;        // 攻击目标
    
    // 触摸属性
    bool _canTouched;           // 是否可以移动
    bool _isTouched;            // 是否被触摸
    bool _isSelected;           // 是否被选中
    bool _isShowOpt;            // 是否显示了opt操作
    float _deltaPos;            // 移动偏移
    EventListenerTouchOneByOne* listener;
    
    // 图片
    CCSize _size;       // 尺寸
    Sprite* _normal;    // 正常图片
    Sprite* _broken;    // 毁坏图片
    Sprite* _tip;       // 箭头
    
    HarvestBubble* bubble;
};

#endif // __BuildingSprite_H__
