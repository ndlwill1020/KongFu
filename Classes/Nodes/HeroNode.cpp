//
//  Hero.cpp
//  KongFu
//
//  Created by macuser on 16/8/19.
//
//

#include "HeroNode.hpp"
//#include "BaseInput.hpp"
#include "BaseState.hpp"
#include "AnimationTools.hpp"
#include "GlobalDefine.h"

HeroNode::HeroNode()
:curState(nullptr)
,needFlippedX(false)
,jumpVelocity(0.0f)
,isCrazy(false)
,isDeadEnded(false)
,isExecuteDead(false)
,isExecuteHurt(false)
{
    
}

HeroNode::~HeroNode(){
    
}

HeroNode* HeroNode::createWithFileName_Level(const char* fileName, int level){
    HeroNode* ret = new (std::nothrow) HeroNode();
    if (ret && ret->initWithFileName_Level(fileName, level)) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool HeroNode::initWithFileName_Level(const char* fileName, int level){
    if (!Node::init()) {
        return false;
    }
    //for test
//    auto layerColor = LayerColor::create(Color4B::RED, WINSIZE.width, WINSIZE.height);
//    this->addChild(layerColor);
    
    curHP = totalHP = 300.0f * level;
    curMP = 0.0f;
    totalMP = 100.0f;
    hpPercent = 100.0f;
    
    heroSpeed = 5.0f;
    jumpVelocity = 10.0f;
    heroSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName));
    this->addChild(heroSprite);
    
    
    //test for FlippedX  position
//    log("%f",heroSprite->getPositionX());
//    heroSprite->setFlippedX(true);
//    log("%f",heroSprite->getPositionX());

    
    curState = (BaseState *)BaseState::idleState;
    
    
    
    return true;
}

//void HeroNode::handleInput(BaseInput *input){
//    if (input == nullptr) {
//        return;
//    }
//    _curState->handleInput(this, input);
//}

void HeroNode::handleInput(InputType type){
    log("handle input!!!!!!");
    if (type == InputType::NONE) {
        return;
    }
    curState->handleInput(this, type);
}

void HeroNode::executeRunAnimation(const char* eachFileName, float delay){
    Animate *animate = AnimationTools::animationWithFrameName(eachFileName, -1, delay);
    heroSprite->runAction(animate);
}

void HeroNode::stopAnimations_resetIdleImage(){
    heroSprite->stopAllActions();
    //setTexture有bug 可能和精灵帧(SpriteFrame)有关
    heroSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("idle.png"));
}

void HeroNode::executeAttackAnimation(const char* eachFileName, float delay){
    log("execute attack animation!!!!!!");
    if (this->isCrazy) {
        curMP = 0.0f;
    }
    Animate *animate = AnimationTools::animationWithFrameName(eachFileName, 1, delay);
    CallFunc *func = CallFunc::create(CC_CALLBACK_0(HeroNode::attackAnimationFinished_ActionCB, this));
    heroSprite->runAction(Sequence::create(animate, func, NULL));
}

void HeroNode::attackAnimationFinished_ActionCB(){
    curState = (BaseState *)BaseState::idleState;
    if (this->isCrazy) {
        isCrazy = false;
    }
}

void HeroNode::executeJumpUpAnimation(const char* eachFileName, float delay){
    Animate *animate = AnimationTools::animationWithFrameName(eachFileName, -1, delay);
    heroSprite->runAction(animate);
}

void HeroNode::executeJumpDownAnimation(const char* eachFileName, float delay){
    Animate *animate = AnimationTools::animationWithFrameName(eachFileName, -1, delay);
    heroSprite->runAction(animate);
}

void HeroNode::executeHurtAnination(const char* eachFileName, float delay){
    if (isExecuteHurt == true) {
        return;
    }
    log("execute hurt-------------------------");
    isExecuteHurt = true;
    curHP -= 100.0f;
    if (curHP <= 0.0f) {
        log("######################## hp=0");
        hpPercent = 0.0f;
        curState = (BaseState *)BaseState::deadState;
    } else {
        log("######################## hp>0");
        hpPercent = curHP / totalHP * 100.0f;
        //isExecuteHurt = true;
        stopAnimations_resetIdleImage();
        Animate* animate = AnimationTools::animationWithFrameName(eachFileName, 1, delay);
        CallFunc* func = CallFunc::create(CC_CALLBACK_0(HeroNode::hurtAnimationFinished_ActionCB, this));
        heroSprite->runAction(Sequence::create(animate, func, NULL));
    }
}

void HeroNode::hurtAnimationFinished_ActionCB(){
    log("hurt finished------------------------");
    curState = (BaseState *)BaseState::idleState;
    isExecuteHurt = false;
}

void HeroNode::executeDeadAnimation(const char* eachFileName, float delay){
    if (isExecuteDead == true) {
        return;
    }
    isExecuteDead = true;
    heroSprite->stopAllActions();
    Animate* animate = AnimationTools::animationWithFrameName(eachFileName, 1, delay);
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(HeroNode::deadAnimationFinished_ActionCB, this));
    ActionInterval* seqAction = Sequence::create(animate, callFunc, NULL);
    Director::getInstance()->getScheduler()->setTimeScale(0.5f);
    heroSprite->runAction(seqAction);
}

void HeroNode::deadAnimationFinished_ActionCB(){
    heroSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("monsterDie6.png"));
    isDeadEnded = true;
}




bool HeroNode::isReachCenter(Size winSize){
    if (this->getPositionX() > (WINSIZE.width / 2 +2.0f) || (this->getPositionX() < WINSIZE.width / 2 - 2.0f)) {
        return false;
    } else {
        return true;
    }
}



