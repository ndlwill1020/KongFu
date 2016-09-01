//
//  IdleState.hpp
//  KongFu
//
//  Created by macuser on 16/8/25.
//
//

#ifndef IdleState_hpp
#define IdleState_hpp

#include "BaseState.hpp"
class IdleState : public BaseState{
public:
    IdleState();
    virtual ~IdleState();
    
    virtual void handleInput(HeroNode *heroNode, InputType type);
    virtual void updateHero_Map(HeroNode *heroNode, MapNode *mapNode);
    //virtual void handleInput(HeroNode *heroNode, BaseInput *input);
};

#endif /* IdleState_hpp */
