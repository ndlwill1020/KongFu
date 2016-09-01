//
//  HurtState.hpp
//  KongFu
//
//  Created by macuser on 16/8/25.
//
//

#ifndef HurtState_hpp
#define HurtState_hpp

#include "BaseState.hpp"
class HurtState : public BaseState{
public:
    HurtState();
    virtual ~HurtState();
    
    virtual void handleInput(HeroNode *heroNode, InputType type);
    virtual void updateHero_Map(HeroNode *heroNode, MapNode *mapNode);
};

#endif /* HurtState_hpp */
