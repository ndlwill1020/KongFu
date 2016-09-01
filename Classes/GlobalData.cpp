//
//  GlobalData.cpp
//  KongFu
//
//  Created by macuser on 16/8/24.
//
//

#include "GlobalData.h"
#include "MonsterNode.hpp"

int gSelectedLevel = 0;

Vector<MonsterNode*> curMonsterList;
Vector<MonsterNode*> secondWaveMonsterList;
Vector<MonsterNode*> thirdWaveMonsterList;

int waveFlag = 0;