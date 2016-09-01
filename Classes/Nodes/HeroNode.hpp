//
//  Hero.hpp
//  KongFu
//
//  Created by macuser on 16/8/19.
//
//

#ifndef HeroNode_hpp
#define HeroNode_hpp
#include "cocos2d.h"
#include "Enums.h"
USING_NS_CC;

class BaseState;


/*
 //Hero Model
 struct HeroInfo{
 float totalHP;
 float curHP;
 float totalMP;
 float curMP;
 } info;
 */

//run优先attack

//hurt优先 run，attack

//attack,jump,hurt 不能run
//attack,jump,hurt 不能attack
//run,attack,hurt,jump 不能jump
class HeroNode : public Node{
protected:
    HeroNode();
    ~HeroNode();
public:
    static HeroNode* createWithFileName_Level(const char* fileName, int level);
    virtual bool initWithFileName_Level(const char* fileName, int level);
    
    //virtual void handleInput(BaseInput *input);
    virtual void handleInput(InputType type);
    
    //run
    void executeRunAnimation(const char* eachFileName, float delay);
    //attack
    void executeAttackAnimation(const char* eachFileName, float delay);
    void attackAnimationFinished_ActionCB();
    //jump
    void executeJumpUpAnimation(const char* eachFileName, float delay);
    void executeJumpDownAnimation(const char* eachFileName, float delay);
    //void stopJumpAnimation_resetIdleImage();
    
    //hurt
    void executeHurtAnination(const char* eachFileName, float delay);
    void hurtAnimationFinished_ActionCB();
    //dead
    void executeDeadAnimation(const char* eachFileName, float delay);
    void deadAnimationFinished_ActionCB();
    
    
    //stop & reset
    void stopAnimations_resetIdleImage();
    
    // 判断英雄是否运动到了窗口的中间位置,visibleSize为当前窗口的大小
    bool isReachCenter(Size winSize);
    
    //jump 斜抛运动，到达竖直的速度为0时，达到最高点
    inline float getJumpVelocity(){
        jumpVelocity = jumpVelocity - 0.3f;
        return jumpVelocity;
    };
    
    inline void setJumpVelocity(float velocity){
        this->jumpVelocity = velocity;
    };
    
private:
    
    //Sprite *heroSprite;
    //BaseState* curState;
    //float totalHP;
    //float curHP;
    float totalMP;
    //float curMP;
    
    float jumpVelocity;//跳起速度
    
    //float speed;
    CC_SYNTHESIZE(float, heroSpeed, HeroSpeed);//移动速度
    CC_SYNTHESIZE(Sprite *, heroSprite, HeroSprite);
    CC_SYNTHESIZE(bool, needFlippedX, NeedFlippedX);
    CC_SYNTHESIZE(BaseState *, curState, CurState);
    
    CC_SYNTHESIZE(bool, isCrazy, IsCrazy);
    
    CC_SYNTHESIZE(float, curMP, CurMP);
    CC_SYNTHESIZE(float, curHP, CurHP);
    CC_SYNTHESIZE(float, totalHP, TotalHP);
    CC_SYNTHESIZE(float, hpPercent, HpPercent);
    
    CC_SYNTHESIZE(bool, isDeadEnded, IsDeadEnded);
    bool isExecuteDead;
    bool isExecuteHurt;
    
};

#endif /* HeroNode_hpp */
