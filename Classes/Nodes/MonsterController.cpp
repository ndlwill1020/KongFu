//
//  MonsterControllerNode.cpp
//  KongFu
//
//  Created by macuser on 16/8/29.
//
//

#include "MonsterController.hpp"
#include "GlobalData.h"
#include "HeroNode.hpp"
#include "MapNode.hpp"
#include "MonsterNode.hpp"

MonsterController::MonsterController(){

}

MonsterController::~MonsterController(){

}

MonsterController* MonsterController::createWithHeroNode_MapNode(HeroNode* heroNode, MapNode *mapNode){
    auto ret = new MonsterController();
    if (ret && ret->initWithHeroNode_MapNode(heroNode, mapNode)) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool MonsterController::initWithHeroNode_MapNode(HeroNode* heroNode, MapNode *mapNode){
    this->heroNode = heroNode;
    this->mapNode = mapNode;
    
    curMonsterList.clear();
    secondWaveMonsterList.clear();
    thirdWaveMonsterList.clear();
    
    //mapNode addChild monster
    auto first = MonsterNode::createWithFileName_Level("monsterWalk5.png", 1);
    first->setType(MonsterType::WOOD_ATTRIBUTE);
    first->setVisible(true);
    first->setPosition(1100, 365);
    first->startUpdate(heroNode, mapNode);
    mapNode->addChild(first);
    
    curMonsterList.pushBack(first);
    waveFlag = 1;
    
    //second
    auto second1 = MonsterNode::createWithFileName_Level("monsterWalk5.png", 1);
    second1->setType(MonsterType::WOOD_ATTRIBUTE);
    second1->setVisible(false);
    second1->setPosition(2000, 365);
    secondWaveMonsterList.pushBack(second1);
    
    auto second2 = MonsterNode::createWithFileName_Level("monsterWalk5.png", 1);
    second2->setType(MonsterType::WOOD_ATTRIBUTE);
    second2->setVisible(false);
    second2->setPosition(-150, 365);
    secondWaveMonsterList.pushBack(second2);
    
    //third
    for (int i = 0; i < 3; i++)
    {
        auto third = MonsterNode::createWithFileName_Level("monsterWalk5.png", 1);
        third->setType(MonsterType::WOOD_ATTRIBUTE);
        if (i == 0 || i == 1)
        {
            third->setPosition(-100 * i, 365);
        }
        else
        {
            third->setPosition(2000, 365);
        }
        third->setVisible(false);
        thirdWaveMonsterList.pushBack(third);
    }
    
    return true;
}

