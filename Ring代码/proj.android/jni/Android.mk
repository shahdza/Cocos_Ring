LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)



LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/Helper/CSVParser/CSVParser.cpp \
                   ../../Classes/Helper/Sqlite3/sqlite3.c \
                   ../../Classes/Model/BaseSprite.cpp \
                   ../../Classes/Model/Building.cpp \
                   ../../Classes/Model/BuildingSprite.cpp \
                   ../../Classes/Model/BuildProcess.cpp \
                   ../../Classes/Model/BulletSprite.cpp \
                   ../../Classes/Model/HarvestBubble.cpp \
                   ../../Classes/Model/Hero.cpp \
                   ../../Classes/Model/MiwuSprite.cpp \
                   ../../Classes/Model/NewBuilding.cpp \
                   ../../Classes/Model/Notice.cpp \
                   ../../Classes/Model/Robot.cpp \
                   ../../Classes/Model/Soilder.cpp \
                   ../../Classes/Model/TownSprite.cpp \
                   ../../Classes/UI/DialogScene/BuildingInfoDialog.cpp \
                   ../../Classes/UI/DialogScene/BuildingUpgradeDialog.cpp \
                   ../../Classes/UI/DialogScene/CampDialog.cpp \
                   ../../Classes/UI/DialogScene/GameOverDialog.cpp \
                   ../../Classes/UI/DialogScene/HeroHotelDialog.cpp \
                   ../../Classes/UI/DialogScene/HeroInfoDialog.cpp \
                   ../../Classes/UI/DialogScene/LabDialog.cpp \
                   ../../Classes/UI/DialogScene/NewBuildDialog.cpp \
                   ../../Classes/UI/DialogScene/SoilderInfoDialog.cpp \
                   ../../Classes/UI/DialogScene/TownDialog.cpp \
                   ../../Classes/UI/HelloScene/HelloScene.cpp \
                   ../../Classes/UI/HomeScene/HomeHudLayer.cpp \
                   ../../Classes/UI/HomeScene/HomeMapLayer.cpp \
                   ../../Classes/UI/HomeScene/HomeOptLayer.cpp \
                   ../../Classes/UI/HomeScene/HomeScene.cpp \
                   ../../Classes/UI/WorldScene/WorldHudLayer.cpp \
                   ../../Classes/UI/WorldScene/WorldMapLayer.cpp \
                   ../../Classes/UI/WorldScene/WorldScene.cpp \
                   ../../Classes/UI/BattleScene/AIManager.cpp \
                   ../../Classes/UI/BattleScene/BattleHudLayer.cpp \
                   ../../Classes/UI/BattleScene/BattleMapLayer.cpp \
                   ../../Classes/UI/BattleScene/BattleScene.cpp \
                   ../../Classes/UI/PanZoomLayer.cpp \
                   ../../Classes/Utils/DataManager.cpp \
                   ../../Classes/Utils/DBManager.cpp \
                   ../../Classes/Utils/GlobalManager.cpp 
                   

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../Classes/Helper \
					$(LOCAL_PATH)/../../Classes/Helper/CSVParser \
					$(LOCAL_PATH)/../../Classes/Helper/Sqlite3 \
					$(LOCAL_PATH)/../../Classes/Model \
					$(LOCAL_PATH)/../../Classes/UI \
					$(LOCAL_PATH)/../../Classes/UI/DialogScene \
					$(LOCAL_PATH)/../../Classes/UI/HelloScene \
					$(LOCAL_PATH)/../../Classes/UI/HomeScene \
					$(LOCAL_PATH)/../../Classes/UI/WorldScene \
					$(LOCAL_PATH)/../../Classes/UI/BattleScene \
					$(LOCAL_PATH)/../../Classes/Utils

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
