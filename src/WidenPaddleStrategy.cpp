#include "WidenPaddleStrategy.h"
#include "Paddle.h" // 确保包含了 Paddle.h 来使用它的方法

PowerUpResult  WidenPaddleStrategy::apply(Paddle& paddle, Ball& ball) {
    // 将挡板宽度设置为 150.f
    paddle.setWidth(150.f);

    // 这个策略不影响球，但为了保持接口一致性，我们还是接收 ball 参数
    // (void)ball; 是一种告诉编译器“我知道我没用这个变量，请不要警告我”的写法
    (void)ball;
    return PowerUpResult();
}