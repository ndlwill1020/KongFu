//
//  ChallengeScene.hpp
//  KongFu
//
//  Created by macuser on 16/8/24.
//
//

#ifndef ChallengeScene_hpp
#define ChallengeScene_hpp

#include "cocos2d.h"
USING_NS_CC;

class SelectLevelNode;

class ChallengeScene : public Layer{
protected:
    ChallengeScene();
    ~ChallengeScene();
public:
    static Scene* createScene();
    CREATE_FUNC(ChallengeScene);
    virtual bool init();
private:
    void close_menuCB(Ref* pSender);
    void challenge_menuCB(Ref* pSender);
    
    void item1_menuCB(Ref* pSender);
    void item2_menuCB(Ref* pSender);
    void item3_menuCB(Ref* pSender);
private:
    SelectLevelNode *levelNode;
};

#endif /* ChallengeScene_hpp */
