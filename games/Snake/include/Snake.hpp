/*
** EPITECH PROJECT, 2026
** IGame
** File description:
** header
*/

#pragma once

#include "IGame.hpp"
#include "Keys.hpp"
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
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    void moveSnake();
    void handleCollision();
    std::queue<AnyInstruction> getGfxInstructions();
    ~GameSnake();
private:
    using Func = std::function<void(void)>;

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
    std::map<DIRECTION, Func> _directions {
        {UP, [this]() -> void {moveUp();}},
        {DOWN, [this]() -> void { moveDown(); }},
        {LEFT, [this]() -> void { moveLeft(); }},
        {RIGHT, [this]() -> void { moveRight(); }}
    };
    std::map<CommonKey, DIRECTION> _keys {
        {CommonKey::UP, UP},
        {CommonKey::DOWN, DOWN},
        {CommonKey::LEFT, LEFT},
        {CommonKey::RIGHT, RIGHT}
    };
    GameMatrix<GAME> _matrix;
    std::deque<snake_t> _snake;
    point_t _fish;
    size_t _score;
};
}