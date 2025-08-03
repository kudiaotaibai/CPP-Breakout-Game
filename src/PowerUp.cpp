#include "PowerUp.h"

PowerUp::PowerUp(float x, float y, std::unique_ptr<IPowerUpStrategy> strategy)
    : strategy_(std::move(strategy)) // 使用 std::move 转移所有权
{
    shape_.setSize(sf::Vector2f(20, 20));
    // 为了区分，我们可以根据策略类型给不同的颜色，但暂时先用一个颜色
    shape_.setFillColor(sf::Color::Cyan); 
    shape_.setOrigin(shape_.getSize() / 2.f);
    shape_.setPosition(x, y);
}

void PowerUp::update(sf::Time dt) {
    shape_.move(0, speed_ * dt.asSeconds());
}
void PowerUp::draw(sf::RenderWindow& window) {
    window.draw(shape_);
}

sf::RectangleShape& PowerUp::getShape() {
    return shape_;
}

IPowerUpStrategy* PowerUp::getStrategy() {
    return strategy_.get(); // 从 unique_ptr 获取裸指针
}