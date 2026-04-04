#include "Snake.hpp"
#include "IGame.hpp"
#include "gfx.hpp"
#include <queue>

extern "C" IGame *create()
{
    return new Snake();
}

Snake::Snake() : _matrix(20, 20, SNAKE::EMPTY, 1)
{
};

void Snake::init()
{

};

void Snake::close()
{

};

void Snake::update(std::queue<Event>)
{
};

std::queue<AnyInstruction> Snake::getGfxInstructions()
{
    rectInstr rectange = {0, 0, '\0', "", 16777215};
    std::queue<AnyInstruction> instruction;
    return instruction;
}
Snake::~Snake() {};

extern "C" LIB_TYPE getLibType()
{
    return GAME;
}