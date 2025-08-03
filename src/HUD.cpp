#include "HUD.h"
#include "iostream"

HUD::HUD() {
    if (!font_.loadFromFile("arial.ttf")) {
        std::cout << "Error loading font." << std::endl;
    }

    setupText(scoreText_,sf::Vector2f(20,10));
    setupText(livesText_,sf::Vector2f(680,10));

    onScoreChanged(0);
    onLivesChanged(3);
}

void HUD::draw(sf::RenderWindow& window) {
    window.draw(scoreText_);
    window.draw(livesText_);
}
void HUD::onScoreChanged(int newscore) {
    scoreText_.setString("Score:"+std::to_string(newscore));

}
void HUD::onLivesChanged(int newlives) {
    livesText_.setString("Lives:"+std::to_string(newlives));
}

void HUD::setupText(sf::Text& text,const sf::Vector2f& position) {
    text.setFont(font_);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(position);
}
