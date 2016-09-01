//
//  SelectLevelNode.cpp
//  KongFu
//
//  Created by macuser on 16/8/24.
//
//

#include "SelectLevelNode.hpp"
#include "GlobalDefine.h"

#define ANIMATION_DURATION  0.3f
//菜单的缩小比例 最小的比例是1-MENU_SCALE
#define MENU_SCALE 0.3
//菜单的倾斜度
#define MENU_SLOPE 60.0
#define CALC_RATIO 1

//菜单项长度与菜单长度的比例 滑动一个菜单项长度，菜单项变化一个
#define ITEM_SIZE_SCALE (1.0/4)

SelectLevelNode::SelectLevelNode()
:selectedItem(nullptr)
,index(0.0f)
,lastIndex(0.0f)
{

}

SelectLevelNode::~SelectLevelNode(){

}

bool SelectLevelNode::init(){
    if (!Node::init()) {
        return false;
    }
    
    this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    this->setContentSize(WINSIZE * 2 / 3);
    
    //for test
//    auto layerColor = LayerColor::create(Color4B::RED, this->getContentSize().width, this->getContentSize().height);
//    this->addChild(layerColor, -888);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(SelectLevelNode::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(SelectLevelNode::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(SelectLevelNode::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void SelectLevelNode::addMenuItem(MenuItem *item){
    item->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
    this->addChild(item);
    items.pushBack(item);
    
    index = 0;
    lastIndex = 0;
    
    updateItemPositionWithAnimation();
    
}

//index / (index + 1),得到的小于1    index越大，得到的值越大
float SelectLevelNode::calcFunc(int index, float value){
    return value * index / (abs(index) + CALC_RATIO);
}

void SelectLevelNode::updateItemPosition(){
    auto menuSize = getContentSize();
    for (int i = 0; i < items.size(); i++){
        //设置位置
        float x = calcFunc(i - index, menuSize.width / 2);
        items.at(i)->setPosition(Point(menuSize.width / 2 + x, menuSize.height / 2));
        //设置zOrder,即绘制顺序
        items.at(i)->setLocalZOrder((int)(-fabsf((i - index) * 100)));
        //设置伸缩比例
        items.at(i)->setScale(1.0 - fabsf(calcFunc(i - index, MENU_SCALE)));
        //设置倾斜
        auto orbit = OrbitCamera::create(0, 1, 0, calcFunc(i - lastIndex, MENU_SLOPE), calcFunc(i - lastIndex, MENU_SLOPE) - calcFunc(i - index, MENU_SLOPE), 0, 0);
        items.at(i)->runAction(orbit);
    }
}

void SelectLevelNode::updateItemPositionWithAnimation(){
    auto menuSize = getContentSize();
    for (int i = 0; i < items.size(); i++){
        items.at(i)->stopAllActions();
    }
    
    
    for (int i = 0; i < items.size(); i++){
        //设置zOrder,即绘制顺序
        items.at(i)->setLocalZOrder((int)(-fabsf((i - index) * 100)));
        //设置位置
        float offsetX = calcFunc(i - index, menuSize.width / 2);
        auto moveTo = MoveTo::create(ANIMATION_DURATION, Point(menuSize.width / 2 + offsetX, menuSize.height / 2));
        items.at(i)->runAction(moveTo);
        //设置伸缩比例
        auto scaleTo = ScaleTo::create(ANIMATION_DURATION, (1.0f - fabsf(calcFunc(i - index, MENU_SCALE))));
        items.at(i)->runAction(scaleTo);
        ////设置倾斜   OrbitCamera关键参数4和5  起始位置和旋转角度
        
        log("turn:%f", calcFunc(i - index, MENU_SLOPE) - calcFunc(i - lastIndex, MENU_SLOPE));
        
        auto orbit = OrbitCamera::create(ANIMATION_DURATION, 1.0f, 0.0f, calcFunc(i - lastIndex, MENU_SLOPE), calcFunc(i - index, MENU_SLOPE) - calcFunc(i - lastIndex, MENU_SLOPE), 0.0f, 0.0f);
        items.at(i)->runAction(orbit);
    }
    scheduleOnce(schedule_selector(SelectLevelNode::actionFinished_updateCB), ANIMATION_DURATION);
}

MenuItem* SelectLevelNode::getCurrentItem(){
    if (items.size() == 0) {
        return nullptr;
    }
    return items.at(index);
}

void SelectLevelNode::setIndex(int index){
    lastIndex = index;
    this->index = index;
}
float SelectLevelNode::getIndex(){
    return index;
}

void SelectLevelNode::actionFinished_updateCB(float dt){
    selectedItem = getCurrentItem();
    if (selectedItem) {
        selectedItem->selected();//MenuItem的属性
    }
}

//void SelectLevelNode::addItem(Sprite *sprite){
//
//}

bool SelectLevelNode::onTouchBegan(Touch *touch, Event *unused_event){
    for (int i = 0; i < items.size(); i++){
        items.at(i)->stopAllActions();
    }
    
    if (selectedItem) {
        selectedItem->unselected();
    }
    
    auto position = this->convertToNodeSpace(touch->getLocation());
    auto size = this->getContentSize();
    auto rect = Rect(0, 0, size.width, size.height);
    if (rect.containsPoint(position)){
        return true;
    }
    return false;
}

void SelectLevelNode::onTouchMoved(Touch *touch, Event *unused_event){
    //delta position between the current location and the previous location
    auto xDelta = touch->getDelta().x;
    auto size = getContentSize();
    
    
    lastIndex = index;
    index -= xDelta / (size.width * ITEM_SIZE_SCALE);
    updateItemPosition();
}

void SelectLevelNode::onTouchEnded(Touch *touch, Event *unused_event){
    auto size = getContentSize();
    auto xDelta = touch->getLocation().x - touch->getStartLocation().x;
    rectify(xDelta>0);
    if (fabsf(xDelta)<size.width / 24 && selectedItem)
        selectedItem->activate();
    updateItemPositionWithAnimation();
}

void SelectLevelNode::rectify(bool forward){
    auto _index = getIndex();
    if (_index < 0)
        _index = 0;
    if (_index>items.size() - 1)
        _index = items.size() - 1;
    if (forward){
        _index = (int)(_index + 0.4);
    }
    else
        _index = (int)(_index + 0.6);
    setIndex((int)_index);
}
