//
//  SettingScene.hpp
//  KongFu
//
//  Created by macuser on 16/8/23.
//
//

#ifndef SettingScene_hpp
#define SettingScene_hpp

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
USING_NS_CC;
USING_NS_CC_EXT;

class SettingScene : public Layer{
protected:
    SettingScene();
    ~SettingScene();
public:
    static Scene* createScene();
    CREATE_FUNC(SettingScene);
    virtual bool init();
    
private:
    void close_menuCB(Ref* pSender);
    void save_menuCB(Ref* pSender);
    void musicToggle_menuCB(Ref* pSender);
    void effectToggle_menuCB(Ref* pSender);
    
    void changeMusicVol(Ref* pSender, Control::EventType type);
    void changeEffectVol(Ref* pSender, Control::EventType type);
    
    void musicVol_sliderCB(Ref* pSender, Slider::EventType type);
    void effectVol_sliderCB(Ref* pSender, Slider::EventType type);
};

#endif /* SettingScene_hpp */
