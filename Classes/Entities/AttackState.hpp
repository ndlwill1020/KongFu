//
//  AttackState.hpp
//  KongFu
//
//  Created by macuser on 16/8/25.
//
//

#ifndef AttackState_hpp
#define AttackState_hpp

class MonsterNode;

#include "BaseState.hpp"
class AttackState : public BaseState{
public:
    AttackState();
    virtual ~AttackState();
    
    virtual void handleInput(HeroNode *heroNode, InputType type);
    virtual void updateHero_Map(HeroNode *heroNode, MapNode *mapNode);
private:
    bool isMonsterAttackedByHero(HeroNode *heroNode, MapNode *mapNode, MonsterNode *monsterNode);
};

#endif /* AttackState_hpp */
