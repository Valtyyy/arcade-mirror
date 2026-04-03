/*
** EPITECH PROJECT, 2026
** IGame
** File description:
** header
*/

#pragma once

#include "IGame.hpp"
#include "gfx.hpp"
#include <deque>
#include <queue>
#include <vector>
#include <deque>
#include "GameMatrix.hpp"

enum SNAKE {
    EMPTY,
    WALL,
    HEAD,
    BODY,
    APPLE,
};

class Snake : public IGame {
public:
    Snake();
    void init();
    void close();
    void update(std::queue<Event>);
    std::queue<AnyInstruction> getGfxInstructions();
    ~Snake();
private:
    GameMatrix<SNAKE> _matrix;
    std::deque<point_t> _snake;
    point_t _apple;
};
