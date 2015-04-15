#ifndef __GlobalManager_H__
#define __GlobalManager_H__

#include "Public.h"

#define GM() GlobalManager::getInstance()


class GlobalManager : public cocos2d::Ref
{
public:
    GlobalManager();
    virtual ~GlobalManager();
    virtual bool init();
    static GlobalManager* getInstance();

//--------------------------------------------------------------------------------
// get
//--------------------------------------------------------------------------------
    inline int getMin(int x, int y) { return (x < y) ? x : y; }
    inline int getMax(int x, int y) { return (x > y) ? x : y; }
    
    // 区域检测
    float xmult(Vec2 p1, Vec2 p2, Vec2 p0);  // 叉乘
    bool isPointInCircle(Vec2 centerPoint, float radius, Vec2 p);   // 点是否在圆形内
    bool isPointInDiamond(Vec2 centerPoint, CCSize size, Vec2 p);   // 点是否在菱形内
    bool isPointInRect(Vec2 centerPoint, CCSize size, Vec2 p);      // 点是否在矩形内
    
    string getIntToStr(int value);          // int转string
    int getStrToInt(string value);          // string转int
    float getDistance(Vec2 p1, Vec2 p2);    // 两点距离
    int getManhadun(Vec2 p1, Vec2 p2);      // 曼哈顿距离
    int getTimeStamp();                     // 获取时间戳
    
    // 瓦片坐标
    Vec2 getMapPos(Vec2 pos);               // 地图坐标
    Vec2 getTiledPos(Vec2 pos);             // 瓦片坐标
    bool isOutMap(Vec2 pos);                // 瓦片越界
    void setCoverd(Vec2 pos, int delta);    // 占据/释放地面
    bool isCovered(Vec2 pos);               // 地面是否被占据
    void clearCovered();                    // 清空占地情况
    Vec2 getSpaceTiled();                   // 获取空地
    ValueVector getNextSpace(Vec2 pos);     // 随机获取当前位置周围的空地
    
    int getDir(Vec2 src, Vec2 des);         // 通过两点，获取方向
    int getDir(Vec2 delta);                 // 通过向量方向，获取方向
    Vec2 getMapDelta(int idr);              // 根据瓦片坐标的偏移方向，获取地图坐标的偏移量
    
    // 战斗相关
    int getBattleTownID();  // 获取要进攻的城池ID
    
    // 建筑图片
    string getBuildingIMG(int type);        // 获取建筑的图片名
    string getBuildingBrokenIMG(int type);  // 获取建筑被摧毁后的图片名
    
    // 场景切换
    void enterWorldScene();
    void enterHomeScene();
    void enterChapterScene(int townID, int type);

public:
    int _cover[40][40]; // 占地情况

    bool _newBuild;
    NewBuilding* _build;
    
    int _townID;
    
private:
    static GlobalManager* _g;
};

#endif // __GlobalManager_H__
