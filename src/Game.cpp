#include "Game.h"
#include <cmath>   // 为了 std::abs
#include <cstdlib> // 为了 rand() 和 srand()
#include <ctime>   // 为了 time()
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iostream>
#include "BrickFactory.h"
// Game 类的构造函数：负责初始化所有游戏内容
Game::Game()
    // 使用成员初始化列表来初始化对象
    : window_(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Breakout Game! (with PowerUps)"),
      ball_(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f),
      paddle_(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - 50.f),
      score_(0),
      lives_(3),
       hud_()

{
    // 设置帧率限制
    window_.setFramerateLimit(60);

    // 初始化随机数种子，这样每次运行游戏时道具的出现位置都不同
    srand(static_cast<unsigned int>(time(NULL)));

    loadLevel("levels/level1.txt");

    addObserver(&hud_);

    notifyScoreChanged();
    notifyLivesChanged();

}

// 游戏主循环的驱动函数
void Game::run() {
    sf::Clock clock;
    while (window_.isOpen()) {
            sf::Time dt=clock.restart();
            processEvents();
            update(dt);
            render();

    }
}

// 处理窗口事件和用户输入
void Game::processEvents() {
    sf::Event event;
    while (window_.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window_.close();
        }
    }
}

// 更新所有游戏对象的状态
void Game::update(sf::Time dt) {
    ball_.update(dt);
    paddle_.update(dt);

    // 更新所有道具的位置
    for (auto& powerUp : powerUps_) {
        powerUp.update(dt);
    }

    handleCollisions();
}

// 专门处理所有碰撞逻辑
void Game::handleCollisions() {
    // 1. 小球与窗口边界的碰撞
    if (ball_.getPosition().x - ball_.getRadius() < 0 || ball_.getPosition().x + ball_.getRadius() > WINDOW_WIDTH) {
        ball_.reboundX();
    }
    if (ball_.getPosition().y - ball_.getRadius() < 0) {
        ball_.reboundY();
    }
    if (ball_.getPosition().y + ball_.getRadius() > WINDOW_HEIGHT) {
        // 游戏失败：生命值减一并发出通知
        lives_--;
        notifyLivesChanged();

        if (lives_ <= 0) {
            // 如果生命值为0，游戏结束
            window_.close();
        } else {
            // 如果还有生命值，重置小球位置
            ball_ = Ball(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
        }
    }

    // 2. 小球与挡板的碰撞
    if (ball_.getShape().getGlobalBounds().intersects(paddle_.getShape().getGlobalBounds())) {
        ball_.reboundY();
    }

    // 3. 小球与砖块的碰撞
    for (auto it = bricks_.begin(); it != bricks_.end(); ) {
        if (ball_.getShape().getGlobalBounds().intersects(it->getShape().getGlobalBounds())) {
            // 小球反弹
            ball_.reboundY();

            // 调用 brick.hit() 来处理伤害，并检查砖块是否被摧毁
            if (it->hit()) {
                // 如果 hit() 返回 true，说明砖块被彻底摧毁
                score_ += 10;
                notifyScoreChanged();

                // 检查被摧毁的砖块是不是道具砖块
                if (it->getType() == EBrickType::PowerUp) {
                    spawnPowerUp(it->getShape().getPosition().x, it->getShape().getPosition().y);
                }

                // 如果砖块被摧毁了，就从 vector 中移除它
                it = bricks_.erase(it);
            } else {
                // 如果砖块只是掉血但没死（比如硬砖块），我们就不删除它
                // 迭代器需要继续前进以检查下一个砖块
                ++it;
            }

            // 为简化逻辑，每帧只处理一次砖块碰撞
            break;
        } else {
            // 如果没有碰撞，迭代器继续前进
            ++it;
        }
    }

    // 4. 挡板与道具的碰撞
    for (auto it = powerUps_.begin(); it != powerUps_.end(); ) {
        if (paddle_.getShape().getGlobalBounds().intersects(it->getShape().getGlobalBounds())) {
            // 应用道具效果
            it->getStrategy()->apply(paddle_, ball_);
            // 接到后销毁道具
            it = powerUps_.erase(it);
        } else {
            // (可选) 检查道具是否掉出屏幕，如果是也销毁它
            if (it->getShape().getPosition().y > WINDOW_HEIGHT) {
                it = powerUps_.erase(it);
            } else {
                 ++it;
            }
        }
    }
}

// 生成一个随机道具的辅助函数
void Game::spawnPowerUp(float x, float y) {
    // 随机选择一个道具效果 (50%的概率)
    int randomType = rand() % 2;
    if (randomType == 0) {
        powerUps_.emplace_back(x, y, std::make_unique<WidenPaddleStrategy>());
    } else {
        powerUps_.emplace_back(x, y, std::make_unique<SlowBallStrategy>());
    }
}


// 渲染所有游戏对象到屏幕
void Game::render() {
    window_.clear(sf::Color::Black);

    ball_.draw(window_);
    paddle_.draw(window_);

    for (auto& brick : bricks_) {
        brick.draw(window_);
    }

    for (auto& powerUp : powerUps_) {
        powerUp.draw(window_);
    }
    hud_.draw(window_);

    window_.display();
}

void Game::addObserver(IGameObserver* observer) {
    if (observer) { // 检查指针是否有效
        observers_.push_back(observer);
    }
}

void Game::removeObserver(IGameObserver* observer) {
    // C++20 中有更简洁的 std::erase_if，这里用传统方法
    observers_.erase(std::remove(observers_.begin(), observers_.end(), observer), observers_.end());
}

void Game::notifyScoreChanged() {
    for (auto* observer : observers_) {
        observer->onScoreChanged(score_);
    }
}

void Game::notifyLivesChanged() {
    for (auto* observer : observers_) {
        observer->onLivesChanged(lives_);
    }
}

void Game::loadLevel(const std::string& filePath) {
    bricks_.clear();

    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr<<"Error opening file: "<<filePath<<std::endl;
        return;
    }
    std::string line;
    int row = 0;

    const float brickWidth = 60.f;
    const float brickHeight = 20.f;
    const float brickSpacingX=10.f;
    const float brickSpacingY=5.f;
    const float startOffsetX=70.f;
    const float startOffsetY=60.f;

    while (std::getline(file, line)) {
        for (int col=0;col<line.length();++col) {
            EBrickType type;
            char c = line[col];


            switch (c) {
                case 'N': type = EBrickType::Normal; break;
                case 'H': type = EBrickType::Hard; break;
                case 'P': type = EBrickType::PowerUp; break;
                case 'I': type = EBrickType::Indestructible; break;
                default: continue; // 如果是空格或其他字符，直接跳到下一次循环
            }

            float xPos = col * (brickWidth + brickSpacingX) + startOffsetX;
            float yPos = row * (brickHeight + brickSpacingY) + startOffsetY;

            bricks_.emplace_back(xPos, yPos, type);

        }
        row++;
    }
}