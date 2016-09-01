//
//  DeadState.cpp
//  KongFu
//
//  Created by macuser on 16/8/26.
//
//

#include "DeadState.hpp"
#include "HeroNode.hpp"
#include "MapNode.hpp"

DeadState::DeadState(){

}

DeadState::~DeadState(){

}

void DeadState::handleInput(HeroNode *heroNode, InputType type){

}

void DeadState::updateHero_Map(HeroNode *heroNode, MapNode *mapNode){
    log("DeadState update!!!!!!!!!!");
    heroNode->executeDeadAnimation("dead", 0.2f);
}