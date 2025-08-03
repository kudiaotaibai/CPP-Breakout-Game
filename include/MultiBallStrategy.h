#pragma once
#include "IPowerUpStrategy.h"

class MultiBallStrategy : public IPowerUpStrategy {
public:
    PowerUpResult apply(Paddle& paddle, Ball& ball) override;
};