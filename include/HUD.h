#pragma once

#include "IGameObserver.h"
#include<SFML/Graphics.hpp>

class HUD: public IGameObserver {
    public:
    HUD();
    void draw(sf::RenderWindow& window);

    void onScoreChanged(int newScore) override;
    void onLivesChanged(int newLives) override;
    private:
    sf::Font font_;
    sf::Text scoreText_;
    sf::Text livesText_;


    void setupText(sf::Text& text,const sf::Vector2f& position);
};
