//
//  Enums.h
//  KongFu
//
//  Created by macuser on 16/8/26.
//
//

#ifndef Enums_h
#define Enums_h

enum InputType{
    NONE,
    
    FIST_CLICKED,
    FOOT_CLICKED,
    JUMP_CLICKED,
    SKILL_CLICKED,
    
    LEFT_PRESSED,
    LEFT_DARGOUT,
    LEFT_RELEASED,
    
    RIGHT_PRESSED,
    RIGHT_DARGOUT,
    RIGHT_RELEASED
    
};

enum MonsterState{
    IDLE,
    RUN,
    ATTACK,
    HURT,
    DEAD
};

enum MonsterType{
    NONE_ATTRIBUTE,
    WOOD_ATTRIBUTE,
    FIRE_ATTRIBUTE,
    ROCK_ATTRIBUTE
};


#endif /* Enums_h */
