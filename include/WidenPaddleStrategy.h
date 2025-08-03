#pragma once
#include "IPowerUpStrategy.h"

class WidenPaddleStrategy : public IPowerUpStrategy {
public:
    PowerUpResult  apply(Paddle& paddle, Ball& ball) override;
};