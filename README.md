# C++ 2D游戏：复古打砖块 (Retro Breakout)

[![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![Library](https://img.shields.io/badge/Library-SFML-green.svg)](https://www.sfml-dev.org/)
[![Build](https://img.shields.io/badge/Build-CMake-orange.svg)](https://cmake.org/)

一款基于 C++17 和 SFML 图形库，从零开始独立开发的 2D 复古打砖块游戏。这个项目是我学习和实践 C++ 面向对象编程、软件设计模式以及游戏开发基础的个人作品。

---

### 游戏截图 / GIF

<img width="816" height="639" alt="23346b637b2ef5d8e0d1cead3c8d32e" src="https://github.com/user-attachments/assets/13338faa-2df3-4f4f-b6d1-8e64642fcfa6" />



---

### 主要特色

*   **经典的打砖块核心玩法**: 控制挡板反弹小球，清除所有可摧毁的砖块。
*   **多样化的砖块类型**: 包括普通砖块、硬砖块（需多次撞击）和不可摧毁的砖块。
*   **动态道具系统**: 击碎特殊砖块会掉落道具，提供限时增益效果（如挡板变宽、小球减速）。
*   **数据驱动的关卡加载**: 游戏关卡布局由简单的文本文件定义，易于创建和扩展新关卡。
*   **实时 UI 反馈**: 屏幕上实时显示分数和剩余生命值。

---

### 使用的技术栈

*   **语言**: C++17
*   **图形/多媒体库**: SFML 2.6.2
*   **构建系统**: CMake
*   **版本控制**: Git
*   **开发环境**: CLion + MinGW (GCC)

---

### 如何编译和运行

本项目使用 CMake 进行构建。请确保你已经安装了 C++ 编译器和 CMake。

1.  **克隆仓库**:
    ```bash
    git clone https://github.com/kudiaotaibai/CPP-Breakout-Game.git
    cd CPP-Breakout-Game
    ```

2.  **安装 SFML**:
    *   **Windows (MSYS2/MinGW)**: 推荐使用 pacman 进行安装：
        ```bash
        pacman -S mingw-w64-x86_64-sfml
        ```
    *   **其他系统或手动安装**: 请参考 [SFML 官方教程](https://www.sfml-dev.org/tutorials/2.6/)，并将库文件路径配置到你的环境中。

3.  **配置并构建项目**:
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```
    (或者直接在 CLion 或 Visual Studio Code 中打开项目根目录，IDE 会自动处理 CMake 配置。)

4.  **运行游戏**:
    *   在 Windows 上，可执行文件位于 `build/Debug/` 或 `build/` 目录下。
    *   **注意**: 运行时，请确保字体文件 (`arial.ttf`) 和资源文件夹 (`levels/`) 与可执行文件位于同一工作目录下，或已正确配置运行环境的工作目录。

---

###  项目架构设计

本项目以**面向对象**和**设计模式**为核心思想进行架构，旨在实现代码的**高内聚、低耦合**，提高系统的可扩展性和可维护性。

#### 策略模式 (Strategy Pattern)
*   **应用场景**: 灵活实现多种道具效果。
*   **实现**: 定义了一个 `IPowerUpStrategy` 接口，将每种道具效果（如 `WidenPaddleStrategy`, `SlowBallStrategy`）封装在独立的策略类中。`Game` 类的核心逻辑不关心具体的道具效果，只负责在碰撞时调用策略的 `apply` 方法，从而实现了新道具的**可插拔式扩展**。

#### 工厂模式 (Factory Pattern)
*   **应用场景**: 管理不同类型砖块的创建。
*   **实现**: 创建了 `BrickFactory` 类，它根据从关卡文件读取的类型字符（'N', 'H', 'P' 等），负责创建具有不同属性（生命值、颜色）的 `Brick` 对象。这使得 `Game` 类的关卡加载逻辑与砖块的具体创建细节**完全解耦**。

#### 观察者模式 (Observer Pattern)
*   **应用场景**: 游戏核心状态（分数、生命值）与 UI 显示之间的通信。
*   **实现**: `Game` 类作为**主题 (Subject)**，在状态变化时广播通知。`HUD` 类作为**观察者 (Observer)**，订阅这些通知并相应地更新显示。这种方式避免了 `Game` 类对 `HUD` 类的直接依赖，实现了**松耦合**，未来可以轻松地加入新的观察者（如音效系统）来响应分数变化。
