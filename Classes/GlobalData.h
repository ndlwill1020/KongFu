//
//  GlobalData.h
//  KongFu
//
//  Created by macuser on 16/8/19.
//
//

#ifndef GlobalData_h
#define GlobalData_h
#include "cocos2d.h"
USING_NS_CC;

class MonsterNode;

extern int gSelectedLevel;

extern Vector<MonsterNode *> curMonsterList;
extern Vector<MonsterNode *> secondWaveMonsterList;
extern Vector<MonsterNode *> thirdWaveMonsterList;

extern int waveFlag;



#endif /* GlobalData_h */
