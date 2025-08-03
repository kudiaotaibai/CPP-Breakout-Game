#include "MultiBallStrategy.h"

PowerUpResult MultiBallStrategy::apply(Paddle& paddle, Ball& ball) {
    // 这个策略本身不修改 paddle 或 ball
    (void)paddle;
    (void)ball;

    // 它只告诉 Game 类：“请帮我生成新的小球”
    PowerUpResult result;
    result.spawnNewBalls = true;
    return result;
}