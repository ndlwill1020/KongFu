//
//  GameScene.hpp
//  KongFu
//
//  Created by macuser on 16/8/24.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp
#include "cocos2d.h"
USING_NS_CC;

class HeroNode;
class MapNode;
class HeroStateNode;
class HeroControlNode;

class GameScene : public Layer{
protected:
    GameScene();
    ~GameScene();
public:
    static Scene* createScene();
    CREATE_FUNC(GameScene);
    virtual bool init();
    
    virtual void update(float dt);
private:
    void pause_menuCB(Ref *pSender);
    void pushScene_update(float dt);
    
    void gameFail_update(float dt);
    void gameSuccess_update(float dt);
    
    
private:
    HeroNode *_hero;
    MapNode *mapNode;
    HeroStateNode *_heroStateNode;
    HeroControlNode *controlNode;
    
    RenderTexture* render;
};
#endif /* GameScene_hpp */
