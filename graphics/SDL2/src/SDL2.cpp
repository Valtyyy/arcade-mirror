#include "SDL2.hpp"
#include "IDisplay.hpp"
#include "IGame.hpp"
#include <SDL.h>
#include <SDL_error.h>
#include <SDL_render.h>
#include <cstddef>
#include <numbers>
#include <ostream>
#include <stdexcept>
#include <iostream>
#include <utility>
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
    _textures = {};
}

void SDL2::close()
{
    for (auto elem : _textures)
        SDL_DestroyTexture(elem);
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void SDL2::clear()
{

}

SDL2::rgba_t SDL2::convert_rgba(int hex_color)
{
    rgba_t color;

    color.r = ((hex_color >> 24) & 0xFF) ;
    color.g = ((hex_color >> 16) & 0xFF);
    color.g = ((hex_color >> 8) & 0xFF);
    color.b = ((hex_color) & 0xFF);
    return color;
}

void SDL2::create_texture(const int width, const int height)
{
    SDL_Texture *texture =
    SDL_CreateTexture(_renderer,
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_TARGET,
    width,
    height);
    if (!texture)
        throw std::runtime_error(SDL_GetError());
    _textures.push_back(std::move(texture));
}

void SDL2::display_instruction(rectInstr &rectangle)
{
    rgba_t color = convert_rgba(rectangle.color_hex);
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {(int)rectangle.x, 
        (int)rectangle.y, (int)rectangle.width, (int)rectangle.length};
    SDL_RenderFillRect(_renderer, &rect);
    if (rectangle.asset_location)
        create_texture(rectangle.width, rectangle.length);
}

void SDL2::DrawCircle(int x, int y, float radius, SDL_Renderer *renderer)
{
    double pi = std::numbers::pi;
    int precision = 1000;
    double step = pi / (double)(precision - 1);

    for (int i = 0; i < precision; i++) {
        float x1 = cos(-i * step) * radius + x;
        float y1 = sin(-i * step) * radius + y;
        float x2 = cos(i * step) * radius + x;
        float y2 = sin(i * step) * radius + y;
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
}

void SDL2::display_instruction(circleInstr &circle)
{
    rgba_t color = convert_rgba(circle.color_hex);
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    DrawCircle(
        circle.x, 
        circle.y, 
        circle.radius, _renderer);
}

void SDL2::display_instruction(textInstr &text)
{
    std::cout << "TEXT" << std::endl;
}

void SDL2::render(std::queue<AnyInstruction> instructions)
{
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
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
