#include "Snake.hpp"
#include "GameMatrix.hpp"
#include "IGame.hpp"
#include "Keys.hpp"
#include "gfx.hpp"
#include <cstddef>
#include <cstdio>
#include <ncurses.h>
#include <queue>
#include <chrono>
#include <stack>
#include <variant>

extern "C" IGame *create()
{
    return new Snake::GameSnake();
}

Snake::GameSnake::GameSnake() :
    _matrix(COLUMNS, LINES, Snake::EMPTY, TILESIZE) 
{
    _snake.push_front({11, 10, HEAD, UP});
    _snake.push_back({10, 10, BODY, RIGHT});
    _snake.push_back({9, 10, BODY, RIGHT});
    _snake.push_back({8, 10, TAIL, RIGHT});
    _fish.x = rand() % (COLUMNS - 1);
    _fish.y = rand() % (LINES - 1);
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

void Snake::GameSnake::moveUp()
{
    _snake.front().y = (_snake.front().y - 1 + LINES) % LINES;
}

void Snake::GameSnake::moveDown()
{
    _snake.front().y = (_snake.front().y + 1) % LINES;
}
void Snake::GameSnake::moveLeft()
{
    _snake.front().x = (_snake.front().x - 1 + COLUMNS) % COLUMNS;
}

void Snake::GameSnake::moveRight()
{
    _snake.front().x = (_snake.front().x + 1) % COLUMNS;
}

void Snake::GameSnake::updateMatrix()
{
    _matrix = GameMatrix<GAME>(COLUMNS, LINES, EMPTY, TILESIZE);
    setBackground();

    for (const auto &elem : _snake) {
        _matrix(elem.x, elem.y) = elem.part;
    }
    _matrix(_fish.x, _fish.y) = FISH;
}

void Snake::GameSnake::handleCollision()
{
    if (_matrix(_snake.front().x, _snake.front().y) == WALL) {
        std::cout << "WALL" << std::endl;
    }
    if (_matrix(_snake.front().x, _snake.front().y) == FISH) {
        std::cout << "FISH" << std::endl;
    }
}

void Snake::GameSnake::moveSnake()
{
    std::cout << "Size:" << _snake.size() << std::endl;
    for (size_t i = (_snake.size() - 1); i > 0; i--) {
        _snake[i].x = _snake[i - 1].x;
        _snake[i].y = _snake[i - 1].y;
        //printf(
        //    "Elem X %ld | Elem Y %ld | Part Elem %d / Next X %ld | Next Y %ld | Part Next %d\n",
        //    _snake[i].x, _snake[i].y, _snake[i].part, _snake[i + 1].x, _snake[i + 1].y, _snake[i + 1].part);
        std::cout << "Part:" << _snake[i].part << std::endl;
    }
    _directions[_snake.front().direction]();

}

void Snake::GameSnake::update(std::queue<Event> events)
{
    static auto start = std::chrono::steady_clock::now();
    const auto interval = std::chrono::milliseconds(400);
    CommonKey *key = 0;

    while (!events.empty()) {
        key = std::get_if<CommonKey>(&events.front());
        if (key && _keys.count(*key))
            _snake.front().direction = _keys[*key];
        events.pop();
    }
    auto now = std::chrono::steady_clock::now();
    if (now - start >= interval) {
        moveSnake();
        handleCollision();
        updateMatrix();
        start = now;
    }
}

std::queue<AnyInstruction> Snake::GameSnake::convertMatrixToGfx()
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
    return instructions;
}

std::queue<AnyInstruction> Snake::GameSnake::getGfxInstructions()
{
    std::queue<AnyInstruction> instructions = convertMatrixToGfx();

  //  std::cout << std::endl;
  //  _matrix.printMatrix();
  //  std::cout << std::endl;
    return instructions;
}

Snake::GameSnake::~GameSnake() {};

extern "C" LIB_TYPE getLibType()
{
    return GAME;
}