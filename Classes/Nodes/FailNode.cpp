//
//  FailNode.cpp
//  KongFu
//
//  Created by macuser on 16/8/29.
//
//

#include "FailNode.hpp"
#include "GlobalDefine.h"
#include "ChallengeScene.hpp"

FailNode::FailNode(){

}

FailNode::~FailNode(){

}

bool FailNode::init(){
    if (!Node::init()) {
        return false;
    }
    
    if (getBoolFromXML(MUSIC_KEY))
    {
        AudioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
        if (AudioEngine->isBackgroundMusicPlaying())
        {
            AudioEngine->pauseBackgroundMusic();
            AudioEngine->playBackgroundMusic("Sound/failure.wav", true);
        }
        else
        {
            AudioEngine->playBackgroundMusic("Sound/failure.wav", true);
        }
        
    }
    else
    {
        AudioEngine->pauseBackgroundMusic();
    }
    
    auto bgSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("heiping.png"));
    bgSprite->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
    this->addChild(bgSprite);
    
    auto bgTitle = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bgTitle.png"));
    bgTitle->setPosition(WINSIZE.width / 2 + 23, WINSIZE.height / 2 + 17);
    auto faliureTitle = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("faliure.png"));
    faliureTitle->setPosition(WINSIZE.width / 2, WINSIZE.height / 2 + 227);
    auto energyTitle = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tili.png"));
    energyTitle->setPosition(WINSIZE.width / 2, WINSIZE.height / 2 - 23);
    auto tips = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tipsNext.png"));
    tips->setPosition(WINSIZE.width / 2, WINSIZE.height / 2 - 227);
    
    auto m_pEnergyLabel = LabelTTF::create("-  1", "", 45);
    m_pEnergyLabel->setColor(Color3B(0, 255, 255));
    m_pEnergyLabel->setPosition(300, 60);
    
    bgSprite->addChild(bgTitle);
    bgSprite->addChild(faliureTitle);
    bgSprite->addChild(energyTitle);
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