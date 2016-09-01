//
//  HeroControlNode.cpp
//  KongFu
//
//  Created by macuser on 16/8/24.
//
//

#include "HeroControlNode.hpp"
#include "GlobalData.h"
#include "GlobalDefine.h"


#include "HeroNode.hpp"


HeroControlNode::HeroControlNode()
:inputType(InputType::NONE)
{

}

HeroControlNode::~HeroControlNode(){
    
    
}

bool HeroControlNode::init(){
    if (!Node::init()) {
        return false;
    }
    
    SpriteFrame *tempFrame = nullptr;
    //fist
    tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("fist.png");
    auto fist = Scale9Sprite::createWithSpriteFrame(tempFrame);
    auto fistCtlBtn = ControlButton::create(fist);
    fistCtlBtn->setPreferredSize(Sprite::createWithSpriteFrame(tempFrame)->getContentSize());
    
    //foot
    tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("foot.png");
    auto foot = Scale9Sprite::createWithSpriteFrame(tempFrame);
    auto footCtlBtn = ControlButton::create(foot);
    footCtlBtn->setPreferredSize(Sprite::createWithSpriteFrame(tempFrame)->getContentSize());
    
    //jump
    tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("jump.png");
    auto jump = Scale9Sprite::createWithSpriteFrame(tempFrame);
    auto jumpCtlBtn = ControlButton::create(jump);
    jumpCtlBtn->setPreferredSize(Sprite::createWithSpriteFrame(tempFrame)->getContentSize());
    
    //skill
    std::string skillName = StringUtils::format("comboBtn%d.png", gSelectedLevel);
    tempFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(skillName);
    auto skill = Scale9Sprite::createWithSpriteFrame(tempFrame);
    skillCtlBtn = ControlButton::create(skill);
    skillCtlBtn->setPreferredSize(Sprite::createWithSpriteFrame(tempFrame)->getContentSize());
    
    
    
    auto fistBg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("quan.png"));
    auto footBg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("jiao.png"));
    auto jumpBg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tiao.png"));
    skillBg = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tiao.png"));
    
    
    auto fistSize = fistBg->getContentSize();
    fistCtlBtn->setPosition(Vec2(fistSize.width / 2, fistSize.height / 2));
    //(Ref*, EventType)
    fistCtlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(HeroControlNode::fist_controlCB), Control::EventType::TOUCH_UP_INSIDE);
    
    auto footSize = footBg->getContentSize();
    footCtlBtn->setPosition(Vec2(footSize.width / 2, footSize.height / 2));
    footCtlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(HeroControlNode::foot_controlCB), Control::EventType::TOUCH_UP_INSIDE);
    
    auto jumpSize = jumpBg->getContentSize();
    jumpCtlBtn->setPosition(Vec2(jumpSize.width / 2, jumpSize.height / 2));
    jumpCtlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(HeroControlNode::jump_controlCB), Control::EventType::TOUCH_UP_INSIDE);
    
    auto skillSize = skillBg->getContentSize();
    skillCtlBtn->setPosition(Vec2(skillSize.width / 2, skillSize.height / 2));
    skillCtlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(HeroControlNode::skill_controlCB), Control::EventType::TOUCH_UP_INSIDE);
    
    fistBg->addChild(fistCtlBtn);
    footBg->addChild(footCtlBtn);
    jumpBg->addChild(jumpCtlBtn);
    skillBg->addChild(skillCtlBtn);
    
    fistBg->setPosition(WINSIZE.width - 230, 76);
    footBg->setPosition(WINSIZE.width - 73, 76);
    jumpBg->setPosition(WINSIZE.width - 60, 220);
    skillBg->setPosition(WINSIZE.width - 387, 76);
    
    skillBg->setVisible(false);
    
    
    this->addChild(fistBg);
    this->addChild(footBg);
    this->addChild(jumpBg);
    this->addChild(skillBg);
    
    //left-right
    auto leftBg = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("directionNormal.png"));
    auto leftSelectedBg = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("directionSelected.png"));
    auto leftCtlBtn = ControlButton::create(leftBg);
    leftCtlBtn->setBackgroundSpriteForState(leftSelectedBg, Control::State::HIGH_LIGHTED);
    leftCtlBtn->setZoomOnTouchDown(false);
    leftCtlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(HeroControlNode::left_controlCB), Control::EventType::TOUCH_DOWN);
    leftCtlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(HeroControlNode::left_controlCB), Control::EventType::TOUCH_UP_INSIDE);
    leftCtlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(HeroControlNode::left_controlCB), Control::EventType::DRAG_OUTSIDE);
    leftCtlBtn->setPreferredSize(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("directionNormal.png"))->getContentSize());
    
    
    
    auto rightBg = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("directForNor.png"));
    auto rightSelectedBg = Scale9Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("directForSel.png"));
    auto rightCtlBtn = ControlButton::create(rightBg);
    rightCtlBtn->setBackgroundSpriteForState(rightSelectedBg, Control::State::HIGH_LIGHTED);
    rightCtlBtn->setZoomOnTouchDown(false);
    rightCtlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(HeroControlNode::right_controlCB), Control::EventType::TOUCH_DOWN);
    rightCtlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(HeroControlNode::right_controlCB), Control::EventType::TOUCH_UP_INSIDE);
    rightCtlBtn->addTargetWithActionForControlEvents(this, cccontrol_selector(HeroControlNode::right_controlCB), Control::EventType::DRAG_OUTSIDE);
    rightCtlBtn->setPreferredSize(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("directForNor.png"))->getContentSize());
    
    leftCtlBtn->setPosition(117, 70);
    rightCtlBtn->setPosition(304, 70);
    

    this->addChild(leftCtlBtn);
    this->addChild(rightCtlBtn);
    return true;
}

void HeroControlNode::fist_controlCB(Ref* pSender, Control::EventType type){
    log("fist clicked!!!!!!");
    PLAY_BUTTON_EFFECT
    inputType = FIST_CLICKED;
    _hero->handleInput(inputType);
}

void HeroControlNode::foot_controlCB(Ref* pSender, Control::EventType type){
    log("foot clicked!!!!!!");
    PLAY_BUTTON_EFFECT
    inputType = FOOT_CLICKED;
    _hero->handleInput(inputType);
}

void HeroControlNode::jump_controlCB(Ref* pSender, Control::EventType type){
    log("jump clicked!!!!!!");
    if (getBoolFromXML(SOUND_KEY))
    {
        AudioEngine->setEffectsVolume(getFloatFromXML(SOUNDVOL));
        AudioEngine->playEffect("Sound/Jump.wav");
    }
    inputType = JUMP_CLICKED;
    _hero->handleInput(inputType);
}

void HeroControlNode::skill_controlCB(Ref* pSender, Control::EventType type){
    log("skill clicked!!!!!!");
    if (getBoolFromXML(SOUND_KEY))
    {
        AudioEngine->setEffectsVolume(getFloatFromXML(SOUNDVOL));
        AudioEngine->playEffect("Sound/combo.wav");
    }
    inputType = SKILL_CLICKED;
    _hero->handleInput(inputType);
}

void HeroControlNode::left_controlCB(Ref* pSender, Control::EventType type){
    log("left !!!!!!");
    //_hero->setNeedFlippedX(true);
    switch (type) {
        case Control::EventType::TOUCH_DOWN:
            inputType = InputType::LEFT_PRESSED;
            break;
        case Control::EventType::DRAG_OUTSIDE:
            inputType = InputType::LEFT_DARGOUT;
            break;
        case Control::EventType::TOUCH_UP_INSIDE:
            inputType = InputType::LEFT_RELEASED;
            break;
            
        default:
            break;
    }
    _hero->handleInput(inputType);
}

void HeroControlNode::right_controlCB(Ref* pSender, Control::EventType type){
    log("right !!!!!!");
    
    //_hero->setNeedFlippedX(false);
    
    switch (type) {
        case Control::EventType::TOUCH_DOWN:
            inputType = InputType::RIGHT_PRESSED;
            break;
        case Control::EventType::DRAG_OUTSIDE:
            inputType = InputType::RIGHT_DARGOUT;
            break;
        case Control::EventType::TOUCH_UP_INSIDE:
            inputType = InputType::RIGHT_RELEASED;
            break;
            
        default:
            break;
    }

    _hero->handleInput(inputType);
}
