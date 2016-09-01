//
//  RunState.hpp
//  KongFu
//
//  Created by macuser on 16/8/25.
//
//

#ifndef RunState_hpp
#define RunState_hpp

#include "BaseState.hpp"
class RunState : public BaseState{
public:
    RunState();
    virtual ~RunState();
    
    virtual void handleInput(HeroNode *heroNode, InputType type);
    virtual void updateHero_Map(HeroNode *heroNode, MapNode *mapNode);
};

#endif /* RunState_hpp */
