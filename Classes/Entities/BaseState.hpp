//
//  BaseState.hpp
//  KongFu
//
//  Created by macuser on 16/8/19.
//
//

#ifndef BaseState_hpp
#define BaseState_hpp
#include "Enums.h"

class IdleState;
class AttackState;
class RunState;
class JumpState;
class HurtState;
class DeadState;

//class BaseInput;
class HeroNode;
class MapNode;
//#include "BaseInput.hpp"
//#include "HeroNode.hpp"

class BaseState{
public:
    static IdleState *idleState;
    static AttackState *attackState;
    static RunState *runState;
    static JumpState *jumpState;
    static HurtState *hurtState;
    
    static DeadState *deadState;
    
    
    BaseState(){};
    virtual ~BaseState(){};
    
    virtual void handleInput(HeroNode *heroNode, InputType type){};
    virtual void updateHero_Map(HeroNode *heroNode, MapNode *mapNode){};
    
    //virtual void handleInput(HeroNode *heroNode, BaseInput *input){};
    //virtual void onEnterState(HeroNode *heroNode){};
    //virtual void onExitState(HeroNode *heroNode){};
};

#endif /* BaseState_hpp */
