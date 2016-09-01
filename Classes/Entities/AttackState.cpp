//
//  AttackState.cpp
//  KongFu
//
//  Created by macuser on 16/8/25.
//
//

#include "AttackState.hpp"
#include "HeroNode.hpp"
#include "MapNode.hpp"
#include "GlobalData.h"
#include "MonsterNode.hpp"

AttackState::AttackState(){

}

AttackState::~AttackState(){

}

void AttackState::handleInput(HeroNode *heroNode, InputType type){
    switch (type) {
        case InputType::FIST_CLICKED:
            log("curState:attack   execute:fist");
            break;
        case InputType::FOOT_CLICKED:
            log("curState:attack   execute:foot");
            break;
            
        default:
            break;
    }
}

//attack commonRange-150 skillRange-350
void AttackState::updateHero_Map(HeroNode *heroNode, MapNode *mapNode){//逻辑处理
    log("AttackState update!!!!!!!!!!");
    
    for (auto monster : curMonsterList) {
        if (monster->getCurState() != MonsterState::DEAD && isMonsterAttackedByHero(heroNode, mapNode, monster)) {
            float distance = heroNode->getPositionX() - (monster->getPositionX() + mapNode->getPositionX());
            if (heroNode->getIsCrazy()) {//skill attack
                if (fabsf(distance) <= 350) {
                    if (monster->getType() == MonsterType::WOOD_ATTRIBUTE) {
                        monster->executeHurtAnimation("monsterHurt", 0.2f, 1);
                    } else if (monster->getType() == MonsterType::FIRE_ATTRIBUTE) {
                        monster->executeHurtAnimation("lionHurt", 0.2f, 1);
                    } else if (monster->getType() == MonsterType::ROCK_ATTRIBUTE) {
                        monster->executeHurtAnimation("stoneHurt", 0.2f, 1);
                    }
                }
            } else {//common attack
                if (fabsf(distance) <= 150) {
                    if (monster->getType() == MonsterType::WOOD_ATTRIBUTE) {
                        monster->executeHurtAnimation("monsterHurt", 0.2f, 1);
                    } else if (monster->getType() == MonsterType::FIRE_ATTRIBUTE) {
                        monster->executeHurtAnimation("lionHurt", 0.2f, 1);
                    } else if (monster->getType() == MonsterType::ROCK_ATTRIBUTE) {
                        monster->executeHurtAnimation("stoneHurt", 0.2f, 1);
                    }
                }
            }
            
        }
    }
}

//hero attack monster (英雄是否可能攻击到monster)
bool AttackState::isMonsterAttackedByHero(HeroNode *heroNode, MapNode *mapNode, MonsterNode *monsterNode){
    float heroX = heroNode->getPositionX();
    float monsterX = mapNode->getPositionX() + monsterNode->getPositionX();
    
    auto heroDirection = heroNode->getNeedFlippedX();//true-left
    //auto monsterDirection = monsterNode->getNeedFlippedX();//false-left
    
    if (heroDirection) {//hero 向左
        if (monsterX <= heroX) {
            return true;
        }
    } else {
        if (monsterX >= heroX) {
            return true;
        }
    }
    return false;
}