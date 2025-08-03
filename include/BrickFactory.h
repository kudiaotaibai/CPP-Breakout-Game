#pragma once
#include "Brick.h" // 需要知道 Brick 类型和 EBrickType 枚举

// 这是一个纯粹的工具类，用于创建砖块
class BrickFactory {
public:
    // 一个静态方法，可以直接通过类名调用，无需创建工厂对象
    // 它接收一个类型和位置，返回一个创建好的 Brick 对象
    static Brick createBrick(EBrickType type, float x, float y);
};