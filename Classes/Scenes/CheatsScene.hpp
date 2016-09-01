//
//  CheatsScene.hpp
//  KongFu
//
//  Created by macuser on 16/8/23.
//
//

#ifndef CheatsScene_hpp
#define CheatsScene_hpp

#include "cocos2d.h"
USING_NS_CC;

class CheatsScene : public Layer{
protected:
    CheatsScene();
    ~CheatsScene();
public:
    static Scene* createScene();
    CREATE_FUNC(CheatsScene);
    virtual bool init();
    
private:
    void right_menuCB(Ref* pSender);
    void left_menuCB(Ref* pSender);
private:
    //被lambda使用 要写成成员变量
    bool flag;
    Sprite *interface_1;
    Sprite *interface_2;
};


#endif /* CheatsScene_hpp */
