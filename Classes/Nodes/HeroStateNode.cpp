//
//  HeroStateNode.cpp
//  KongFu
//
//  Created by macuser on 16/8/24.
//
//

#include "HeroStateNode.hpp"
#include "GlobalDefine.h"

HeroStateNode::HeroStateNode(){
    
}

HeroStateNode::~HeroStateNode(){
    
}

bool HeroStateNode::init(){
    if (!Node::init()) {
        return false;
    }
    
    auto bg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("barGround.png"));
    
    hpBar = ProgressTimer::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("HPBar.png")));
    hpBar->setType(ProgressTimer::Type::BAR);
    hpBar->setMidpoint(Vec2(0, 0.5));
    hpBar->setBarChangeRate(Vec2(1, 0));
    hpBar->setPercentage(100.0f);
    
    mpBar = ProgressTimer::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("MPBar.png")));
    mpBar->setType(ProgressTimer::Type::BAR);
    mpBar->setMidpoint(Vec2(0, 0.5));
    mpBar->setBarChangeRate(Vec2(1, 0));
    mpBar->setPercentage(0.0f);
    
    hpBar->setPosition(240, 45);
    mpBar->setPosition(226, 30);
    
    bg->addChild(hpBar);
    bg->addChild(mpBar);
    
    bg->setPosition(260, WINSIZE.height - 60);
    
    this->addChild(bg);
    
    
    return true;
}
