#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "IPowerUpStrategy.h"

class PowerUp {
public:
    // 构造时需要指定类型和位置，工厂会创建对应的策略
    PowerUp(float x, float y, std::unique_ptr<IPowerUpStrategy> strategy);

    void update(sf::Time dt);
    void draw(sf::RenderWindow& window);

    sf::RectangleShape& getShape();
    IPowerUpStrategy* getStrategy(); // 返回策略指针

private:
    sf::RectangleShape shape_;
    std::unique_ptr<IPowerUpStrategy> strategy_;
    float speed_ = 30.f;
};