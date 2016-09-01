//
//  MonsterControllerNode.hpp
//  KongFu
//
//  Created by macuser on 16/8/29.
//
//

#ifndef MonsterController_hpp
#define MonsterController_hpp
#include "cocos2d.h"
USING_NS_CC;

class HeroNode;
class MapNode;

class MonsterController : public Ref{
protected:
    MonsterController();
    ~MonsterController();
public:
    static MonsterController* createWithHeroNode_MapNode(HeroNode* heroNode, MapNode *mapNode);
    bool initWithHeroNode_MapNode(HeroNode* heroNode, MapNode *mapNode);
    
private:
    HeroNode *heroNode;
    MapNode *mapNode;

};
#endif /* MonsterController_hpp */
