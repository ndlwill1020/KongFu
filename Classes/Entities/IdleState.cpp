//
//  IdleState.cpp
//  KongFu
//
//  Created by macuser on 16/8/25.
//
//

#include "IdleState.hpp"

#include "HeroNode.hpp"
#include "MapNode.hpp"
#include "GlobalData.h"
//#include "BaseInput.hpp"


IdleState::IdleState(){

}

IdleState::~IdleState(){

}

void IdleState::handleInput(HeroNode *heroNode, InputType type){
    log("idle state handle input!!!!!!");
    switch (type) {
        case InputType::FIST_CLICKED:
            log("idle state -> fist");
            heroNode->setCurState((BaseState *)BaseState::attackState);
            heroNode->executeAttackAnimation("fist", 0.1f);
            break;
        case InputType::FOOT_CLICKED:
            heroNode->setCurState((BaseState *)BaseState::attackState);
            heroNode->executeAttackAnimation("leg", 0.1f);
            break;
        case InputType::JUMP_CLICKED:
            heroNode->setCurState((BaseState *)BaseState::jumpState);//设置current状态
            
            break;
        case InputType::SKILL_CLICKED:
            heroNode->setIsCrazy(true);
            heroNode->setCurState((BaseState *)BaseState::attackState);
            switch (gSelectedLevel) {
                case 1:
                    heroNode->executeAttackAnimation("combo", 0.1f);
                    break;
                case 2:
                    heroNode->executeAttackAnimation("bakandao", 0.1f);
                    break;
                case 3:
                    heroNode->executeAttackAnimation("gun", 0.1f);
                    break;
                    
                default:
                    break;
            }
            break;
            
            
            
        case InputType::LEFT_PRESSED:
        {
            bool needFlippedX = true;
            if (heroNode->getNeedFlippedX() != needFlippedX) {
                heroNode->setNeedFlippedX(needFlippedX);
                heroNode->getHeroSprite()->setFlippedX(needFlippedX);
            }
            heroNode->setCurState((BaseState *)BaseState::runState);
            heroNode->executeRunAnimation("run", 0.07f);
        }
            break;
            
        case InputType::RIGHT_PRESSED:
        {
            bool needFlippedX = false;
            if (heroNode->getNeedFlippedX() != needFlippedX) {
                heroNode->setNeedFlippedX(needFlippedX);
                heroNode->getHeroSprite()->setFlippedX(needFlippedX);
            }
            heroNode->setCurState((BaseState *)BaseState::runState);
            heroNode->executeRunAnimation("run", 0.07f);
        }
            break;
        default:
            break;
    }
}

void IdleState::updateHero_Map(HeroNode *heroNode, MapNode *mapNode){

}