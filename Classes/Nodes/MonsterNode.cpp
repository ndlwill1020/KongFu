//
//  MonsterNode.cpp
//  KongFu
//
//  Created by macuser on 16/8/29.
//
//

#include "MonsterNode.hpp"
#include "HeroNode.hpp"
#include "MapNode.hpp"
#include "BaseState.hpp"
#include "GlobalDefine.h"
#include "AnimationTools.hpp"
#include "GlobalData.h"

MonsterNode::MonsterNode()
:curState(MonsterState::IDLE)
,monsterSprite(nullptr)
,type(MonsterType::NONE_ATTRIBUTE)
,needFlippedX(false)
{

}

MonsterNode::~MonsterNode(){

}

MonsterNode* MonsterNode::createWithFileName_Level(const char* fileName, int level){
    MonsterNode *ret = new (std::nothrow) MonsterNode();
    if (ret && ret->initWithFileName_Level(fileName, level)) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool MonsterNode::initWithFileName_Level(const char* fileName, int level){
    if (!Node::init()) {
        return false;
    }
    
    _hp = 100 * (1 + 0.3 * level);
    monsterSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName));
    this->addChild(monsterSprite);
    
    
    return true;
}

void MonsterNode::startUpdate(HeroNode *heroNode, MapNode *mapNode){
    this->heroNode = heroNode;
    this->mapNode = mapNode;
    
    //this->schedule(schedule_selector(MonsterNode::calcDistance_update), 1.0f);
    scheduleUpdate();
}

//void MonsterNode::calcDistance_update(float dt){
//    if (this->curState == MonsterState::DEAD || heroNode->getCurState() == (BaseState *)BaseState::deadState) {
//        return;
//    }
//    
//    //相对于GameScene的layer
//    float delta = heroNode->getPositionX() - (mapNode->getPositionX() + this->getPositionX());
//    distanceFromHero = fabsf(delta);
//}

void MonsterNode::update(float dt){
    //log("MonsterNode update!!!!!!!!!! curState:%d",curState);
    if (this->curState == MonsterState::DEAD || heroNode->getCurState() == (BaseState *)BaseState::deadState) {
        unscheduleUpdate();
        return;
    }
    //hero － monster
    distanceFromHero = heroNode->getPositionX() - (mapNode->getPositionX() + this->getPositionX());
    
    if (fabsf(distanceFromHero) < WINSIZE.width) {
        followHero();
    } else {
        return;
    }
}


void MonsterNode::followHero(){
    //log("follow!!!!!!!!!!");
    //attack(范围120) hero
    if (fabsf(distanceFromHero) <= 120) {
        if (curState == MonsterState::RUN || curState == MonsterState::IDLE) {
            monsterSprite->stopAllActions();
            monsterSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("monsterWalk5.png"));
            curState = MonsterState::IDLE;
            
            //2.5秒后执行attack 期间也可能取消attack
            scheduleOnce(schedule_selector(MonsterNode::attack_updateOnce), 2.5f);
            return;
        }
    }
    
    //run(范围100) to hero
    if (distanceFromHero < -100) {//hero-left monster-right  //monster向left走
        //log("to left");
        if (this->curState == MonsterState::ATTACK) {
            return;
        }
        
        if (needFlippedX != false) {
            needFlippedX = false;
            monsterSprite->setFlippedX(needFlippedX);
        }
        //run
        executeRunAnimation("monsterWalk", 0.1f, -1);
        if (curState == MonsterState::RUN) {
            this->setPositionX(this->getPositionX() - 1.5f);
        }
    } else if (distanceFromHero > 100) {//向right走
        //log("to right");
        if (this->curState == MonsterState::ATTACK) {
            return;
        }
        
        if (needFlippedX != true) {
            needFlippedX = true;
            monsterSprite->setFlippedX(needFlippedX);
        }
        //run
        executeRunAnimation("monsterWalk", 0.1f, -1);
        if (curState == MonsterState::RUN) {
            this->setPositionX(this->getPositionX() + 1.5f);
        }
    }
}

void MonsterNode::attack_updateOnce(float dt){
    
    executeAttackAnimation("monsterA", 0.08f, 1);
}

//之前已设置好flippedX
void MonsterNode::executeRunAnimation(const char *eachFileName, float delay, int iLoops){
    if (curState == MonsterState::ATTACK || curState == MonsterState::RUN || curState == MonsterState::HURT || curState == MonsterState::DEAD) {
        return;
    }
    log("run!!!!!!!!!!!!!!!!!!!!!!!!!");
    Animate* animate = AnimationTools::animationWithFrameName(eachFileName, iLoops, delay);
    monsterSprite->runAction(animate);
    curState = MonsterState::RUN;
    
//    if (this->needFlippedX == true) {//to left
//        this->setPositionX(this->getPositionX() - 1.5f);
//    } else {
//        this->setPositionX(this->getPositionX() + 1.5f);
//    }
}

void MonsterNode::executeAttackAnimation(const char *eachFileName, float delay, int iLoops){
    //要attack时，如果hero离开攻击范围，不攻击，去followHero
    if (curState == MonsterState::RUN || curState == MonsterState::HURT || curState == MonsterState::ATTACK || curState == MonsterState::DEAD) {
        return;
    }
    
    Animate* animate = AnimationTools::animationWithFrameName(eachFileName, iLoops, delay);
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MonsterNode::attackAnimationFinished_ActionCB, this));
    curState = MonsterState::ATTACK;//必中
    monsterSprite->runAction(Sequence::create(animate, callFunc, NULL));
}

void MonsterNode::attackAnimationFinished_ActionCB(){
    monsterSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("monsterWalk5.png"));
    curState = MonsterState::IDLE;
}

void MonsterNode::executeHurtAnimation(const char *eachFileName, float delay, int iLoops){
    if (curState == MonsterState::HURT) {
        return;
    }
    
    //受伤优先
    if (curState == MonsterState::RUN || curState == MonsterState::ATTACK) {
        monsterSprite->stopAllActions();
        monsterSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("monsterWalk5.png"));
    }
    Animate* animate = AnimationTools::animationWithFrameName(eachFileName, iLoops, delay);
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MonsterNode::hurtAnimationFinished_ActionCB, this));
    ActionInterval* seqAction = Sequence::create(animate, callFunc, NULL);
    
    curState = MonsterState::HURT;
    monsterSprite->runAction(seqAction);
    
}

void MonsterNode::hurtAnimationFinished_ActionCB(){
    curState = MonsterState::IDLE;
    
    if (heroNode->getIsCrazy()) {
        _hp -= 100;
    } else {
        _hp -= 30;
    }
    
    if (_hp <= 0) {
        curMonsterList.eraseObject(this);//hp < 0先从集合中移除，执行完动作，再从界面中移除，被释放
        curState = MonsterState::DEAD;
        executeDeadAnimation("monsterDie", 0.1f, 1);
    }
}

void MonsterNode::executeDeadAnimation(const char *eachFileName, float delay, int iLoops){
    Animate* animate = AnimationTools::animationWithFrameName(eachFileName, iLoops, delay);
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MonsterNode::deadAnimationFinished_ActionCB, this));
    ActionInterval* seqAction = Sequence::create(animate, callFunc, NULL);
    monsterSprite->runAction(seqAction);
    //curState = MonsterState::DEAD;
    
    if (heroNode->getCurMP() < 100) {
        heroNode->setCurMP(heroNode->getCurMP() + 50.0f);
        if (heroNode->getCurMP() > 100) {
            heroNode->setCurMP(100);
        }
    }
}

void MonsterNode::deadAnimationFinished_ActionCB(){
    monsterSprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("monsterDie6.png"));
    
    Blink* blink = Blink::create(3.0f, 3);
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(MonsterNode::blinkFinished_ActionCB, this));
    ActionInterval* seqAction = Sequence::create(blink, callFunc, NULL);
    monsterSprite->runAction(seqAction);
}

void MonsterNode::blinkFinished_ActionCB(){
    this->removeFromParentAndCleanup(true);
    
}