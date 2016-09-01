//
//  HeroStateNode.hpp
//  KongFu
//
//  Created by macuser on 16/8/24.
//
//

#ifndef HeroStateNode_hpp
#define HeroStateNode_hpp

#include "cocos2d.h"
USING_NS_CC;

class HeroStateNode : public Node{
protected:
    HeroStateNode();
    ~HeroStateNode();
public:
    CREATE_FUNC(HeroStateNode);
    virtual bool init();
private:
    CC_SYNTHESIZE(ProgressTimer *, hpBar, HpBar);
    CC_SYNTHESIZE(ProgressTimer *, mpBar, MpBar);
    //    ProgressTimer *hpBar;
    //    ProgressTimer *mpBar;
};


#endif /* HeroStateNode_hpp */
