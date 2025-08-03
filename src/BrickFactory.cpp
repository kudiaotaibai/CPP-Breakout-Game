#include "BrickFactory.h"

// 实现 createBrick 静态方法
Brick BrickFactory::createBrick(EBrickType type, float x, float y) {
    // 我们直接返回一个通过构造函数创建的 Brick 对象
    // Brick 的构造函数已经包含了根据类型设置颜色和生命值的逻辑
    return Brick(x, y, type);
}