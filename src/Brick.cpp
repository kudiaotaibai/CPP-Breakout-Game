#include "Brick.h"

Brick::Brick(float x, float y,EBrickType type):type_(type) {
    shape_.setSize(sf::Vector2f(60, 20));

    shape_.setOrigin(shape_.getSize() / 2.f);
    shape_.setPosition(x, y);
    switch (type_) {
        case EBrickType::Normal:
            health_ = 1;
            shape_.setFillColor(sf::Color::Yellow);
            break;
        case EBrickType::Hard:
            health_ = 2;
            shape_.setFillColor(sf::Color(128,128,128));
            break;
        case EBrickType::PowerUp:
            health_ = 1;
            shape_.setFillColor(sf::Color::Blue);
            break;
        case EBrickType::Indestructible:
            health_ = -1;
            shape_.setFillColor(sf::Color(80,80,80));
            break;
    }
}

bool Brick::hit() {
    if (type_ == EBrickType::Indestructible){
          return false;
    }
    health_--;
    if (health_ ==1&&type_ == EBrickType::Hard) {
        shape_.setFillColor(sf::Color::Yellow);

    }
    return health_ <= 0;

}
EBrickType Brick::getType() const {
    return type_;
}



sf::RectangleShape& Brick::getShape() {
    return shape_;
}

void Brick::draw(sf::RenderWindow& window) {
    window.draw(shape_);
}