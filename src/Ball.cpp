#include "Ball.h"

Ball::Ball(float startX, float startY):  defaultVelocity_(240.f, -240.f) {
    shape_.setRadius(10.f);
    shape_.setFillColor(sf::Color::Red);
    shape_.setOrigin(shape_.getRadius(), shape_.getRadius());
    shape_.setPosition(startX, startY);
    velocity_ = sf::Vector2f(240.f, -240.f);
}

sf::Vector2f Ball::getPosition() {
    return shape_.getPosition();
}

sf::CircleShape& Ball::getShape() {
    return shape_;
}

void Ball::update(sf::Time dt) {
    // 为了让移动不受帧率影响，标准的做法是：
    // 位移 = 速度 * 时间
    shape_.move(velocity_ * dt.asSeconds());
}

void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape_);
}

void Ball::reboundX() {
    velocity_.x = -velocity_.x;
}

void Ball::reboundY() {
    velocity_.y = -velocity_.y;
}

void Ball::setSpeed(const sf::Vector2f &newVelocity) {
    velocity_ = newVelocity;
}

void Ball::resetSpeed() {
    velocity_ = defaultVelocity_;
}

sf::Vector2f Ball::getVelocity() {
    return velocity_;
}
float Ball::getRadius() const {
    return shape_.getRadius();
}

