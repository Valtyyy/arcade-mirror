#include "Snake.hpp"
#include "GameMatrix.hpp"
#include "IGame.hpp"
#include "Key.hpp"
#include "gfx.hpp"
#include <cstddef>
#include <cstdio>
#include <queue>
#include <chrono>
#include <thread>
#include <stack>
#include <variant>

extern "C" IGame *create()
{
    return new Snake::GameSnake();
}

Snake::GameSnake::GameSnake() :
    _matrix(COLUMNS, LINES, Snake::EMPTY, TILESIZE) 
{
    _snake.push_front({11, 10, HEAD, RIGHT});
    _snake.push_back({10, 10, BODY, RIGHT});
    _snake.push_back({9, 10, BODY, RIGHT});
    _snake.push_back({8, 10, TAIL, RIGHT});
    _directions[UP] = [this]() { moveUp(); };
    _directions[DOWN] = [this]() { moveDown(); };
    _directions[LEFT] = [this]() { moveLeft(); };
    _directions[RIGHT] = [this]() { moveRight(); };
};

void Snake::GameSnake::setBackground()
{
    for (size_t x = 0; x < COLUMNS; x++)
            _matrix(x, 0) = WALL;
    for (size_t x = 0; x < COLUMNS; x++)
        _matrix(x, LINES - 1) = WALL;
    for (size_t y = 0; y < LINES; y++)
            _matrix(0, y) = WALL;
    for (size_t y = 0; y < LINES; y++)
            _matrix(COLUMNS - 1, y) = WALL;  
}

void Snake::GameSnake::init()
{
    setBackground();
};

void Snake::GameSnake::close()
{

};

void Snake::GameSnake::updateMatrix()
{
    _matrix = GameMatrix<GAME>(COLUMNS, LINES, EMPTY, TILESIZE);
    setBackground();

    for (const auto &elem : _snake) {
        _matrix(elem.x, elem.y) = elem.part;
    }
}

void Snake::GameSnake::moveSnake()
{
    snake_t element = {};
    GAME part = {};

    for (size_t i = 0; i < _snake.size(); i++) {
        
    }
}

void Snake::GameSnake::update(std::queue<Event> events)
{
    static auto lastMove = std::chrono::steady_clock::now();
    const auto interval = std::chrono::milliseconds(100);
    int *key = 0;

    while (!events.empty()) {
        key = std::get_if<int>(&events.front());
        moveSnake();
        events.pop();
    }
    auto now = std::chrono::steady_clock::now();
    if (now - lastMove >= interval) {
        moveSnake();
        updateMatrix();
        lastMove = now;
    }
}

std::queue<AnyInstruction> Snake::GameSnake::getGfxInstructions()
{
    std::queue<AnyInstruction> instructions = {};
    std::stack<rectInstr> matrixInstruction =_matrix.matrixToGFX("", 5);
    point_t coordonates = {0, 0};
    GAME type = EMPTY;

    while (!matrixInstruction.empty()) {
        rectInstr tile = matrixInstruction.top();
        coordonates.x = tile.x / TILESIZE;
        coordonates.y = tile.y / TILESIZE;
        type = _matrix(coordonates.x, coordonates.y);
        tile.asset_location = _assets[type].assets;
        tile.txt = _assets[type].txt;
        tile.color_hex = _assets[type].color;
        instructions.push(tile);
        matrixInstruction.pop();
    }
   // std::cout << std::endl;
   // _matrix.printMatrix();
   // std::cout << std::endl;
    return instructions;
}

Snake::GameSnake::~GameSnake() {};

extern "C" LIB_TYPE getLibType()
{
    return GAME;
}