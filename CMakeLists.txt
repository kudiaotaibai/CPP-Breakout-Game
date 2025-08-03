cmake_minimum_required(VERSION 3.10)
project(txz)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ===================================================================
# SFML 配置部分 (使用 pacman 安装后的版本)
# ===================================================================

# find_package 现在可以自动找到 SFML 了，因为 pacman 把它装在了标准位置。
# 我们不再需要 set(SFML_DIR ...) 和 set(CMAKE_PREFIX_PATH ...)
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# ===================================================================


# --- 添加包含目录 ---
# 这一步依然是好习惯，用于我们自己的头文件
include_directories(${PROJECT_SOURCE_DIR}/include)
# 注意：SFML 的头文件目录，find_package 成功后会自动通过 ${SFML_INCLUDE_DIR} 提供
# 但通常把它加到 target_include_directories 中是更好的做法

# --- 添加可执行文件和所有源文件 ---
add_executable(txz
        src/main.cpp
        src/Game.cpp
        src/Ball.cpp
        src/Paddle.cpp
        src/Brick.cpp
        include/IPowerUpStrategy.h
        src/WidenPaddleStrategy.cpp
        include/WidenPaddleStrategy.h
        src/SlowBallStrategy.cpp
        include/SlowBallStrategy.h
        src/MultiBallStrategy.cpp
        include/MultiBallStrategy.h
        src/PowerUp.cpp
        include/PowerUp.h
        include/IGameObserver.h
        src/HUD.cpp
        include/HUD.h
        src/BrickFactory.cpp
        include/BrickFactory.h
)

# --- 核心链接步骤 ---
# target_link_libraries 会自动处理包含目录和库文件链接
target_link_libraries(txz PRIVATE sfml-graphics)

# --- (可选) Windows 平台特定设置 ---
if(WIN32)
    set_target_properties(txz PROPERTIES WIN32_EXECUTABLE ON)
endif()