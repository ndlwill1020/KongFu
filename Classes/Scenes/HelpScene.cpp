//
//  HelpScene.cpp
//  KongFu
//
//  Created by macuser on 16/8/23.
//
//

#include "HelpScene.hpp"
#include "GlobalDefine.h"
#include "StartScene.hpp"

HelpScene::HelpScene(){

}

HelpScene::~HelpScene(){

}

Scene* HelpScene::createScene(){
    auto scene = Scene::create();
    auto layer = HelpScene::create();
    scene->addChild(layer);
    return scene;
}

bool HelpScene::init(){
    if (!Layer::init()) {
        return false;
    }
    
    auto bgSprite = Sprite::create("Help.png");
    bgSprite->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
    this->addChild(bgSprite);
    
    auto closeItem = MenuItemSprite::create(
                                            Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("GalleryOffNormal.png")),
                                            Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("GalleryOffSelected.png")),
                                            [&](Ref * ref){
                                                PLAY_BUTTON_EFFECT
                                                //弹出场景
                                                Director::getInstance()->replaceScene(StartScene::createScene());
                                            });
    // 关闭按钮
    closeItem->setPosition(WINSIZE.width / 2 + 580, WINSIZE.height / 2 + 320);
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
    auto titleSp = Sprite::create("TitleLogo.png");
    titleSp->setPosition(WINSIZE.width / 2 + 200, WINSIZE.height / 2);
    this->addChild(titleSp);
    
    // 创建文字Label
    text = Label::createWithTTF("KONGFU!\nwwwwwwwwwwwwwwww\nThank You!", "fonts/Marker Felt.ttf", 23);
    text->setColor(Color3B(0, 255, 255));
    //text->setColor(Color3B::RED);
    //text->setTag(15);
    text->setPosition(250, 100);
    
    // 绘制裁剪区域
    DrawNode* area = DrawNode::create();
    Point point[4] = { Point(50, 100), Point(500, 100), Point(500, 450), Point(50, 450) };
    area->drawPolygon(point, 4, Color4F(255, 255, 255, 255), 0, Color4F(255, 255, 255, 255));
    
    // 创建遮罩层
    ClippingNode* m_pClipArea = ClippingNode::create();
    m_pClipArea->setInverted(false);//
    m_pClipArea->setStencil(area);
    m_pClipArea->addChild(text);
    this->addChild(m_pClipArea);
    
    MoveBy* moveact = MoveBy::create(5.0f, Point(0, 400));
    CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(HelpScene::resetPosition_ActionCB, this));

    
    text->runAction(RepeatForever::create(Sequence::create(moveact, callFunc, NULL)));
    
    return true;
}

void HelpScene::resetPosition_ActionCB(){
    text->setPosition(250, 100);
}