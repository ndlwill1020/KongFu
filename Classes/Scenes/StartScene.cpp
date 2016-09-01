//
//  StartScene.cpp
//  KongFu
//
//  Created by macuser on 16/8/23.
//
//

#include "StartScene.hpp"
#include "GlobalDefine.h"
#include "CheatsScene.hpp"
#include "SettingScene.hpp"
#include "PictureAtlasScene.hpp"
#include "HelpScene.hpp"
#include "ChallengeScene.hpp"

StartScene::StartScene(){

}

StartScene::~StartScene(){

}

Scene* StartScene::createScene(){
    auto scene = Scene::create();
    auto layer = StartScene::create();
    scene->addChild(layer);
    return scene;
}

bool StartScene::init(){
    if (!Layer::init()) {
        return false;
    }
    log("StartScene init!!!!!!!!!!!!!!!");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pngPlist/galleryLayer.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pngPlist/monster.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pngPlist/resultLayer.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pngPlist/mapBg.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pngPlist/mapMid.plist");
    
    if (getBoolFromXML(MUSIC_KEY))
    {
        //float music = getFloatFromXML(MUSICVOL) * 100.0f;
        AudioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
        if (AudioEngine->isBackgroundMusicPlaying())
        {
            AudioEngine->pauseBackgroundMusic();
            AudioEngine->playBackgroundMusic("Sound/startBGM.mp3", true);
        }
        else
        {
            log("!!!!!");
            AudioEngine->playBackgroundMusic("Sound/startBGM.mp3", true);
        }
        
    }
    else
    {
        AudioEngine->pauseBackgroundMusic();
    }
    
    if (getBoolFromXML(SOUND_KEY)) {
        AudioEngine->setEffectsVolume(getFloatFromXML(SOUNDVOL));
    }
    
    
    
    Sprite *title = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Title.png"));
    title->setPosition(WINSIZE.width / 2 - 222, WINSIZE.height / 2 + 186);
    Sprite *bgPic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("MainMenuBackground.png"));
    bgPic->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
    
    this->addChild(bgPic, -1);
    this->addChild(title, 1);
    
    auto helpItem = MenuItemSprite::create(
                                           Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("HelpNormal.png")),
                                           Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("HelpSelected.png")),
                                           CC_CALLBACK_1(StartScene::help_menuCB, this)); // 帮助
    
    auto tujiItem = MenuItemSprite::create(
                                           Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PhotoGalleryNormal.png")),
                                           Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PhotoGallerySelected.png")),
                                           CC_CALLBACK_1(StartScene::photo_menuCB, this)); // 图籍
    
    auto setItem = MenuItemSprite::create(
                                          Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("SetNormal.png")),
                                          Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("SetSelected.png")),
                                          CC_CALLBACK_1(StartScene::set_menuCB, this)); // 设置
    
    
    auto mijiItem = MenuItemSprite::create(
                                           Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CheatsNormal.png")),
                                           Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CheatsSelected.png")),
                                           CC_CALLBACK_1(StartScene::cheats_menuCB, this)); // 秘籍
    
    auto chuangguanItem = MenuItemSprite::create(
                                                 Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("EmigratedNormal.png")),
                                                 Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("EmigratedSelected.png")),
                                                 CC_CALLBACK_1(StartScene::levelMode_menuCB, this)); // 闯关
    
    auto tiaozhanItem = MenuItemSprite::create(
                                               Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ChallengeNormal.png")),
                                               Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ChallengeSelected.png")),
                                               CC_CALLBACK_1(StartScene::challenge_menuCB, this)); // 挑战
    
    tujiItem->setPosition(WINSIZE.width - 62, WINSIZE.height - 73);
    mijiItem->setPosition(WINSIZE.width - 62, WINSIZE.height - 209);
    setItem->setPosition(WINSIZE.width - 62, WINSIZE.height - 346);
    helpItem->setPosition(WINSIZE.width - 62, WINSIZE.height - 473);
    chuangguanItem->setPosition(WINSIZE.width / 2 - 240, WINSIZE.height / 2 - 86);
    tiaozhanItem->setPosition(WINSIZE.width / 2 - 240, WINSIZE.height / 2 - 250);
    
    
    auto menu = Menu::create(tujiItem, mijiItem, setItem, helpItem, chuangguanItem, tiaozhanItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 2);
    
    
    
    return true;
}

void StartScene::help_menuCB(Ref* pSender){
    PLAY_BUTTON_EFFECT
    Director::getInstance()->replaceScene(HelpScene::createScene());
}

void StartScene::photo_menuCB(Ref* pSender){
    PLAY_BUTTON_EFFECT
    Director::getInstance()->replaceScene(PictureAtlasScene::createScene());
}

void StartScene::cheats_menuCB(Ref* pSender){
    PLAY_BUTTON_EFFECT
    Director::getInstance()->replaceScene(CheatsScene::createScene());
}

void StartScene::set_menuCB(Ref* pSender){
    PLAY_BUTTON_EFFECT
    Director::getInstance()->replaceScene(SettingScene::createScene());
}

void StartScene::levelMode_menuCB(Ref* pSender){
    PLAY_BUTTON_EFFECT
    
}

void StartScene::challenge_menuCB(Ref* pSender){
    PLAY_BUTTON_EFFECT
    Director::getInstance()->replaceScene(ChallengeScene::createScene());
}

void StartScene::onEnter(){
    Layer::onEnter();
    log("StartScene onEnter!!!!!!!!!!!!!!!");
}

void StartScene::onEnterTransitionDidFinish(){
    Layer::onEnterTransitionDidFinish();
    log("StartScene onEnterTransitionDidFinish!!!!!!!!!!!!!!!");
}