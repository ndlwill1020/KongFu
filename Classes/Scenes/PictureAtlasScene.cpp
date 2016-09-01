//
//  PictureAtlasScene.cpp
//  KongFu
//
//  Created by macuser on 16/8/23.
//
//

#include "PictureAtlasScene.hpp"
#include "GlobalDefine.h"
#include "StartScene.hpp"

PictureAtlasScene::PictureAtlasScene()
:selectedIndex(-1)
{

}

PictureAtlasScene::~PictureAtlasScene(){

}

Scene* PictureAtlasScene::createScene(){
    auto scene = Scene::create();
    auto layer = PictureAtlasScene::create();
    scene->addChild(layer);
    return scene;
}

bool PictureAtlasScene::init(){
    if (!Layer::init()) {
        return false;
    }
    
    auto bgSprite = Sprite::create("PhotoGalleryBackground.png");
    bgSprite->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
    this->addChild(bgSprite);
    
    auto closeItem = MenuItemSprite::create(
                                            Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("GalleryOffNormal.png")),
                                            Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("GalleryOffSelected.png")),
                                            [](Ref * ref){
                                                PLAY_BUTTON_EFFECT
                                                //弹出场景
                                                Director::getInstance()->replaceScene(StartScene::createScene());
                                            });
    // 关闭按钮
    closeItem->setPosition(WINSIZE.width/2+580, WINSIZE.height/2+320);
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    bgSprite->addChild(menu);
    
    // 怪物图鉴
    m_pMZ_Pic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ManWood.png"));
    m_pMZ_Txt = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Text.png"));
    m_pMZLabel = LabelTTF::create("木\n桩\n怪", "", 30);
    m_pMZLabel->setColor(Color3B(0, 255, 255));
    
    m_pLion_Pic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ManLion.png"));
    m_pLionLabel = LabelTTF::create("狮\n子\n怪", "", 30);
    m_pLionLabel->setColor(Color3B(0, 255, 255));
    
    m_pStone_Pic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ManStone.png"));
    m_pStoneLabel = LabelTTF::create("石\n头\n怪", "", 30);
    m_pStoneLabel->setColor(Color3B(0, 255, 255));
    
    m_pMZ_Pic->setPosition(WINSIZE.width / 2 + 50, WINSIZE.height / 2);
    m_pMZ_Pic->setVisible(true);
    m_pMZ_Txt->setPosition(WINSIZE.width / 2 + 460, WINSIZE.height / 2 );
    m_pMZ_Txt->setVisible(true);
    m_pMZLabel->setPosition(WINSIZE.width / 2 + 265, WINSIZE.height / 2 - 120);
    m_pMZLabel->setVisible(true);
    
    m_pLion_Pic->setPosition(WINSIZE.width / 2+50, WINSIZE.height / 2);
    m_pLion_Pic->setVisible(false);
    m_pLionLabel->setPosition(WINSIZE.width / 2 + 265, WINSIZE.height / 2 - 120);
    m_pLionLabel->setVisible(false);
    
    m_pStone_Pic->setPosition(WINSIZE.width / 2 , WINSIZE.height / 2 );
    m_pStone_Pic->setVisible(false);
    m_pStoneLabel->setPosition(WINSIZE.width / 2 + 265, WINSIZE.height / 2 - 120);
    m_pStoneLabel->setVisible(false);
    
    bgSprite->addChild(m_pMZ_Pic);
    bgSprite->addChild(m_pMZ_Txt);
    bgSprite->addChild(m_pMZLabel);
    bgSprite->addChild(m_pLion_Pic);
    bgSprite->addChild(m_pLionLabel);
    bgSprite->addChild(m_pStone_Pic);
    bgSprite->addChild(m_pStoneLabel);
    
    
    
    //ListView
    listView = ListView::create();
    listView->setDirection(ui::ScrollView::Direction::VERTICAL);
    listView->setTouchEnabled(true);
    listView->setBounceEnabled(true);  // 反弹
    listView->setSize(Size(445, 500));
    //when you set _ignoreSize to true, no matther you call setContentSize or not,
    //the widget size is always equal to the return value of the member function getVirtualRendererSize
    listView->ignoreContentAdaptWithSize(false);
    listView->setAnchorPoint(Point(0.0, 0.0));
    listView->setPosition(Point(0, WINSIZE.height / 4));
    listView->addEventListener(CC_CALLBACK_2(PictureAtlasScene::listView_CB,  this));
    bgSprite->addChild(listView);
    
    Button* default_button = Button::create("Cell_0.png", "CellSel_0.png", "", Widget::TextureResType::PLIST);
    log("%f %f",default_button->getContentSize().width, default_button->getContentSize().height);
    default_button->setName("Title Button");
    Layout* default_item = Layout::create();
    default_item->setTouchEnabled(true);
    default_item->setSize(default_button->getSize());
    default_button->setPosition(Vec2(default_item->getSize().width / 2.0f,
                                      default_item->getSize().height / 2.0f));
    default_item->addChild(default_button);
    
    // set model 将创建的模板设置为项目模板
    listView->setItemModel(default_item);
    
    
    // 1
    Button* custom_buttonMZ = Button::create("CellSel_0.png", "Cell_0.png", "", Widget::TextureResType::PLIST);
    custom_buttonMZ->setName("one Button");
    custom_buttonMZ->addTouchEventListener(CC_CALLBACK_2(PictureAtlasScene::button_callback, this));
    custom_buttonMZ->setScale9Enabled(true);
    custom_buttonMZ->setSize(default_button->getSize());
    Layout *custom_itemMZ = Layout::create();
    custom_itemMZ->setSize(custom_buttonMZ->getSize());
    custom_buttonMZ->setPosition(Point(custom_itemMZ->getSize().width / 2.0f, custom_itemMZ->getSize().height / 2.0f));
    custom_itemMZ->addChild(custom_buttonMZ);
    
    // 2
    Button* custom_buttonLion = Button::create("CellSel_1.png", "Cell_1.png", "", Widget::TextureResType::PLIST);
    custom_buttonLion->setName("two Button");
    custom_buttonLion->setScale9Enabled(true);
    custom_buttonLion->setSize(default_button->getSize());
    Layout *custom_itemLion = Layout::create();
    custom_itemLion->setSize(custom_buttonLion->getSize());
    custom_buttonLion->setPosition(Point(custom_itemLion->getSize().width / 2.0f, custom_itemLion->getSize().height / 2.0f));
    custom_itemLion->addChild(custom_buttonLion);
    
    // 3
    Button* custom_buttonStone = Button::create("CellSel_2.png", "Cell_2.png", "", Widget::TextureResType::PLIST);
    custom_buttonStone->setName("three Button");
    custom_buttonStone->setScale9Enabled(true);
    custom_buttonStone->setSize(default_button->getSize());
    Layout *custom_itemStone = Layout::create();
    custom_itemStone->setSize(custom_buttonStone->getSize());
    custom_buttonStone->setPosition(Point(custom_itemStone->getSize().width / 2.0f, custom_itemStone->getSize().height / 2.0f));
    custom_itemStone->addChild(custom_buttonStone);
    
    // 4
    Button* custom_buttonWood = Button::create("CellSel_3.png", "Cell_3.png", "", Widget::TextureResType::PLIST);
    custom_buttonWood->setName("four Button");
    custom_buttonWood->setScale9Enabled(true);
    custom_buttonWood->setSize(default_button->getSize());
    Layout *custom_itemWood = Layout::create();
    custom_itemWood->setSize(custom_buttonWood->getSize());
    custom_buttonWood->setPosition(Point(custom_itemWood->getSize().width / 2.0f, custom_itemWood->getSize().height / 2.0f));
    custom_itemWood->addChild(custom_buttonWood);
    
    
    listView->pushBackCustomItem(custom_itemMZ);
    listView->pushBackCustomItem(custom_itemLion);
    listView->pushBackCustomItem(custom_itemStone);
    listView->pushBackCustomItem(custom_itemWood);
    
    return true;
}

void PictureAtlasScene::listView_CB(Ref* pSender, ListView::EventType type){
    log("ListView callback!!!!!!!!!!!");
    ListView* listView = static_cast<ListView*>(pSender);
    //CC_UNUSED_PARAM(listView);

    
    selectedIndex = listView->getCurSelectedIndex();
    
    switch (selectedIndex)
    {
        case 0:
            m_pMZ_Pic->setVisible(true);
            m_pMZ_Txt->setVisible(true);
            m_pMZLabel->setVisible(true);
            m_pLion_Pic->setVisible(false);
            m_pLionLabel->setVisible(false);
            m_pStone_Pic->setVisible(false);
            m_pStoneLabel->setVisible(false);
            break;
        case 1:
            m_pMZ_Pic->setVisible(false);
            m_pMZLabel->setVisible(false);
            m_pMZ_Txt->setVisible(false);
            m_pLionLabel->setVisible(true);
            m_pLion_Pic->setVisible(true);
            m_pStoneLabel->setVisible(false);
            m_pStone_Pic->setVisible(false);
            break;
        case 2:
            m_pMZ_Pic->setVisible(false);
            m_pMZ_Txt->setVisible(false);
            m_pMZLabel->setVisible(false);
            m_pLion_Pic->setVisible(false);
            m_pLionLabel->setVisible(false);
            m_pStone_Pic->setVisible(true);
            m_pStoneLabel->setVisible(true);
            break;
        case 3:
            m_pMZ_Pic->setVisible(false);
            m_pMZ_Txt->setVisible(false);
            m_pLion_Pic->setVisible(false);
            m_pStone_Pic->setVisible(false);
            m_pLionLabel->setVisible(false);
            m_pStoneLabel->setVisible(false);
            m_pMZLabel->setVisible(false);
            break;
        default:
            break;
    }
}

void PictureAtlasScene::button_callback(Ref* pSender, Widget::TouchEventType type){
    log("button callback!!!!!!!!!!!!!");
    
}