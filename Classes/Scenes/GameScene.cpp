//
//  GameScene.cpp
//  KongFu
//
//  Created by macuser on 16/8/24.
//
//

#include "GameScene.hpp"
#include "GlobalDefine.h"
#include "GlobalData.h"
#include "MapNode.hpp"
#include "HeroControlNode.hpp"
#include "HeroNode.hpp"
#include "HeroStateNode.hpp"
#include "PauseScene.hpp"
#include "BaseState.hpp"
#include "MonsterController.hpp"
#include "MonsterNode.hpp"
#include "Enums.h"

#include "FailNode.hpp"
#include "SuccessNode.hpp"


GameScene::GameScene(){

}

GameScene::~GameScene(){

}

Scene* GameScene::createScene(){
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init(){
    if (!Layer::init()) {
        return false;
    }
    
    // 音乐
    if (getBoolFromXML(MUSIC_KEY))
    {
        //float music = getFloatFromXML(MUSICVOL)*100.0f;
        AudioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
        if (AudioEngine->isBackgroundMusicPlaying())
        {
            AudioEngine->pauseBackgroundMusic();
            AudioEngine->playBackgroundMusic("Sound/gameBGM.wav", true);
        }
        else
        {
            AudioEngine->playBackgroundMusic("Sound/gameBGM.wav", true);
        }
        
    }
    else
    {
        AudioEngine->pauseBackgroundMusic();
    }

    // 资源
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pngPlist/mapBefore.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pngPlist/mapRoad.plist");

    // 初始化
    std::string bgName = StringUtils::format("bgmap%d.png", gSelectedLevel);
    std::string midName = StringUtils::format("MapMiddle%d.png", gSelectedLevel);
    std::string groundName = StringUtils::format("MapGround%d.png", gSelectedLevel);
    std::string beforeName = StringUtils::format("MapBefore%d.png", gSelectedLevel);
    
    //Map 背景（不移动）
    auto bgPic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(bgName));
    bgPic->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
    this->addChild(bgPic, 0);
    
    mapNode = MapNode::create();
    mapNode->initMap(midName.c_str(), groundName.c_str(), beforeName.c_str());
    this->addChild(mapNode, 1);
    
    //Hero
    _hero = HeroNode::createWithFileName_Level("idle.png", 1);
    _hero->setPosition(100, 360);//y:360
    this->addChild(_hero, 3);
    
    //ControlNode
    controlNode = HeroControlNode::create();
    controlNode->setHeroNode(_hero);
    this->addChild(controlNode, 2);
    
    //StateNode
    _heroStateNode = HeroStateNode::create();
    this->addChild(_heroStateNode, 1);
    
    
    //pause
    auto pauseItem = MenuItemSprite::create(
                                                Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pauseNormal.png")),
                                                Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pauseSelected.png")),
                                                CC_CALLBACK_1(GameScene::pause_menuCB, this)); // Pause
    
    pauseItem->setPosition(WINSIZE.width - 50, WINSIZE.height - 48);
    
    auto menu = Menu::create(pauseItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    //monsters
    MonsterController *monsters = MonsterController::createWithHeroNode_MapNode(_hero, mapNode);
    
    
    
    scheduleUpdate();
    return true;
}

void GameScene::update(float dt){
    log("GameScene update!!!!!!!!!!!!!!! monsterSize:%ld",curMonsterList.size());
    
    //dead动画播完 才显示FailNode
    if (_hero->getIsDeadEnded() == true) {
        scheduleOnce(schedule_selector(GameScene::gameFail_update), 2.0f);
        unscheduleUpdate();
        return;
    }

    
    if (curMonsterList.size() != 0) {
        for (auto monster : curMonsterList) {//得到的都是没死的monster
            if (_hero->getCurState() == (BaseState *)BaseState::deadState) {
                _heroStateNode->getHpBar()->setPercentage(_hero->getHpPercent());
                log("~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
                break;
            }
            //
            if (monster->getCurState() == MonsterState::ATTACK && _hero->getCurState() != (BaseState *)BaseState::jumpState) {
                _hero->setCurState((BaseState *)BaseState::hurtState);
                log("change hp~~~~~~~~~~~~~~~~");
                _heroStateNode->getHpBar()->setPercentage(_hero->getHpPercent());
            }

        }
    }
    
    
    
    _hero->getCurState()->updateHero_Map(_hero, mapNode);
    
    
    //更新hero_MP
    auto mpBar = _heroStateNode->getMpBar();
    mpBar->setPercentage(_hero->getCurMP());
    if (mpBar->getPercentage() == 100.0f) {
        controlNode->getSkillBg()->setVisible(true);
    } else if (mpBar->getPercentage() < 100.0f) {
        controlNode->getSkillBg()->setVisible(false);
    }
    
    

    
    //
    bool hasMonster = false;
    switch (waveFlag) {
        case 1:
            for (auto monster : curMonsterList) {
                if (monster->getCurState() != MonsterState::DEAD) {
                    hasMonster = true;
                    break;
                } 
            }
            
            if (!hasMonster) {
                curMonsterList.clear();
                for (auto monster : secondWaveMonsterList)
                {
                    monster->setVisible(true);
                    mapNode->addChild(monster);
                    monster->startUpdate(_hero, mapNode);
                    curMonsterList.pushBack(monster);
                }
                waveFlag++;
            }
            break;
        case 2:
            log("=============================================");
            for (auto monster : curMonsterList) {
                if (monster->getCurState() != MonsterState::DEAD) {
                    hasMonster = true;
                    break;
                }
            }
            
            if (!hasMonster) {
                curMonsterList.clear();
                for (auto monster : thirdWaveMonsterList)
                {
                    monster->setVisible(true);
                    mapNode->addChild(monster);
                    monster->startUpdate(_hero, mapNode);
                    curMonsterList.pushBack(monster);
                }
                waveFlag++;
            }
            break;
        case 3:
            log("=============================================");
            for (auto monster : curMonsterList) {
                if (monster->getCurState() != MonsterState::DEAD) {
                    hasMonster = true;
                    break;
                }
            }
            
            log("success!!!!!!!!!!!!!!!");
            if (!hasMonster) {
                scheduleOnce(schedule_selector(GameScene::gameSuccess_update), 1.0f);
                unscheduleUpdate();
            }

            break;
        default:
            break;
    }
}

void GameScene::gameFail_update(float dt){
    auto failNode = FailNode::create();
    this->addChild(failNode, 5);
}

void GameScene::gameSuccess_update(float dt){
    auto successNode = SuccessNode::create();
    this->addChild(successNode, 5);
}

void GameScene::pause_menuCB(Ref *pSender){
    log("pause menuItem clicked!!!!!!");

    
    render = RenderTexture::create(WINSIZE.width, WINSIZE.height);
    render->begin();
    Director::getInstance()->getRunningScene()->visit();
    render->end();
    render->retain();
    
    //3.0 截屏需要在截完屏的下一帧才能处理RenderTexture
    Director::getInstance()->getScheduler()->schedule(CC_CALLBACK_1(GameScene::pushScene_update, this), this, 0.0f, 0, 0.0f, false, "screenshot");
}

void GameScene::pushScene_update(float dt){
    log("push scene!!!!!!");
    Director::getInstance()->pushScene(PauseScene::createScene(render));
}