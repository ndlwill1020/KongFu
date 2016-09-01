//
//  GlobalDefine.h
//  KongFu
//
//  Created by macuser on 16/8/19.
//
//

#ifndef GlobalDefine_h
#define GlobalDefine_h
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

#define WINSIZE Director::getInstance()->getWinSize()

#define setIntToXML     UserDefault::getInstance()->setIntegerForKey
#define setFloatToXML   UserDefault::getInstance()->setFloatForKey
#define setBoolToXML    UserDefault::getInstance()->setBoolForKey
#define getIntFromXML   UserDefault::getInstance()->getIntegerForKey
#define getFloatFromXML UserDefault::getInstance()->getFloatForKey
#define getBoolFromXML  UserDefault::getInstance()->getBoolForKey



#define SOUNDVOL        "soundVolume"        // 音效音量
#define MUSICVOL        "musicVolume"          // 音乐音量

#define SOUND_KEY       "isPlaySound"            // 是否播放背景音效
#define MUSIC_KEY       "isPlayMusic"              // 是否播放背景音乐

#define GAMELEVEL_KEY   "curLevel"        // 当前关卡
#define SELECTEDLEVEl   "selectedLevel"               // 选择的关卡
#define LEVELONE         "levelOne"                     // 第一关
#define LEVELTWO         "levelTwo"                    // 第二关
#define LEVELTHREE       "levelThree"               // 第三关
#define GAMEOVER        "gameOver"              // 游戏结束结果

#define HEROLEVEL_KEY   "curHeroLevel"          // 当前英雄等级
#define HEROCOIN_KEY    "curHeroCoin"            // 英雄金币
#define HEROENERGY_KEY  "curHeroEnergy"   // 英雄体力



#define AudioEngine   SimpleAudioEngine::getInstance()

//AudioEngine->setEffectsVolume(getFloatFromXML(SOUNDVOL));
#define PLAY_BUTTON_EFFECT \
if (getBoolFromXML(SOUND_KEY)) \
{ \
AudioEngine->playEffect("Sound/button.wav"); \
}




#endif /* GlobalDefine_h */
