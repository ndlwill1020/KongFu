//
//  AnimationTools.cpp
//  KongFu
//
//  Created by macuser on 16/8/19.
//
//

#include "AnimationTools.hpp"

Animate* AnimationTools::animationWithFrameName(const char *frameName, int loops, float delay)
{
    SpriteFrame* frame = nullptr;
    Animation* animation = Animation::create();
    int index = 1;
    do
    {
        //log("animation count!!!!!");
        std::string actualName = StringUtils::format("%s%d.png", frameName, index++);
        log("fileName:%s", actualName.c_str());
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(actualName);
        if (frame == nullptr)
        {
            break;
        }
        animation->addSpriteFrame(frame);
    } while (true);
    animation->setDelayPerUnit(delay);
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(loops);
    Animate* animate = Animate::create(animation);
    return animate;
}

Animate* AnimationTools::animationWithFrameAndNum(const char *frameName, int frameCount, float delay)
{
    SpriteFrame* frame = nullptr;
    Animation* animation = Animation::create();
    for (int index = 1; index <= frameCount; index++)
    {
        std::string actualName = StringUtils::format("%s%d.png", frameName, index++);
        frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(actualName);
        animation->addSpriteFrame(frame);
    }
    animation->setDelayPerUnit(delay);
    animation->setRestoreOriginalFrame(true);
    Animate* animate = Animate::create(animation);
    
    /*
     Vector<SpriteFrame *> animFrames;
     char str[20];
     for (int k = 1; k <= framecount; k++)
     {
     sprintf(str, "%s%d.png", frameName, k);
     SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
     animFrames.pushBack(frame);
     }
     return Animate::create(Animation::createWithSpriteFrames(animFrames, delay));
     */
    
    return animate;
}