//
//  PauseScene.cpp
//  KongFu
//
//  Created by macuser on 16/8/25.
//
//

#include "PauseScene.hpp"
#include "GlobalDefine.h"
#include "StartScene.hpp"
#include "GameScene.hpp"
#include "GlobalData.h"

PauseScene::PauseScene(){

}

PauseScene::~PauseScene(){

}

Scene* PauseScene::createScene(RenderTexture *rt){
    Scene* scene = Scene::create();
    PauseScene* layer = PauseScene::create();
    
    auto sprite = Sprite::createWithTexture(rt->getSprite()->getTexture());
    sprite->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
    sprite->setFlippedY(true);
    scene->addChild(sprite, -1);
    scene->addChild(layer);
    
    
    return scene;
}

bool PauseScene::init(){
    if (!Layer::init()) {
        return false;
    }
    
    spriteUp = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pauseBG1.png"));
    spriteDown = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("pauseBG2.png"));
    spriteUp->setPosition(WINSIZE.width / 2, WINSIZE.height + spriteUp->getContentSize().height / 2);
    spriteDown->setPosition(WINSIZE.width / 2, - (spriteDown->getContentSize().height / 2));
    this->addChild(spriteUp);
    this->addChild(spriteDown);
    
    
    auto resumeItem = MenuItemSprite::create(
                                             Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("playNormal.png")),
                                             Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("playSelected.png")),
                                             [&](Ref * ref){
                                                 PLAY_BUTTON_EFFECT
                                                 //弹出保存的场景
                                                 auto moveOn = MoveBy::create(0.5f, Point(0, (spriteUp->getContentSize().height)));
                                                 auto moveDown = MoveBy::create(0.5f, Point(0, -spriteDown->getContentSize().height));
                                                 CallFunc* replace = CallFunc::create([](){Director::getInstance()->popScene();});
                                                 Action* resume = Sequence::create(moveOn, replace, NULL);
                                                 spriteDown->runAction(moveDown);
                                                 spriteUp->runAction(resume);
                                             });
    resumeItem->setPosition(spriteUp->getContentSize().width / 2-5, 110.0f);
    
    // 返回游戏主界面
    auto startItem = MenuItemSprite::create(
                                            Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("backNormal.png")),
                                            Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("backSelected.png")),
                                            [](Ref * ref){
                                                PLAY_BUTTON_EFFECT
                                                //弹出保存的场景
                                                Director::getInstance()->replaceScene(StartScene::createScene());
                                            });
    startItem->setPosition(890.0f, 180.0f);
    
    // 重新开始游戏
    auto againItem = MenuItemSprite::create(
                                            Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("againNormal.png")),
                                            Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("againSelected.png")),
                                            [](Ref * ref){
                                                PLAY_BUTTON_EFFECT
                                                //弹出保存的场景
                                                Director::getInstance()->replaceScene(GameScene::createScene());}
                                            );
    againItem->setPosition(346.0f, 180.0f);
    
    // 下一关
    auto nextItem = MenuItemSprite::create(
                                           Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("nextNormal.png")),
                                           Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("nextSelected.png")),
                                           [](Ref * ref){
                                               PLAY_BUTTON_EFFECT
                                               //弹出保存的场景
                                               if (gSelectedLevel++ < 3)
                                               {
                                                   Director::getInstance()->replaceScene(GameScene::createScene());
                                               }
                                           });
    nextItem->setPosition(1053.0f, 180.0f);
    
    // 声音设置按钮
    auto musicOn = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("musicOn.png")),
                                          Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("musicOff.png")));
    auto musicOff = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("musicOff.png")),
                                           Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("musicSelected.png")));
    auto musciToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(PauseScene::musicSetting_menuCB, this), musicOn, musicOff, NULL);
    musciToggle->setPosition(190.0f, 180.0f);
    //log("%d",musciToggle->getSelectedIndex());//0
    
    auto menu = Menu::create(resumeItem, startItem, againItem, nextItem, musciToggle, NULL);
    menu->setPosition(Point::ZERO);
    spriteUp->addChild(menu);
    
    auto moveDown = MoveBy::create(0.6f, Point(0, - (spriteUp->getContentSize().height)));
    auto moveUp = MoveBy::create(0.6f, Point(0, spriteDown->getContentSize().height));
    spriteUp->runAction(moveDown);
    spriteDown->runAction(moveUp);
    return true;
}

void PauseScene::musicSetting_menuCB(Ref* pSender){
    PLAY_BUTTON_EFFECT
    auto musicTemp = (MenuItemToggle*)pSender;
//    if (getBoolFromXML(SOUND_KEY))
//    {
//        AudioEngine->setEffectsVolume(getFloatFromXML(SOUNDVOL));
//        AudioEngine->playEffect("");
//    }
    
    if (musicTemp->getSelectedIndex() == 1)
    {
        AudioEngine->pauseBackgroundMusic();
    }
    else
    {
        AudioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
        AudioEngine->resumeBackgroundMusic();
    }
}
