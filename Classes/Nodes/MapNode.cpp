//
//  MapNode.cpp
//  KongFu
//
//  Created by macuser on 16/8/24.
//
//

#include "MapNode.hpp"
#include "HeroNode.hpp"
#include "GlobalDefine.h"


MapNode::MapNode(){

}

MapNode::~MapNode(){

}

void MapNode::initMap(const char *topMap,const char *midMap, const char *bottomMap){
    
    
    top = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(topMap));
    mid = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(midMap));
    bottom = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(bottomMap));
    
    top->setAnchorPoint(Point(0, 0));
    mid->setAnchorPoint(Point(0, 0));
    bottom->setAnchorPoint(Point(0, 0));
    //视差节点
    parallaxNode = ParallaxNode::create();
    parallaxNode->addChild(top, 1, Point(1.18, 0), Point(0,360));//移动最慢，（它最远）
    parallaxNode->addChild(mid, 2, Point(1, 0), Point(0,0));
    parallaxNode->addChild(bottom, 3, Point(0.7, 0), Point(0, 0));
    
    //this->setAnchorPoint(Vec2(0, 0));
    this->addChild(parallaxNode);
}

bool MapNode::isReachBorder(HeroNode *heroNode){
    if (heroNode->getNeedFlippedX() == false && this->getPositionX() >= (WINSIZE.width - mid->getContentSize().width)) {//right
        return false;
    } else if (heroNode->getNeedFlippedX() == true && this->getPositionX() <= 0.0f) {//left
        return false;
    } else {//map已经移动到边缘
        return true;
    }
}

void MapNode::moveMap(HeroNode *heroNode){
    //hero移动到中间，map才移动
    if (heroNode->getNeedFlippedX() == false && heroNode->isReachCenter(WINSIZE)) {//right
        if (this->getPositionX() >= (WINSIZE.width - mid->getContentSize().width)) {
            this->setPositionX(this->getPositionX() - heroNode->getHeroSpeed());
        }
    } else if (heroNode->getNeedFlippedX() == true && heroNode->isReachCenter(WINSIZE)) {//left
        if (this->getPositionX() <= 0.0f) {
            this->setPositionX(this->getPositionX() + heroNode->getHeroSpeed());
        }
    }
}
