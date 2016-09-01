//
//  RunState.cpp
//  KongFu
//
//  Created by macuser on 16/8/25.
//
//

#include "RunState.hpp"
#include "HeroNode.hpp"
#include "MapNode.hpp"
#include "GlobalDefine.h"
RunState::RunState(){

}

RunState::~RunState(){

}

void RunState::handleInput(HeroNode *heroNode, InputType type){
    switch (type) {
        case InputType::FIST_CLICKED:
            
            break;
        case InputType::FOOT_CLICKED:
            
            break;
        case InputType::LEFT_DARGOUT:
            heroNode->stopAnimations_resetIdleImage();
            heroNode->setCurState((BaseState *)BaseState::idleState);
            break;
        case InputType::LEFT_RELEASED:
            heroNode->stopAnimations_resetIdleImage();
            heroNode->setCurState((BaseState *)BaseState::idleState);
            break;
            
        case InputType::RIGHT_DARGOUT:
            heroNode->stopAnimations_resetIdleImage();
            heroNode->setCurState((BaseState *)BaseState::idleState);
            break;
            
        case InputType::RIGHT_RELEASED:
            heroNode->stopAnimations_resetIdleImage();
            heroNode->setCurState((BaseState *)BaseState::idleState);
            break;
            
        default:
            break;
    }
}

void RunState::updateHero_Map(HeroNode *heroNode, MapNode *mapNode){
    log("runState update!!!!!!");
    if (heroNode->getNeedFlippedX() == false) {//right
        if (heroNode->getPositionX() <= WINSIZE.width - 8.0f) {
            //hero没到达窗口中间位置或者map已经移动到边缘了，hero才可以移动，否则只播放动画
            if (heroNode->isReachCenter(WINSIZE) == false || mapNode->isReachBorder(heroNode) == true) {
                heroNode->setPositionX(heroNode->getPositionX() + heroNode->getHeroSpeed());
            }
            //map移动
            mapNode->moveMap(heroNode);
        }
    } else {//left
        if (heroNode->getPositionX() >= 8.0f) {
            if (!heroNode->isReachCenter(WINSIZE) || mapNode->isReachBorder(heroNode)) {
                heroNode->setPositionX(heroNode->getPositionX() - heroNode->getHeroSpeed());
            }
            mapNode->moveMap(heroNode);
        }
    }
}