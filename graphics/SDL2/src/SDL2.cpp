#include "SDL2.hpp"
#include "IDisplay.hpp"
#include "IGame.hpp"
#include <ostream>
#include <iostream>

extern "C" IDisplay *create()
{
    return new SDL2();
}

SDL2::SDL2()
{
}

void SDL2::init()
{
    std::cout << "INIt" << std::endl;
}

void SDL2::close()
{

}

void SDL2::clear()
{
}

void SDL2::render(std::queue<AnyInstruction>)
{
}

std::queue<Event> SDL2::pollEvents()
{
    return {};
}

extern "C" LIB_TYPE getLibType()
{
    return DISPLAY;
}

SDL2::~SDL2()
{
}
