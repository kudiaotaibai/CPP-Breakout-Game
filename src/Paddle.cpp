#include "Paddle.h"

Paddle::Paddle(float startX, float startY) :defaultWidth_(100.f){
    shape_.setSize(sf::Vector2f(100, 20));
    shape_.setFillColor(sf::Color::White);
    shape_.setOrigin(shape_.getSize() / 2.f); // A neat trick to center origin
    shape_.setPosition(startX, startY);

}

sf::Vector2f Paddle::getPosition() {
    return shape_.getPosition();
}

sf::RectangleShape& Paddle::getShape() {
    return shape_;
}

void Paddle::update(sf::Time dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && getPosition().x - shape_.getSize().x / 2 > 0) {
        shape_.move(-speed_, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && getPosition().x + shape_.getSize().x / 2 < 800) { // Assuming WINDOW_WIDTH is 800
        shape_.move(speed_, 0.f);
    }
    if (isPowerUpActive_) {
        if (powerUpClock_.getElapsedTime()>powerUpDuration_) {
            resetWidth();
            isPowerUpActive_ = false;
        }
    }
}

void Paddle::draw(sf::RenderWindow& window) {
    window.draw(shape_);
}

void Paddle::setWidth(float width) {
    sf::Vector2f size=shape_.getSize();
    shape_.setSize(sf::Vector2f(width,size.y));
    shape_.setOrigin(shape_.getSize() / 2.f);
    if (width != defaultWidth_) {
        isPowerUpActive_= true;
        powerUpDuration_ = sf::seconds(5.f); // 效果持续5秒
        powerUpClock_.restart();
    }
}

void Paddle::resetWidth() {
        setWidth(defaultWidth_);
}


