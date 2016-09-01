//
//  PauseScene.hpp
//  KongFu
//
//  Created by macuser on 16/8/25.
//
//

#ifndef PauseScene_hpp
#define PauseScene_hpp

#include "cocos2d.h"
USING_NS_CC;



class PauseScene : public Layer{
protected:
    PauseScene();
    ~PauseScene();
public:
    static Scene* createScene(RenderTexture *rt);
    CREATE_FUNC(PauseScene);
    virtual bool init();
private:
    void musicSetting_menuCB(Ref* pSender);
private:
    Sprite* spriteUp;
    Sprite* spriteDown;
};

#endif /* PauseScene_hpp */
