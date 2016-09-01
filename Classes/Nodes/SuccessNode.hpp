//
//  SuccessNode.hpp
//  KongFu
//
//  Created by macuser on 16/8/29.
//
//

#ifndef SuccessNode_hpp
#define SuccessNode_hpp

#include "cocos2d.h"
USING_NS_CC;

class SuccessNode : public Node{
protected:
    SuccessNode();
    ~SuccessNode();
public:
    CREATE_FUNC(SuccessNode);
    virtual bool init();
};

#endif /* SuccessNode_hpp */
