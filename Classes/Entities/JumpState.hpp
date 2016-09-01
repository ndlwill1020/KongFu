//
//  JumpState.hpp
//  KongFu
//
//  Created by macuser on 16/8/25.
//
//

#ifndef JumpState_hpp
#define JumpState_hpp

#include "BaseState.hpp"
class JumpState : public BaseState{
public:
    JumpState();
    virtual ~JumpState();
    
    virtual void handleInput(HeroNode *heroNode, InputType type);
    virtual void updateHero_Map(HeroNode *heroNode, MapNode *mapNode);
};

#endif /* JumpState_hpp */
