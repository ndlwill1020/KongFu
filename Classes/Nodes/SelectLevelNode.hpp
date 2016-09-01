//
//  SelectLevelNode.hpp
//  KongFu
//
//  Created by macuser on 16/8/24.
//
//

#ifndef SelectLevelNode_hpp
#define SelectLevelNode_hpp

#include "cocos2d.h"
USING_NS_CC;

class SelectLevelNode : public Node{
protected:
    SelectLevelNode();
    ~SelectLevelNode();
public:
    CREATE_FUNC(SelectLevelNode);
    virtual bool init();
    
    void addMenuItem(MenuItem *item);
//    void addItem(Sprite *sprite);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    MenuItem* getCurrentItem();
private:
    void updateItemPosition();
    void updateItemPositionWithAnimation();
    float calcFunc(int index, float value);
    
    void actionFinished_updateCB(float dt);
    
    
    void rectify(bool forward);
    
    //设置当前显示索引
    void setIndex(int index);
    //当前显示菜单项的索引号
    float getIndex();
private:
    Vector<MenuItem *> items;
    MenuItem *selectedItem;
    
//    Vector<Sprite *> items;
//    Sprite* selectedItem;
    //当前下标
    float index;
    float lastIndex;
    
};

#endif /* SelectLevelNode_hpp */
