#include "Snake.hpp"
#include "IGame.hpp"

extern "C" IGame *create()
{
    return new Snake();
}

Snake::Snake() : _matrix(20, 20, SNAKE::EMPTY, 1)
{
};

void Snake::init()
{
    _matrix.
};

void Snake::close()
{

};

void Snake::update(std::queue<Event>)
{
    _matrix.printMatrix();
};

std::queue<AnyInstruction> Snake::getGfxInstructions() { return {}; };

Snake::~Snake() {};

extern "C" LIB_TYPE getLibType()
{
    return GAME;
}