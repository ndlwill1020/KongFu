//
//  HurtState.cpp
//  KongFu
//
//  Created by macuser on 16/8/25.
//
//

#include "HurtState.hpp"
#include "HeroNode.hpp"
#include "MapNode.hpp"


HurtState::HurtState(){

}

HurtState::~HurtState(){

}

//hurt优先
void HurtState::handleInput(HeroNode *heroNode, InputType type){
    switch (type) {
        case InputType::FIST_CLICKED:
            //DO NOTHING
            break;
        case InputType::FOOT_CLICKED:
            //DO NOTHING
            break;
        case InputType::LEFT_PRESSED:
            //run 优先 hurt
//            heroNode->stopAnimations_resetIdleImage();
//            heroNode->setCurState((BaseState *)BaseState::runState);
            break;
        case InputType::RIGHT_PRESSED:
            
            break;
            
        default:
            break;
    }
}

void HurtState::updateHero_Map(HeroNode *heroNode, MapNode *mapNode){
    log("HurtState update!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    
    //如果hero attack，被hurt 停止attack，执行hurt
    //heroNode->stopAnimations_resetIdleImage();
    heroNode->executeHurtAnination("hurt", 0.2f);
}