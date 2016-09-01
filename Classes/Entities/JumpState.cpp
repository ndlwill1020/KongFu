//
//  JumpState.cpp
//  KongFu
//
//  Created by macuser on 16/8/25.
//
//

#include "JumpState.hpp"
#include "HeroNode.hpp"
#include "MapNode.hpp"
#include "GlobalDefine.h"

JumpState::JumpState(){

}

JumpState::~JumpState(){

}

void JumpState::handleInput(HeroNode *heroNode, InputType type){
    switch (type) {
        case InputType::FIST_CLICKED:
            //DO NOTHING
            break;
        case InputType::FOOT_CLICKED:
            //DO NOTHING
            break;
        case InputType::LEFT_PRESSED:
            //DO NOTHING
            break;
        case InputType::RIGHT_PRESSED:
            //DO NOTHING
            break;
            
        
            
        default:
            break;
    }
}

void JumpState::updateHero_Map(HeroNode *heroNode, MapNode *mapNode){
    log("JumpState update!!!!!!!!!!");
    float curJumpVelocity = heroNode->getJumpVelocity();
    if (curJumpVelocity >= 0.1) {//向上运动
        heroNode->executeJumpUpAnimation("jumpup", 0.1f);
//        if (heroNode->getNeedFlippedX() == false) {//right
//            if (heroNode->getPositionX() <= WINSIZE.width - 8.0f) {
//                if (!heroNode->isReachCenter(WINSIZE) || mapNode->isReachBorder(heroNode)) {
//                    heroNode->setPosition(Vec2(heroNode->getPositionX() + heroNode->getHeroSpeed(), heroNode->getPositionY() + curJumpVelocity));
//                } else {
//                    heroNode->setPosition(Vec2(heroNode->getPositionX(), heroNode->getPositionY() + curJumpVelocity));
//                }
//                mapNode->moveMap(heroNode);
//            } else {
//                heroNode->setPosition(Vec2(heroNode->getPositionX(), heroNode->getPositionY() + curJumpVelocity));
//            }
//        } else {//left
//            if (heroNode->getPositionX() >= 8.0f) {
//                if (!heroNode->isReachCenter(WINSIZE) || mapNode->isReachBorder(heroNode)) {
//                    heroNode->setPosition(Vec2(heroNode->getPositionX() - heroNode->getHeroSpeed(), heroNode->getPositionY() + curJumpVelocity));
//                } else {
//                    heroNode->setPosition(Vec2(heroNode->getPositionX(), heroNode->getPositionY() + curJumpVelocity));
//                }
//                mapNode->moveMap(heroNode);
//            } else {
//                heroNode->setPosition(Vec2(heroNode->getPositionX(), heroNode->getPositionY() + curJumpVelocity));
//            }
//        }
    } else {//向下运动
        heroNode->executeJumpDownAnimation("jumpdown", 0.1f);
    }
    
    if (heroNode->getNeedFlippedX() == false) {//right
        if (heroNode->getPositionX() <= WINSIZE.width - 8.0f) {
            if (!heroNode->isReachCenter(WINSIZE) || mapNode->isReachBorder(heroNode)) {
                heroNode->setPosition(Vec2(heroNode->getPositionX() + heroNode->getHeroSpeed(), heroNode->getPositionY() + curJumpVelocity));
            } else {
                heroNode->setPosition(Vec2(heroNode->getPositionX(), heroNode->getPositionY() + curJumpVelocity));
            }
            mapNode->moveMap(heroNode);
        } else {
            heroNode->setPosition(Vec2(heroNode->getPositionX(), heroNode->getPositionY() + curJumpVelocity));
        }
    } else {//left
        if (heroNode->getPositionX() >= 8.0f) {
            if (!heroNode->isReachCenter(WINSIZE) || mapNode->isReachBorder(heroNode)) {
                heroNode->setPosition(Vec2(heroNode->getPositionX() - heroNode->getHeroSpeed(), heroNode->getPositionY() + curJumpVelocity));
            } else {
                heroNode->setPosition(Vec2(heroNode->getPositionX(), heroNode->getPositionY() + curJumpVelocity));
            }
            mapNode->moveMap(heroNode);
        } else {
            heroNode->setPosition(Vec2(heroNode->getPositionX(), heroNode->getPositionY() + curJumpVelocity));
        }
    }
    
    if (heroNode->getPositionY() <= 360.0f) {
        heroNode->stopAnimations_resetIdleImage();
        heroNode->setCurState((BaseState *)BaseState::idleState);
        heroNode->setPositionY(360.0f);
        //heroNode->setPosition(Vec2(heroNode->getPositionX() + 3.0f, 360.0f));
        heroNode->setJumpVelocity(10.0f);
    }

}