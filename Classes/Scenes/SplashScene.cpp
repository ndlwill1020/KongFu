//
//  SplashScene.cpp
//  KongFu
//
//  Created by macuser on 16/8/23.
//
//

#include "SplashScene.hpp"
#include "StartScene.hpp"
#include "GlobalDefine.h"

SplashScene::SplashScene()
:loadedCount(0)
{

}

SplashScene::~SplashScene(){

}

Scene* SplashScene::createScene(){
    auto scene = Scene::create();
    auto layer = SplashScene::create();
    scene->addChild(layer);
    return scene;
}

bool SplashScene::init(){
    if (!Layer::init()) {
        return false;
    }
    
    logoSprite = Sprite::create("logo.png");
    logoSprite->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
    this->addChild(logoSprite);
    
    // 首次运行初始化用户数据
    if (!getBoolFromXML("_IS_EXISTED"))//默认值false
    {
        initUserData();
        setBoolToXML("_IS_EXISTED", true);
        UserDefault::getInstance()->flush();
    }
    
    setFloatToXML(SOUNDVOL, 0.8f);
    setFloatToXML(MUSICVOL, 0.35f);
    UserDefault::getInstance()->flush();
    
    Director::getInstance()->getTextureCache()->addImageAsync("pngPlist/startGame.png", CC_CALLBACK_1(SplashScene::loadingTextureCallBack, this));
    // 图籍
    Director::getInstance()->getTextureCache()->addImageAsync("pngPlist/gameLayer.png", CC_CALLBACK_1(SplashScene::loadingTextureCallBack, this));
    // 设置
    Director::getInstance()->getTextureCache()->addImageAsync("pngPlist/setLayer.png", CC_CALLBACK_1(SplashScene::loadingTextureCallBack, this));
    // 秘籍
    Director::getInstance()->getTextureCache()->addImageAsync("pngPlist/cheatsLayer.png", CC_CALLBACK_1(SplashScene::loadingTextureCallBack, this));
    // 选关
    Director::getInstance()->getTextureCache()->addImageAsync("pngPlist/gateMap.png", CC_CALLBACK_1(SplashScene::loadingTextureCallBack, this));
    // 暂停
    Director::getInstance()->getTextureCache()->addImageAsync("pngPlist/pauseLayer.png", CC_CALLBACK_1(SplashScene::loadingTextureCallBack, this));
    
    // 英雄
    Director::getInstance()->getTextureCache()->addImageAsync("pngPlist/hero.png", CC_CALLBACK_1(SplashScene::loadingTextureCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("pngPlist/heroComobo.png", CC_CALLBACK_1(SplashScene::loadingTextureCallBack, this));
    Director::getInstance()->getTextureCache()->addImageAsync("pngPlist/heroGun.png", CC_CALLBACK_1(SplashScene::loadingTextureCallBack, this));
    
    //异步加载声音
    _loadingAudioThread = new std::thread(&SplashScene::loadingAudio, this);
    
    return true;
}

void SplashScene::loadingTextureCallBack(Texture2D *texture){
    switch (loadedCount++)
    {
        case 0:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pngPlist/startGame.plist", texture);
            break;
        case 1:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pngPlist/gameLayer.plist", texture);
            break;
        case 2:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pngPlist/setLayer.plist", texture);
            break;
        case 3:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pngPlist/cheatsLayer.plist", texture);
            break;
        case 4:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pngPlist/gateMap.plist", texture);
            break;
        case 5:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pngPlist/pauseLayer.plist", texture);
            break;
        case 6:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pngPlist/hero.plist", texture);
            break;
        case 7:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pngPlist/heroComobo.plist", texture);
            break;
        case 8:
            SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pngPlist/heroGun.plist", texture);
            this->schedule(schedule_selector(SplashScene::nextScene), 1.0f, 1, 1.0f);//repeat1次 一共走2次update
            break;
        default:
            break;
    }
}

void SplashScene::loadingAudio(){
    //初始化 音乐
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sound/startBGM.mp3");
    //初始化音效
    SimpleAudioEngine::getInstance()->preloadEffect("Sound/button.wav");
}

void SplashScene::initUserData(){
    setIntToXML(GAMELEVEL_KEY, 1);        // 初始化关卡
    setIntToXML(HEROENERGY_KEY, 10);  // 初始化体力
    setIntToXML(HEROCOIN_KEY, 1000);    // 初始化金币
    setBoolToXML(SOUND_KEY, true);
    setBoolToXML(MUSIC_KEY, true);
    // 刷新
    UserDefault::getInstance()->flush();
}

void SplashScene::onExitTransitionDidStart(){
    Layer::onExitTransitionDidStart();
    log("Splash Scene onExitTransitionDidStart!!!!!!!!!!!");
}

void SplashScene::onExit(){
    Layer::onExit();
    log("Splash Scene onExit!!!!!!!!!!!");
    _loadingAudioThread->join();
    CC_SAFE_DELETE(_loadingAudioThread);
    
}

void SplashScene::nextScene(float dt){
    log("next scene!!!!!!!!!!!!!!!!");
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, StartScene::createScene()));
    this->unschedule(schedule_selector(SplashScene::nextScene));
}
