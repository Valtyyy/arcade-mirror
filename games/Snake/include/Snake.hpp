/*
** EPITECH PROJECT, 2026
** IGame
** File description:
** header
*/

#pragma once

#include "IGame.hpp"
#include "Key.hpp"
#include "gfx.hpp"
#include <cstddef>
#include <deque>
#include <functional>
#include <ncurses.h>
#include <queue>
#include <string>
#include <deque>
#include <map>
#include "GameMatrix.hpp"
#define TILESIZE 40
#define COLUMNS 20
#define LINES 20


namespace Snake {

enum GAME {
    EMPTY,
    WALL,
    SCORE,
    FISH,
    HEAD,
    BODY,
    TAIL,
};

enum DIRECTION {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct snake_t {
    size_t x;
    size_t y;
    GAME part;
    DIRECTION direction;
};

struct cell {
    std::string assets;
    char txt;
    size_t color;
};

class GameSnake : public IGame {
public:
    GameSnake();
    void init();
    void close();
    void update(std::queue<Event>);
    void updateMatrix();
    void setBackground();
    std::queue<AnyInstruction> convertMatrixToGfx();
    void moveUp() { _snake.front().y = (_snake.front().y - 1 + LINES) % LINES; }
    void moveDown() { _snake.front().y = (_snake.front().y + 1) % LINES; }
    void moveLeft() { _snake.front().x = (_snake.front().x - 1 + COLUMNS) % COLUMNS; }
    void moveRight() { _snake.front().x = (_snake.front().x + 1) % COLUMNS; }
    void moveSnake();
    std::queue<AnyInstruction> getGfxInstructions();
    ~GameSnake();
private:
    cell createCell(std::string assetLocation, char txt, size_t color)
    { cell newCell {assetLocation, txt, color}; return newCell; }
    std::map<GAME, cell> _assets {
            {EMPTY, createCell("games/Snake/assets/empty.png", ' ', 0)},
            {SCORE, createCell("games/Snake/assets/wild-jungle-font/WildJungleRegular-vnop9.ttf", '\0', 16777215)},
            {WALL, createCell("games/Snake/assets/wall.png", '#', 32768)},
            {FISH, createCell("games/Snake/assets/fish.png", '@', 16711680)},
            {HEAD, createCell("games/Snake/assets/head.png", '>', 255)},
            {TAIL, createCell("games/Snake/assets/tail.png", '<', 7845374)},
            {BODY, createCell("games/Snake/assets/body.png", '=', 3247335)}
    };
    std::map<DIRECTION, std::function<void(void)>> _directions;
    GameMatrix<GAME> _matrix;
    std::deque<snake_t> _snake;
    point_t _apple;
    size_t _score;
};
}