//
//  BaseState.cpp
//  KongFu
//
//  Created by macuser on 16/8/19.
//
//

#include "BaseState.hpp"

#include "IdleState.hpp"
#include "AttackState.hpp"
#include "RunState.hpp"
#include "JumpState.hpp"
#include "HurtState.hpp"
#include "DeadState.hpp"


IdleState *BaseState::idleState = new IdleState();
AttackState *BaseState::attackState = new AttackState();
RunState *BaseState::runState = new RunState();
JumpState *BaseState::jumpState = new JumpState();
HurtState *BaseState::hurtState = new HurtState();
DeadState *BaseState::deadState = new DeadState();