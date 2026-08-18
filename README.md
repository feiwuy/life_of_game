# Game of Life - 康威生命游戏

用 C 语言实现的生命游戏，支持终端和图形化（Raylib）两种显示方式。

## 功能

- 标准 B2/S23 规则
- 可自定义初始细胞（输入坐标）
- 图形版支持 60 FPS 流畅显示，演化速度独立控制
- 终端版采用 ANSI 转义实现原地刷新

## 依赖

- 终端版：仅需标准 C 库
- 图形版：需安装 [Raylib](https://www.raylib.com/)

## 编译与运行

```bash
# 终端版
gcc -o life life_game.c -lm
./life

# 图形版（需先安装 raylib）
gcc -o life_visual life_game_visual.c -lraylib -lm
./life_visual



-------------------------------------------
By: DeepSeek 网页端
