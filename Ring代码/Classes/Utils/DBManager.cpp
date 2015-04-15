#include "DBManager.h"


DBManager* DBManager::_g = nullptr;
DBManager* DBManager::getInstance()
{
    if (nullptr == _g) {
        _g = new DBManager();
        _g->init();
    }
    return _g;
}

DBManager::DBManager()
{
    
}

DBManager::~DBManager()
{
    _g = nullptr;
}

bool DBManager::init()
{
    return true;
}


bool DBManager::open()
{
    string path = FileUtils::getInstance()->getWritablePath() + "/" + DB_NAME;
    
    int ret = sqlite3_open(path.c_str(), &_pdb);
    if (ret != SQLITE_OK) {
        const char* errmsg = sqlite3_errmsg(_pdb);
        CCLOG("sqlite open error: %s", errmsg);
        sqlite3_close(_pdb);
        return false;
    }
    return true;
}

void DBManager::close()
{
    sqlite3_close(_pdb);
    _pdb = nullptr;
}

// 更新数据库
void DBManager::executeUpdate(std::string sql)
{
    if(open() == true) {
        int ret = sqlite3_exec(_pdb, sql.c_str(), nullptr, nullptr, nullptr);
        if(ret != SQLITE_OK) {
            CCLOG("update data failed!");
        }
        close();
    }
}

// 查询数据库
ValueVector DBManager::executeQuery(std::string sql)
{
    ValueVector v;

    if (open()) {
        char** table;   // 查询结果
        int r, c;       // 行数、列数
        
        sqlite3_get_table(_pdb, sql.c_str(), &table, &r, &c, nullptr);
        
        // 第0行（0 ~ c-1），为字段名
        // 第1~r行（c ~ 2*c-1），第一条记录
        for(int i = 0; i <= r; i++) {
            ValueMap map;
            for(int j = 0; j < c; j++) {
//                CCLOG("%s", table[i * c + j]);
                map[table[j]] = table[i * c + j];
            }
            v.push_back((Value)map);
        }
        
        // 记得释放查询表
        sqlite3_free_table(table);
    }
    
    return v;
}


void DBManager::createTable()
{
    string path = FileUtils::getInstance()->getWritablePath() + "/" + DB_NAME;

    if (!FileUtils::getInstance()->isFileExist(path)) {
        CCLOG("create RingDB.db");
        createPlayerInfo();
        createTownStateInfo();
        createMiwuStateInfo();
        createBuildingListInfo();
        createHeroListInfo();
        createSoilderListInfo();
    }
}


void DBManager::createPlayerInfo()
{
    ValueVector data;
    loadCsvData(CSV_PLAYERINFO, data);
    
    string sql = "create table PlayerInfo(ID integer primary key autoincrement, Name, Level, Exp, RingCount, GoldCount, WoodCount, GoldCapacity, WoodCapacity)";
    executeUpdate(sql);
    
    for (int i = 1; i < data.size(); i++) {
        ValueMap& map = data.at(i).asValueMap();
        sql = "insert into PlayerInfo values("
        + map["ID"].asString() + ", '"
        + map["Name"].asString() + "', '"
        + map["Level"].asString() + "', '"
        + map["Exp"].asString() + "', '"
        + map["RingCount"].asString() + "', '"
        + map["GoldCount"].asString() + "', '"
        + map["WoodCount"].asString() + "', '"
        + map["GoldCapacity"].asString() + "', '"
        + map["WoodCapacity"].asString() + "')";
        
//        CCLOG("sql: %s", sql.c_str());
        executeUpdate(sql);
    }
}

void DBManager::createTownStateInfo()
{
    ValueVector data;
    loadCsvData(CSV_TOWNSTATEINFO, data);
    
    string timeStamp = GM()->getIntToStr(GM()->getTimeStamp());
    string sql = "create table TownStateInfo(TownID integer primary key autoincrement, Type, LastHarvest)";
    executeUpdate(sql);
    
    for (int i = 1; i < data.size(); i++) {
        ValueMap& map = data.at(i).asValueMap();
        sql = "insert into TownStateInfo values("
        + map["TownID"].asString() + ", '"
        + map["Type"].asString() + "', '"
        + timeStamp + "')";
        
//        CCLOG("sql: %s", sql.c_str());
        executeUpdate(sql);
    }
}

void DBManager::createMiwuStateInfo()
{
    ValueVector data;
    loadCsvData(CSV_MIWUSTATEINFO, data);
    
    string timeStamp = GM()->getIntToStr(GM()->getTimeStamp());
    string sql = "create table MiwuStateInfo(MiwuID integer primary key autoincrement, Type)";
    executeUpdate(sql);
    
    for (int i = 1; i < data.size(); i++) {
        ValueMap& map = data.at(i).asValueMap();
        sql = "insert into MiwuStateInfo values("
        + map["MiwuID"].asString() + ", '"
        + map["Type"].asString() + "')";
        
//        CCLOG("sql: %s", sql.c_str());
        executeUpdate(sql);
    }
}

void DBManager::createBuildingListInfo()
{
    ValueVector data;
    loadCsvData(CSV_BUILDINGLISTINFO, data);
    
    string timeStamp = GM()->getIntToStr(GM()->getTimeStamp());
    string sql = "create table BuildingListInfo(ID integer primary key autoincrement, BuildingID, PositionX, PositionY, BuildState, LastBuildTime, LastGoldHarvest, LastWoodHarvest)";
    executeUpdate(sql);
    
    for (int i = 1; i < data.size(); i++) {
        ValueMap& map = data.at(i).asValueMap();
        sql = "insert into BuildingListInfo values("
        + map["ID"].asString() + ", '"
        + map["BuildingID"].asString() + "', '"
        + map["PositionX"].asString() + "', '"
        + map["PositionY"].asString() + "', '"
        + map["BuildState"].asString() + "', '"
        + timeStamp + "', '"
        + timeStamp + "', '"
        + timeStamp + "')";
        
//        CCLOG("sql: %s", sql.c_str());
        executeUpdate(sql);
    }
}

void DBManager::createSoilderListInfo()
{
    ValueVector data;
    loadCsvData(CSV_SOILDER_LISTINFO, data);
    
    string timeStamp = GM()->getIntToStr(GM()->getTimeStamp());
    string sql = "create table SoilderListInfo(ID integer primary key autoincrement, SoilderID, Count)";
    executeUpdate(sql);
    
    for (int i = 1; i < data.size(); i++) {
        ValueMap& map = data.at(i).asValueMap();
        sql = "insert into SoilderListInfo values("
        + map["ID"].asString() + ", '"
        + map["SoilderID"].asString() + "', '"
        + map["Count"].asString() + "')";
        
//        CCLOG("sql: %s", sql.c_str());
        executeUpdate(sql);
    }
}

void DBManager::createHeroListInfo()
{
    ValueVector data;
    loadCsvData(CSV_HERO_LISTINFO, data);
    
    string timeStamp = GM()->getIntToStr(GM()->getTimeStamp());
    string sql = "create table HeroListInfo(ID integer primary key autoincrement, HeroID, Exp, State)";
    executeUpdate(sql);
    
    for (int i = 1; i < data.size(); i++) {
        ValueMap& map = data.at(i).asValueMap();
        sql = "insert into HeroListInfo values("
        + map["ID"].asString() + ", '"
        + map["HeroID"].asString() + "', '"
        + map["Exp"].asString() + "', '"
        + map["State"].asString() + "')";
        
//        CCLOG("sql: %s", sql.c_str());
        executeUpdate(sql);
    }
}


// 加载CSV数据
void DBManager::loadCsvData(std::string file, ValueVector& data)
{
    Csv csv = Csv(file.c_str());
    for (int i = 0; i < csv.getRowCount(); i++) {
        ValueMap map;
        for (int j = 0; j < csv[i].size(); j++) {
            map[csv[0][j]] = csv[i][j];
        }
        data.push_back((Value)map);
    }
}
