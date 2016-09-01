//
//  SplashScene.hpp
//  KongFu
//
//  Created by macuser on 16/8/23.
//
//

#ifndef SplashScene_hpp
#define SplashScene_hpp

#include "cocos2d.h"
USING_NS_CC;

class SplashScene : public Layer{
protected:
    SplashScene();
    ~SplashScene();
public:
    static Scene* createScene();
    CREATE_FUNC(SplashScene);
    virtual bool init();
    virtual void onExit();
    virtual void onExitTransitionDidStart();
private:
    // 初始化用户数据
    void initUserData();
    
    void loadingTextureCallBack(Texture2D *texture);
    void nextScene(float dt);
    void loadingAudio();
private:
    Sprite* logoSprite;
    int loadedCount;
    std::thread* _loadingAudioThread;
};

#endif /* SplashScene_hpp */
