//
//  HeroControlNode.hpp
//  KongFu
//
//  Created by macuser on 16/8/24.
//
//

#ifndef HeroControlNode_hpp
#define HeroControlNode_hpp
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "Enums.h"
USING_NS_CC;
USING_NS_CC_EXT;

class HeroNode;

//input handler
class HeroControlNode : public Node{
protected:
    HeroControlNode();
    ~HeroControlNode();
private:
    void fist_controlCB(Ref* pSender, Control::EventType type);
    void foot_controlCB(Ref* pSender, Control::EventType type);
    void jump_controlCB(Ref* pSender, Control::EventType type);
    void skill_controlCB(Ref* pSender, Control::EventType type);
    
    void left_controlCB(Ref* pSender, Control::EventType type);
    void right_controlCB(Ref* pSender, Control::EventType type);
public:
    CREATE_FUNC(HeroControlNode);
    virtual bool init();
    
    inline void setHeroNode(HeroNode* hero){
        this->_hero = hero;
    };
private:
    ControlButton *skillCtlBtn;
    //Sprite *skillBg;
    CC_SYNTHESIZE(Sprite *, skillBg, SkillBg);
    HeroNode* _hero;
    
    
    InputType inputType;
};
#endif /* HeroControlNode_hpp */
