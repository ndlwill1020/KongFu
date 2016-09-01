//
//  MonsterNode.hpp
//  KongFu
//
//  Created by macuser on 16/8/29.
//
//

#ifndef MonsterNode_hpp
#define MonsterNode_hpp

#include "cocos2d.h"
#include "Enums.h"
USING_NS_CC;

class HeroNode;
class MapNode;


class MonsterNode : public Node{
protected:
    MonsterNode();
    ~MonsterNode();
    
public:
    static MonsterNode* createWithFileName_Level(const char* fileName, int level);
    virtual bool initWithFileName_Level(const char* fileName, int level);
    
    void startUpdate(HeroNode *heroNode, MapNode *mapNode);
    
    void executeHurtAnimation(const char *eachFileName, float delay, int iLoops);
    
    
    //void calcDistance_update(float dt);
    void update(float dt);
private:
    void followHero();
    
    void executeRunAnimation(const char *eachFileName, float delay, int iLoops);
    
    void executeAttackAnimation(const char *eachFileName, float delay, int iLoops);
    void attackAnimationFinished_ActionCB();
    
    
    void hurtAnimationFinished_ActionCB();
    
    void executeDeadAnimation(const char *eachFileName, float delay, int iLoops);
    void deadAnimationFinished_ActionCB();
    void blinkFinished_ActionCB();
    
    void attack_updateOnce(float dt);
private:
    Sprite* monsterSprite;
    int _hp;
    //MonsterState curState;
    CC_SYNTHESIZE(MonsterState, curState, CurState);
    CC_SYNTHESIZE(MonsterType, type, Type);
    CC_SYNTHESIZE(bool, needFlippedX, NeedFlippedX);
    
    HeroNode* heroNode;
    MapNode* mapNode;
    
    
    //ai
    //仇恨范围，跟随hero，攻击判断
    float distanceFromHero;//负 表示hero在左边monster在右边
};

#endif /* MonsterNode_hpp */
