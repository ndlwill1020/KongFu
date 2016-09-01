//
//  BaseInput.hpp
//  KongFu
//
//  Created by macuser on 16/8/25.
//
//

#ifndef BaseInput_hpp
#define BaseInput_hpp
//#include "cocos2d.h"
//#include "extensions/cocos-ext.h"
//USING_NS_CC;
//USING_NS_CC_EXT;

class HeroNode;
//#include "HeroNode.hpp"

class BaseInput{
public:
    BaseInput(){};
    virtual ~BaseInput(){};
    
    virtual void execute(HeroNode *heroNode) = 0;//heroNode->handleInput(this);
    
};
#endif /* BaseInput_hpp */
