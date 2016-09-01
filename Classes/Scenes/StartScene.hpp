//
//  StartScene.hpp
//  KongFu
//
//  Created by macuser on 16/8/23.
//
//

#ifndef StartScene_hpp
#define StartScene_hpp

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class StartScene : public Layer{
protected:
    StartScene();
    ~StartScene();
public:
    static Scene* createScene();
    CREATE_FUNC(StartScene);
    virtual bool init();
    
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
private:
    void help_menuCB(Ref* pSender);
    void photo_menuCB(Ref* pSender);
    void cheats_menuCB(Ref* pSender);
    void set_menuCB(Ref* pSender);
    void levelMode_menuCB(Ref* pSender);
    void challenge_menuCB(Ref* pSender);
};

#endif /* StartScene_hpp */
