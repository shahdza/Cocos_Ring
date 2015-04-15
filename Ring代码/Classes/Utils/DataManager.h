#ifndef __DataManager_H__
#define __DataManager_H__

#include "Public.h"

#define DM() DataManager::getInstance()


class DataManager : public cocos2d::Ref
{
public:
    DataManager();
    virtual ~DataManager();
    virtual bool init();
    static DataManager* getInstance();
    
//--------------------------------------------------------------------------------
// load
//--------------------------------------------------------------------------------
    void loadPlayerInfo();          // 加载玩家信息
    
    void loadPlayerLevelInfo();     // 加载等级信息
    void loadTownInfo();            // 加载城池信息
    void loadMiwuInfo();            // 加载迷雾信息
    
    void loadBuildingInfo();        // 加载建筑信息
    void loadBuildingLimitInfo();   // 加载建筑限制表信息：司令部等级对应建筑数量限制
    
    void loadSoilderInfo();         // 加载士兵信息
    void loadSoilderLimitInfo();    // 加载兵营士兵数量限制表
    
    void loadHeroInfo();            // 加载英雄信息
    void loadSkillInfo();           // 加载技能信息
    
    void loadBattleInfo();          // 加载关卡信息
    
    void loadCsvData(std::string file, ValueVector& data);
    void bindingIndex(ValueVector& data, map<string, int>& index, string ID);
    void printData(ValueVector& data);
    
//--------------------------------------------------------------------------------
// update
//--------------------------------------------------------------------------------
    void updatePlayerExp(int exp);
    void updateGold(int gold);
    void updateWood(int wood);
    void updateGoldCapacity(int capacity);
    void updateWoodCapacity(int capacity);
    void updateRing(int addRing);
    
    
    void updateTownType(int townID, int type);
    void updateTownHarvest(int townID, int lastHarvest);
    
    void updateMiwuType(int level);
    
    void updateBuildingPos(int ID, Vec2 pos);           // 改变坐标
    void updateBuildingBuildState(int ID, int state);   // 改变建造状态
    void updateBuildingLevel(int ID);                   // 改变建筑等级
    void updateLastGoldHarvest(int ID, int lastHarvest);// 金矿
    void updateLastWoodHarvest(int ID, int lastHarvest);// 木材
    int addNewBuilding(int type, Vec2 pos);             // 新建建筑
    
    // 士兵
    void updateSoilderCount(int ID, int delta);         // 更新士兵数量，+delta
    void updateSoilderLevel(int ID);                    // 提升士兵等级
    
    // 英雄
    void updateHeroExp(int ID, int addExp);             // 更新英雄经验值并升级
    void updateHeroLevel(int ID);                       // 提升英雄等级
    

//--------------------------------------------------------------------------------
// get
//--------------------------------------------------------------------------------
    int getPlayerExpRequire(int level);
    int getPlayerLevel();   // 获取玩家等级
    int getGoldCount();     // 获取金币资源数量
    int getWoodCount();     // 获取木材资源数量
    int getGoldCapacity();  // 获取金币资源容量
    int getWoodCapacity();  // 获取木材资源容量
    
    // 城池
    ValueMap& getTownInfo(int townID);  // 获取城池信息

    // 设施
    ValueMap& getBuilding(int ID);                  // 根据列表ID获取建筑信息
    ValueMap& getBuildingInfo(int buildingID);      // 根据BuildingID，获取建筑信息
    ValueMap& getBuildingLimit(int level);          // 根据司令部等级，获取建筑限制
    ValueMap& getBuildingNextInfo(int buildingID);  // 获取设施下一等级信息
    int getBaseTowerLevel();                        // 获取司令部等级
    int getBuildingCountForType(int type);          // 获取某个type的建筑数量
    
    // 士兵
    ValueMap& getSoilder(int ID);               // 根据列表ID，获取士兵
    ValueMap& getSoilderInfo(int soilderID);    // 根据SoilderID，获取士兵信息
    ValueMap& getSoilderNextInfo(int soilderID);// 获取士兵下一等级信息
    int getSoilderLimit(int level);             // 获取兵营数量限制
    int getCampLevel();                         // 获取兵营等级
    int getLabLevel();                          // 获取研究所等级
    
    // 英雄
    ValueMap& getHero(int ID);                  // 根据英雄ID，获取玩家英雄信息
    ValueMap& getHeroInfo(int heroID);          // 根据HeroID，获取英雄信息
    ValueMap& getHeroNextInfo(int heroID);      // 获取英雄下一等级信息
    ValueMap& getSkillInfo(int skillID);        // 获取技能信息
    
    // 关卡信息
    ValueVector getBattleBuilding(int townID); // 获取关卡townID的设施信息
    
public:

    // ValueMap <string, Value<stirng, string> >
    ValueVector _player;        // 玩家信息
    ValueVector _playerLevel;   // 玩家等级经验
    
    ValueVector _town;          // 城池信息
    ValueVector _miwu;          // 迷雾信息

    int _baseID;                // 司令部的ID，数组下标
    int _campID;                // 兵营的ID，数组下标
    int _labID;                 // 研究所ID，数组下标
    ValueVector _buildingInfo;  // 所有建筑信息
    ValueVector _building;      // 玩家建筑信息
    ValueVector _buildingLimit; // 建筑限制表
    
    ValueVector _soilderInfo;   // 所有士兵信息
    ValueVector _soilder;       // 玩家士兵信息
    ValueVector _soilderLimit;  // 士兵数量限制表
    
    ValueVector _heroInfo;      // 所有英雄信息
    ValueVector _hero;          // 英雄信息
    ValueVector _skillInfo;     // 所有技能信息

    
    ValueVector _battleBuilding; // 关卡设施

    
    // 关联Vector下标和数据ID
    map<string, int> _indexPlayerLevel;     // Level与下标
    map<string, int> _indexTown;            // TownID与下标
    map<string, int> _indexMiwu;            // MiwuID与下标
    
    map<string, int> _indexBuilding;        // ID与下标
    map<string, int> _indexBuildingInfo;    // BuildingID与下标
    map<string, int> _indexBuildingLimit;   // 司令部Level与下标
    
    map<string, int> _indexSoilder;         // ID与下标
    map<string, int> _indexSoilderInfo;     // SoilderID与下标
    map<string, int> _indexSoilderLimit;    // 兵营Level与下标
    
    map<string, int> _indexHero;            // ID与下标
    map<string, int> _indexHeroInfo;        // HeroID与下标
    map<string, int> _indexSkillInfo;       // SkillID与下标

private:
    static DataManager* _g;
};

#endif // __DataManager_H__

