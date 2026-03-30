#include "SDL2.hpp"
#include "IDisplay.hpp"
#include "IGame.hpp"
#include <SDL.h>
#include <SDL_error.h>
#include <SDL_render.h>
#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <iostream>
#include <variant>

extern "C" IDisplay *create()
{
    return new SDL2();
}

SDL2::SDL2() : _window(nullptr)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw std::runtime_error(SDL_GetError());
}

void SDL2::init()
{
    _window = SDL_CreateWindow("SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1920,
        1080,
        SDL_WINDOW_RESIZABLE);
    if (!_window)
        throw std::runtime_error(SDL_GetError());
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED); 
}

void SDL2::close()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void SDL2::clear()
{

}

void SDL2::display_instruction(rectInstr &rectangle)
{
    SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
    SDL_Rect rect = {(int)rectangle.x, 
        (int)rectangle.y, (int)rectangle.width, (int)rectangle.length};
    SDL_RenderDrawRect(_renderer, &rect);
}

void SDL2::display_instruction(circleInstr &circle)
{
    std::cout << "CERCLE" << std::endl;

}

void SDL2::display_instruction(textInstr &text)
{
    std::cout << "TEXT" << std::endl;
}

void SDL2::render(std::queue<AnyInstruction> instructions)
{
    SDL_SetRenderDrawColor(_renderer, 255, 200, 100, 255);
    SDL_RenderClear(_renderer);

    while (!instructions.empty()) {
        std::visit([this](auto &arg){ display_instruction(arg); },
        instructions.front());
        instructions.pop();
    }
    SDL_RenderPresent(_renderer);
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
