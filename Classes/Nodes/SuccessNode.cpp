//
//  SuccessNode.cpp
//  KongFu
//
//  Created by macuser on 16/8/29.
//
//

#include "SuccessNode.hpp"
#include "GlobalDefine.h"
#include "GlobalData.h"
#include "ChallengeScene.hpp"

SuccessNode::SuccessNode(){

}

SuccessNode::~SuccessNode(){

}

bool SuccessNode::init(){
    if (!Node::init()) {
        return false;
    }
    
    if (getBoolFromXML(MUSIC_KEY))
    {
        AudioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
        if (AudioEngine->isBackgroundMusicPlaying())
        {
            AudioEngine->pauseBackgroundMusic();
            AudioEngine->playBackgroundMusic("Sound/victory.wav", true);
        }
        else {
            AudioEngine->playBackgroundMusic("Sound/victory.wav", true);
        }
    }
    else
    {
        AudioEngine->pauseBackgroundMusic();
    }
    
    if (gSelectedLevel == 1)
    {
        setBoolToXML(LEVELONE, true);
    }
    else if (gSelectedLevel == 2)
    {
        setBoolToXML(LEVELONE, true);
    }
    else {
        setBoolToXML(LEVELONE, true);
    }
    
    // 弹出游戏胜利的界面
    auto bgSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("heiping.png"));
    bgSprite->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
    this->addChild(bgSprite, 5);
    auto bgTitle = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bgTitle.png"));
    bgTitle->setPosition(WINSIZE.width / 2 + 23, WINSIZE.height / 2 + 17);
    auto victoryTitle = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("victory.png"));
    victoryTitle->setPosition(WINSIZE.width / 2, WINSIZE.height / 2 + 227);
    auto energyTitle = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tili.png"));
    energyTitle->setPosition(WINSIZE.width / 2 + 116, WINSIZE.height / 2 - 23);
    auto moneyTitle = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jinbi.png"));
    moneyTitle->setPosition(WINSIZE.width / 2 - 275, WINSIZE.height / 2 - 27);
    auto tips = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tipsNext.png"));
    tips->setPosition(WINSIZE.width / 2, WINSIZE.height / 2 - 227);
    bgSprite->addChild(bgTitle);
    bgSprite->addChild(victoryTitle);
    bgSprite->addChild(energyTitle);
    bgSprite->addChild(moneyTitle);
    bgSprite->addChild(tips);
    
    // 获取事件分发器
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    // 触摸监听器
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](Touch* touch, Event* event){return true; };
    listener->onTouchMoved = [](Touch* touch, Event* event){};
    listener->onTouchEnded = [](Touch* touch, Event* event){
        Director::getInstance()->replaceScene(ChallengeScene::createScene());
    };
    listener->setSwallowTouches(true);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}