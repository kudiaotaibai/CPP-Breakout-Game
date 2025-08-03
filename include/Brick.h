#pragma once
#include <SFML/Graphics.hpp>

enum class EBrickType {
   Normal,
   Hard,
   PowerUp,
   Indestructible
};

class Brick {
public:
   Brick(float x, float y,EBrickType type);

   sf::RectangleShape& getShape();
   void draw(sf::RenderWindow& window);

   bool hit();
   EBrickType getType() const;
private:
   sf::RectangleShape shape_;
   EBrickType type_;
   int health_;
};