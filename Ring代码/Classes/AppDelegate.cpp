#include "AppDelegate.h"

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate() 
{

}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("Ring");
        glview->setFrameSize(480, 270);
        director->setOpenGLView(glview);
    }
    
    glview->setDesignResolutionSize(960, 640, ResolutionPolicy::FIXED_WIDTH);
    director->setDisplayStats(false);
    director->setAnimationInterval(1.0 / 60);
    
    this->loadResources();
    
    // WIN_SIZE = Director::getInstance()->getWinSize();
    
    auto scene = HelloScene::createScene();
//    auto scene = WorldScene::createScene();
//    auto scene = HomeScene::createScene();
//    auto scene = BattleScene::createScene();
    director->runWithScene(scene);
    
    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}

void AppDelegate::loadResources()
{
    // 创建数据库
    DBM()->createTable();
    
    // 加载数据到缓存
    DM();
    
    // 加载搜索路径
    FileUtils::getInstance()->addSearchPath("images");
    
    // 加载动画
    ArmatureDataManager::getInstance()->addArmatureFileInfo(ANIM_FIGHTER);
    ArmatureDataManager::getInstance()->addArmatureFileInfo(ANIM_BOWMAN);
    ArmatureDataManager::getInstance()->addArmatureFileInfo(ANIM_GUNNER);
    ArmatureDataManager::getInstance()->addArmatureFileInfo(ANIM_MEATSHIELD);
    ArmatureDataManager::getInstance()->addArmatureFileInfo(ANIM_HERO_ARAGORN);
    ArmatureDataManager::getInstance()->addArmatureFileInfo(ANIM_SKILL_1);
    ArmatureDataManager::getInstance()->addArmatureFileInfo(ANIM_SKILL_2);
}

