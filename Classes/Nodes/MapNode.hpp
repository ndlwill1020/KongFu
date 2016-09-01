//
//  MapNode.hpp
//  KongFu
//
//  Created by macuser on 16/8/24.
//
//

#ifndef MapNode_hpp
#define MapNode_hpp
class HeroNode;

#include "cocos2d.h"
USING_NS_CC;

class MapNode : public Node{
protected:
    MapNode();
    ~MapNode();
public:
    void initMap(const char *topMap,const char *midMap, const char *bottomMap);
    CREATE_FUNC(MapNode);
    
    bool isReachBorder(HeroNode *heroNode);
    void moveMap(HeroNode *heroNode);
private:
    ParallaxNode *parallaxNode;
    Sprite* top;
    Sprite* mid;
    Sprite* bottom;
};

#endif /* MapNode_hpp */
