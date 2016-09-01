//
//  DeadState.hpp
//  KongFu
//
//  Created by macuser on 16/8/26.
//
//

#ifndef DeadState_hpp
#define DeadState_hpp
//bu需要
#include "BaseState.hpp"
class DeadState : public BaseState{
public:
    DeadState();
    virtual ~DeadState();
    
    virtual void handleInput(HeroNode *heroNode, InputType type);
    virtual void updateHero_Map(HeroNode *heroNode, MapNode *mapNode);
private:
    
};

#endif /* DeadState_hpp */
