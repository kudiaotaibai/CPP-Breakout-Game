#pragma once
#include <SFML/Graphics.hpp>

class Paddle {
public:
    Paddle(float startX, float startY);

    sf::Vector2f getPosition();
    sf::RectangleShape& getShape();

    void update(sf::Time dt);
    void draw(sf::RenderWindow& window);

    void setWidth(float width);
    void resetWidth();
private:
    sf::RectangleShape shape_;
    float speed_ = 20.f;
    float defaultWidth_ = 100.f;
    sf::Clock powerUpClock_;
    sf::Time powerUpDuration_;
    bool isPowerUpActive_ = false;
};