//
//  FailNode.hpp
//  KongFu
//
//  Created by macuser on 16/8/29.
//
//

#ifndef FailNode_hpp
#define FailNode_hpp

#include "cocos2d.h"
USING_NS_CC;

class FailNode : public Node{
protected:
    FailNode();
    ~FailNode();
public:
    CREATE_FUNC(FailNode);
    virtual bool init();
};

#endif /* FailNode_hpp */
