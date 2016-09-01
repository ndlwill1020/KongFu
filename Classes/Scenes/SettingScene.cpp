//
//  SettingScene.cpp
//  KongFu
//
//  Created by macuser on 16/8/23.
//
//

#include "SettingScene.hpp"
#include "GlobalDefine.h"
#include "StartScene.hpp"


SettingScene::SettingScene(){

}

SettingScene::~SettingScene(){

}

Scene* SettingScene::createScene(){
    auto scene = Scene::create();
    auto layer = SettingScene::create();
    scene->addChild(layer);
    return scene;
}

bool SettingScene::init(){
    if (!Layer::init()) {
        return false;
    }
    
    float music = getFloatFromXML(MUSICVOL) * 100.0f;
    float effect = getFloatFromXML(SOUNDVOL) * 100.0f;
    
    auto BG = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("image-0.png"));
    BG->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
    
    auto bgInterface = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("BGPicSet.png"));
    bgInterface->setPosition(WINSIZE.width / 2 + 50, WINSIZE.height / 2);
    
    auto closeBtn = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("closeSetNormal.png")),
                                           Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("closeSetSelected.png")), CC_CALLBACK_1(SettingScene::close_menuCB, this));
    closeBtn->setPosition(WINSIZE.width - 150, WINSIZE.height - 100);
    
    
    auto saveBtn = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("SaveSettings.png")),
                                          Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("SaveSettings.png")), CC_CALLBACK_1(SettingScene::save_menuCB, this));
    saveBtn->setPosition(WINSIZE.width/2+40, WINSIZE.height / 2 - 190);
    
    
    auto musicOn = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("unchecked.png")),
                                          Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("unchecked.png")));
    auto musicOff = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Hook.png")),
                                           Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Hook.png")));
    
    auto effectOn = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("unchecked.png")),
                                           Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("unchecked.png")));
    auto effectOff = MenuItemSprite::create(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Hook.png")),
                                            Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Hook.png")));
    
    auto musicToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingScene::musicToggle_menuCB, this), musicOn, musicOff, NULL);
    musicToggle->setPosition(369.5, 457);
    
    auto effectToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(SettingScene::effectToggle_menuCB, this), effectOn, effectOff, NULL);
    effectToggle->setPosition(369.5, 357);
    
    
    if (getBoolFromXML(MUSIC_KEY))
    {
        musicToggle->setSelectedIndex(1);
    }
    else
    {
        musicToggle->setSelectedIndex(0);
    }
    
    if (getBoolFromXML(SOUND_KEY))
    {
        effectToggle->setSelectedIndex(1);
    }
    else
    {
        effectToggle->setSelectedIndex(0);
    }
    
    auto menu = Menu::create(closeBtn, saveBtn, musicToggle, effectToggle, NULL);
    menu->setPosition(Point::ZERO);
    
    //ui::Slider
    auto musicSlider = Slider::create();
    musicSlider->loadBarTexture("bgBar.png", Widget::TextureResType::PLIST);
    musicSlider->loadProgressBarTexture("progressBar.png", Widget::TextureResType::PLIST);
    musicSlider->loadSlidBallTextureNormal("ThumbBtn.png", Widget::TextureResType::PLIST);
    musicSlider->loadSlidBallTexturePressed("ThumbBtn.png", Widget::TextureResType::PLIST);
    musicSlider->addEventListener(CC_CALLBACK_2(SettingScene::musicVol_sliderCB, this));
    musicSlider->setPosition(Vec2(800, 457));
    musicSlider->setPercent((int)music);
    
    auto effectSlider = Slider::create();
    effectSlider->loadBarTexture("bgBar.png", Widget::TextureResType::PLIST);
    effectSlider->loadProgressBarTexture("progressBar.png", Widget::TextureResType::PLIST);
    effectSlider->loadSlidBallTextureNormal("ThumbBtn.png", Widget::TextureResType::PLIST);
    effectSlider->loadSlidBallTexturePressed("ThumbBtn.png", Widget::TextureResType::PLIST);
    effectSlider->addEventListener(CC_CALLBACK_2(SettingScene::effectVol_sliderCB, this));
    effectSlider->setPosition(Vec2(800, 357));
    effectSlider->setPercent((int)effect);

    
    
    
    //ControlSlider
//    auto musicSlider = ControlSlider::create(
//                                             Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bgBar.png")),
//                                             Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("progressBar.png")),
//                                             Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ThumbBtn.png")));
//    musicSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(SettingScene::changeMusicVol), Control::EventType::VALUE_CHANGED);
//    
//    auto effectSlider = ControlSlider::create(
//                                              Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bgBar.png")),
//                                              Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("progressBar.png")),
//                                              Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("ThumbBtn.png")));
//    effectSlider->addTargetWithActionForControlEvents(this, cccontrol_selector(SettingScene::changeEffectVol), Control::EventType::VALUE_CHANGED);
//    
//    musicSlider->setPosition(800, 457);
//    musicSlider->setMinimumValue(0.0f);
//    musicSlider->setMaximumValue(100.0f);
//    musicSlider->setMinimumAllowedValue(0.0f);
//    musicSlider->setMaximumAllowedValue(100.0f);
//    musicSlider->setValue(music);
//    effectSlider->setPosition(800, 357);
//    effectSlider->setMinimumValue(0.0f);
//    effectSlider->setMaximumValue(100.0f);
//    effectSlider->setMinimumAllowedValue(0.0f);
//    effectSlider->setMaximumAllowedValue(100.0f);
//    effectSlider->setValue(effect);
    
    
    this->addChild(BG);
    this->addChild(bgInterface);
    this->addChild(musicSlider);
    this->addChild(effectSlider);
    this->addChild(menu);
    
    
    
    return true;
}

void SettingScene::close_menuCB(Ref* pSender){
    PLAY_BUTTON_EFFECT
    Director::getInstance()->replaceScene(StartScene::createScene());
}

void SettingScene::save_menuCB(Ref* pSender){
    PLAY_BUTTON_EFFECT
    Director::getInstance()->replaceScene(StartScene::createScene());
}

void SettingScene::musicToggle_menuCB(Ref* pSender){
    PLAY_BUTTON_EFFECT
    auto musicTemp = (MenuItemToggle*)pSender;
    if (musicTemp->getSelectedIndex() == 0)//从1-0 关闭
    {
        setBoolToXML(MUSIC_KEY, false);
        UserDefault::getInstance()->flush();
        AudioEngine->pauseBackgroundMusic();
    }
    else
    {
        setBoolToXML(MUSIC_KEY, true);
        UserDefault::getInstance()->flush();
        AudioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
        AudioEngine->resumeBackgroundMusic();
    }
}

void SettingScene::effectToggle_menuCB(Ref* pSender){
    PLAY_BUTTON_EFFECT
    auto effectTemp = (MenuItemToggle*)pSender;
    if (effectTemp->getSelectedIndex() == 0)
    {
        setBoolToXML(SOUND_KEY, false);
        UserDefault::getInstance()->flush();
    }
    else
    {
        setBoolToXML(SOUND_KEY, true);
        UserDefault::getInstance()->flush();
    }
}

void SettingScene::changeMusicVol(Ref* pSender, Control::EventType type){
    auto temp = (ControlSlider*)pSender;
    setFloatToXML(MUSICVOL, temp->getValue() / 100.0f);
    UserDefault::getInstance()->flush();
    AudioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
}

void SettingScene::changeEffectVol(Ref* pSender, Control::EventType type){
    auto temp = (ControlSlider*)pSender;
    setFloatToXML(SOUNDVOL, temp->getValue() / 100.0f);
    UserDefault::getInstance()->flush();
    AudioEngine->setEffectsVolume(getFloatFromXML(SOUNDVOL));
}

void SettingScene::musicVol_sliderCB(Ref* pSender, Slider::EventType type){
    auto temp = (Slider*)pSender;
    setFloatToXML(MUSICVOL, temp->getPercent() / 100.0f);//getPercent() 1-100
    UserDefault::getInstance()->flush();
    AudioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
}

void SettingScene::effectVol_sliderCB(Ref* pSender, Slider::EventType type){
    auto temp = (Slider*)pSender;
    setFloatToXML(SOUNDVOL, temp->getPercent() / 100.0f);
    UserDefault::getInstance()->flush();
    AudioEngine->setEffectsVolume(getFloatFromXML(SOUNDVOL));
}