#include "SlowBallStrategy.h"
#include "Ball.h"   // 确保包含了 Ball.h
#include "Paddle.h" // 虽然没用，但接口要求

PowerUpResult SlowBallStrategy::apply(Paddle& paddle, Ball& ball) {
    // 获取小球当前的速度
    sf::Vector2f currentVelocity = ball.getVelocity(); // 注意：我们需要为 Ball 类添加 getVelocity 方法

    // 将速度减半
    ball.setSpeed(currentVelocity * 0.5f);

    (void)paddle;
    return PowerUpResult();
}