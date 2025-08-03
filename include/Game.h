#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory> // 为了 std::unique_ptr 和 std::make_unique
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include "PowerUp.h"
#include "WidenPaddleStrategy.h"
#include "SlowBallStrategy.h"
#include "IGameObserver.h"
#include"HUD.h"
class Game {
public:
    Game();
    void run();

    void addObserver(IGameObserver* observer);
    void removeObserver(IGameObserver* observer);

private:
    void processEvents();
    void update(sf::Time dt);
    void render();
    void handleCollisions();
    void spawnPowerUp(float x, float y); // 新增一个辅助函数来生成道具

    void notifyScoreChanged();
    void notifyLivesChanged();

    void loadLevel(const std::string& filePath);

    sf::RenderWindow window_;
    HUD hud_;
    Ball ball_;
    Paddle paddle_;
    std::vector<Brick> bricks_;
    std::vector<PowerUp> powerUps_; // 用于管理屏幕上所有道具的容器

    int score_ = 0;
    int lives_ = 3;

    std::vector<IGameObserver*> observers_;
    // 游戏窗口的尺寸常量
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;
};