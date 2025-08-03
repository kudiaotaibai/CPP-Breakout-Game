#pragma once
#include "Ball.h"
#include "Paddle.h"
#include <vector>
#include <memory>

// 前向声明 Ball 类
class Ball;

// 我们可以定义一个结构体来返回复杂的结果
struct PowerUpResult {
    bool spawnNewBalls = false;
    // 未来可以添加更多结果，比如 addScore, changeLevel 等
};

class IPowerUpStrategy {
public:
    virtual ~IPowerUpStrategy() = default;
    
    // apply 函数现在返回一个结果
    virtual PowerUpResult apply(Paddle& paddle, Ball& ball) = 0;
};