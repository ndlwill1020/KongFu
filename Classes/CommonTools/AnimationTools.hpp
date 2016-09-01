//
//  AnimationTools.hpp
//  KongFu
//
//  Created by macuser on 16/8/19.
//
//

#ifndef AnimationTools_hpp
#define AnimationTools_hpp

#include "cocos2d.h"
USING_NS_CC;

class AnimationTools {
public:
    //run1,run2   framename = run 不用传动画帧的数量
    static Animate* animationWithFrameName(const char *frameName, int loops, float delay);
    static Animate* animationWithFrameAndNum(const char *frameName, int frameCount, float delay);
};

#endif /* AnimationTools_hpp */
