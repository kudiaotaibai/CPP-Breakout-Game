#pragma once
#include <SFML/Graphics.hpp>

class Ball {
public:
    Ball(float startX, float startY);

    sf::Vector2f getPosition();
    sf::CircleShape& getShape();


    void update(sf::Time dt);
    void draw(sf::RenderWindow& window);
    void reboundX();
    void reboundY();

    void setSpeed(const sf::Vector2f& newVelocity);
    void resetSpeed();
    // ... 在 public 部分 ...
    sf::Vector2f getVelocity();
    float getRadius() const;
private:
    sf::CircleShape shape_;
    sf::Vector2f velocity_;
    sf::Vector2f defaultVelocity_=sf::Vector2f(240.f, -240.f);

};