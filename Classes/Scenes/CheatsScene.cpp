//
//  CheatsScene.cpp
//  KongFu
//
//  Created by macuser on 16/8/23.
//
//

#include "CheatsScene.hpp"
#include "GlobalDefine.h"
#include "StartScene.hpp"

CheatsScene::CheatsScene(){

}

CheatsScene::~CheatsScene(){

}

Scene* CheatsScene::createScene(){
    auto scene = Scene::create();
    auto layer = CheatsScene::create();
    scene->addChild(layer);
    return scene;
}

bool CheatsScene::init(){
    if (!Layer::init()) {
        return false;
    }
    flag = true;
    auto spriteBG = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CheatsBackground.png"));
    spriteBG->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
    this->addChild(spriteBG);
    
    // 秘籍技能界面
    interface_1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CheatsInterface1.png"));
    interface_2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("CheatsInterface2.png"));
    interface_1->setPosition(WINSIZE.width / 2, WINSIZE.height / 2 - 10);
    interface_1->setVisible(true);
    interface_2->setPosition(WINSIZE.width / 2, WINSIZE.height / 2 - 10);
    interface_2->setVisible(false);
    spriteBG->addChild(interface_1);
    spriteBG->addChild(interface_2);
    
    // 关闭按钮
    auto closeItem = MenuItemSprite::create(
                                            Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("OffNormal.png")),
                                            Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("offSelected.png")),
                                            [](Ref * ref){
                                                // 切换主界面场景
                                                PLAY_BUTTON_EFFECT
                                                Director::getInstance()->replaceScene(StartScene::createScene()); });
    closeItem->setPosition(WINSIZE.width - 164, WINSIZE.height - 132);
    
    // 点击切换按钮
    auto nextRightItem = MenuItemSprite::create(
                                                Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PageTurnNormal.png")),
                                                Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PageTurnSelected.png")),
                                                //CC_CALLBACK_1(CheatsScene::right_menuCB, this)
                                                [&](Ref * ref){
                                                    PLAY_BUTTON_EFFECT
                                                    // 切换秘籍
                                                    if (flag)
                                                    {
                                                        log("true!!!!!!");
                                                        interface_2->setVisible(true);
                                                        flag = false;
                                                    }
                                                    else
                                                    {
                                                        log("false!!!!!!");
                                                        interface_2->setVisible(false);
                                                        flag = true;
                                                    }
                                                }
                                                );
    nextRightItem->setPosition(WINSIZE.width - 55, WINSIZE.height / 2 - 14);
    
    // 点击切换按钮
    auto nor = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PageTurnNormal.png"));
    nor->setFlippedX(true);
    auto sel = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("PageTurnSelected.png"));
    sel->setFlippedX(true);
    auto nextLeftItem = MenuItemSprite::create(nor, sel, CC_CALLBACK_1(CheatsScene::left_menuCB, this)
//                                               [&](Ref * ref){
//                                                   PLAY_BUTTON_EFFECT
//                                                   // 切换秘籍
//                                                   if (flag)
//                                                   {
//                                                       interface_2->setVisible(true);
//                                                       flag = false;
//                                                   }
//                                                   else
//                                                   {
//                                                       interface_2->setVisible(false);
//                                                       flag = true;
//                                                   }
//                                               }
                                               );
    nextLeftItem->setPosition(55, WINSIZE.height / 2 - 14);
    
    auto menu = Menu::create(closeItem, nextRightItem, nextLeftItem, NULL);
    menu->setPosition(Point::ZERO);
    
    spriteBG->addChild(menu);
    
    
    
    return true;
}

void CheatsScene::right_menuCB(Ref* pSender){
    PLAY_BUTTON_EFFECT
    // 切换秘籍
    if (flag)
    {
        log("true!!!!!!");
        interface_2->setVisible(true);
        flag = false;
    }
    else
    {
        log("false!!!!!!");
        interface_2->setVisible(false);
        flag = true;
    }
}
void CheatsScene::left_menuCB(Ref* pSender){
    PLAY_BUTTON_EFFECT
    // 切换秘籍
    if (flag)
    {
        interface_2->setVisible(true);
        flag = false;
    }
    else
    {
        interface_2->setVisible(false);
        flag = true;
    }
}
