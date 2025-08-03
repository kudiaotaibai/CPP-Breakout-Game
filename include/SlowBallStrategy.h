#pragma once
#include "IPowerUpStrategy.h"

class SlowBallStrategy : public IPowerUpStrategy {
public:
   PowerUpResult  apply(Paddle& paddle, Ball& ball) override;
};