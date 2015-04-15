#ifndef __Public_H__
#define __Public_H__

// cocos2d
#include "cocos2d.h"
using namespace cocos2d;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace cocostudio;
using namespace cocos2d::ui;

// Helper
#include "sqlite3.h"
#include "CSVParser.h"
using namespace CSVParser;


// class
// Manager
class ActManager;
class DataManager;
class DBManager;
class GlobalManager;

// Model
class Notice;
class BuildProcess;
class HarvestBubble;
class TownSprite;
class MiwuSprite;
class BuildingSprite;
class NewBuilding;
class BulletSprite;
class Robot;
class Building;
class Soilder;
class Hero;

// PanZoomLayer
class PanZoomLayer;
// HelloScene
class HelloScene;
// WorldScene
class WorldScene;
class WorldMapLayer;
class WorldHudLayer;
// HomeScene
class HomeScene;
class HomeMapLayer;
class HomeHudLayer;
class HomeOptLayer;
// ChapterScene
class BattleScene;
class BattleMapLayer;
class BattleHudLayer;
class AIManager;

// Dialog
class TownDialog;
class BuildingInfoDialog;
class BuildingUpgradeDialog;
class NewBuildDialog;
class SoilderInfoDialog;
class CampDialog;
class LabDialog;
class HeroInfoDialog;
class HeroHotelDialog;
class GameOverDialog;


// Manager
#include "Config.h"
#include "DataManager.h"
#include "DBManager.h"
#include "GlobalManager.h"

// Model
#include "Notice.h"
#include "BuildProcess.h"
#include "HarvestBubble.h"
#include "TownSprite.h"
#include "MiwuSprite.h"
#include "BuildingSprite.h"
#include "NewBuilding.h"
#include "BulletSprite.h"
#include "Robot.h"
#include "Building.h"
#include "Soilder.h"
#include "Hero.h"

// PanZoomLayer
#include "PanZoomLayer.h"
// HelloScene
#include "HelloScene.h"
// WorldScene
#include "WorldScene.h"
#include "WorldMapLayer.h"
#include "WorldHudLayer.h"
// HomeScene
#include "HomeScene.h"
#include "HomeMapLayer.h"
#include "HomeHudLayer.h"
#include "HomeOptLayer.h"
// BattleScene
#include "BattleScene.h"
#include "BattleMapLayer.h"
#include "BattleHudLayer.h"
#include "AIManager.h"


// Dialog
#include "TownDialog.h"
#include "BuildingInfoDialog.h"
#include "BuildingUpgradeDialog.h"
#include "NewBuildDialog.h"
#include "SoilderInfoDialog.h"
#include "CampDialog.h"
#include "LabDialog.h"
#include "HeroInfoDialog.h"
#include "HeroHotelDialog.h"
#include "GameOverDialog.h"


#endif // __Public_H__
