//
//  ChallengeScene.cpp
//  KongFu
//
//  Created by macuser on 16/8/24.
//
//

#include "ChallengeScene.hpp"
#include "StartScene.hpp"
#include "GlobalDefine.h"
#include "SelectLevelNode.hpp"
#include "GameScene.hpp"
#include "GlobalData.h"

ChallengeScene::ChallengeScene(){

}

ChallengeScene::~ChallengeScene(){

}

Scene* ChallengeScene::createScene(){
    auto scene = Scene::create();
    auto layer = ChallengeScene::create();
    scene->addChild(layer);
    return scene;
}

bool ChallengeScene::init(){
    if (!Layer::init()) {
        return false;
    }
    
    if (getBoolFromXML(MUSIC_KEY))
    {
        //float music = getFloatFromXML(MUSICVOL) * 100.0f;
        AudioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
        if (AudioEngine->isBackgroundMusicPlaying())
        {
            AudioEngine->pauseBackgroundMusic();
            AudioEngine->playBackgroundMusic("Sound/gateMap.wav", true);
        }
        else
        {
            AudioEngine->playBackgroundMusic("Sound/gateMap.wav", true);
        }
    }
    else
    {
        AudioEngine->pauseBackgroundMusic();
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pngPlist/gateMap.plist");
    
    auto bgPic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("GateMapBG.png"));
    bgPic->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
    this->addChild(bgPic);
    
    auto closeItem = MenuItemSprite::create(
                                            Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CloseNormal.png")),
                                            Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CloseSelected.png")),
                                            CC_CALLBACK_1(ChallengeScene::close_menuCB, this)); // 退出
    
    auto challengeItem = MenuItemSprite::create(
                                                Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tiaozhanNormal.png")),
                                                Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tiaozhanSelected.png")),
                                                CC_CALLBACK_1(ChallengeScene::challenge_menuCB, this)); // 挑战
    
    closeItem->setPosition(WINSIZE.width - 47, WINSIZE.height - 44);
    challengeItem->setPosition(WINSIZE.width - 253, 7 * WINSIZE.height / 72);
    auto menu = Menu::create(closeItem, challengeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    auto item1 = MenuItemSprite::create(
                                              Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_1.png")),
                                              Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_1.png")),
                                              CC_CALLBACK_1(ChallengeScene::item1_menuCB, this)); // 退出
    
    auto item2 = MenuItemSprite::create(
                                              Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_2.png")),
                                              Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_2.png")),
                                              CC_CALLBACK_1(ChallengeScene::item2_menuCB, this)); // 退出
    
    auto item3 = MenuItemSprite::create(
                                                Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_3.png")),
                                                Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_3.png")),
                                                CC_CALLBACK_1(ChallengeScene::item3_menuCB, this)); // 退出
    
    //sprites
//    auto item1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_1.png"));
//    auto item2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_2.png"));
//    auto item3 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_3.png"));
    
    levelNode = SelectLevelNode::create();
    levelNode->addMenuItem(item1);
    levelNode->addMenuItem(item2);
    levelNode->addMenuItem(item3);
//    levelNode->addItem(item1);
//    levelNode->addItem(item2);
//    levelNode->addItem(item3);
    levelNode->setPosition(WINSIZE.width / 2, WINSIZE.height / 2 + 74);
    this->addChild(levelNode, 2);
    
    
    
    auto m_pMoneyLabel = LabelTTF::create("1000", "", 45);
    m_pMoneyLabel->setColor(Color3B(0, 255, 255));
    m_pMoneyLabel->setPosition(300, 60);
    
    auto m_pEnergyLabel = LabelTTF::create("10", "", 45);
    m_pEnergyLabel->setColor(Color3B(0, 255, 255));
    m_pEnergyLabel->setPosition(640, 60);
    
    this->addChild(m_pMoneyLabel);
    this->addChild(m_pEnergyLabel);
    return true;
}

void ChallengeScene::close_menuCB(Ref* pSender){
    PLAY_BUTTON_EFFECT
    Director::getInstance()->replaceScene(StartScene::createScene());
}

void ChallengeScene::challenge_menuCB(Ref* pSender){
    PLAY_BUTTON_EFFECT
    levelNode->getCurrentItem()->activate();//执行回调
}

void ChallengeScene::item1_menuCB(Ref* pSender){
    log("item1 cb!!!!!!!!");
    PLAY_BUTTON_EFFECT
    setIntToXML(GAMELEVEL_KEY, 1);
    setIntToXML(SELECTEDLEVEl, 1);
    UserDefault::getInstance()->flush();
    gSelectedLevel = 1;
    Director::getInstance()->replaceScene(GameScene::createScene());
}

void ChallengeScene::item2_menuCB(Ref* pSender){
    log("item2 cb!!!!!!!!");
    PLAY_BUTTON_EFFECT
    if (getBoolFromXML(LEVELONE, false))
    {
        setIntToXML(GAMELEVEL_KEY, 2);
        setIntToXML(SELECTEDLEVEl, 2);
        UserDefault::getInstance()->flush();
        gSelectedLevel = 2;
        Director::getInstance()->replaceScene(GameScene::createScene());
    }
}

void ChallengeScene::item3_menuCB(Ref* pSender){
    log("item3 cb!!!!!!!!");
}
