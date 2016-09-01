//
//  PictureAtlasScene.hpp
//  KongFu
//
//  Created by macuser on 16/8/23.
//
//

#ifndef PictureAtlasScene_hpp
#define PictureAtlasScene_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d::ui;

class PictureAtlasScene : public Layer{
protected:
    PictureAtlasScene();
    ~PictureAtlasScene();
public:
    static Scene* createScene();
    CREATE_FUNC(PictureAtlasScene);
    virtual bool init();
    
private:
    void listView_CB(Ref* pSender, ListView::EventType type);
    
    void button_callback(Ref* pSender, Widget::TouchEventType type);
    
private:
    ListView* listView;
    ssize_t selectedIndex;
    
    Sprite* m_pMZ_Pic;
    LabelTTF* m_pMZLabel;
    Sprite* m_pMZ_Txt;
    
    Sprite* m_pLion_Pic;
    LabelTTF* m_pLionLabel;
    
    Sprite* m_pStone_Pic ;
    LabelTTF* m_pStoneLabel;
};

#endif /* PictureAtlasScene_hpp */
