//
//  HelpScene.hpp
//  KongFu
//
//  Created by macuser on 16/8/23.
//
//

#ifndef HelpScene_hpp
#define HelpScene_hpp

#include "cocos2d.h"
USING_NS_CC;


class HelpScene : public Layer{
protected:
    HelpScene();
    ~HelpScene();
public:
    static Scene* createScene();
    CREATE_FUNC(HelpScene);
    virtual bool init();
private:
    void resetPosition_ActionCB();
private:
    Label* text;
};

#endif /* HelpScene_hpp */
