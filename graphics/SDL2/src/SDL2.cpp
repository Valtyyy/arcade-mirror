#include "SDL2.hpp"
#include "IDisplay.hpp"
#include "gfx.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL_render.h>
#include <cstddef>
#include <cstdio>
#include <numbers>
#include <stdexcept>
#include <variant>
#include <iostream>

extern "C" IDisplay *create()
{
    return new SDL2();
}

SDL2::SDL2() : _window(nullptr)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        throw std::runtime_error(SDL_GetError());
    if (TTF_Init() != 0)
        throw std::runtime_error(SDL_GetError());
    _events = {};
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

SDL_Color SDL2::convert_rgba(int hex_color)
{
    SDL_Color color;

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

void SDL2::createTextureFromSurface(SDL_Surface *surface, int x, int y, int w, int h)
{
    if (!surface)
        throw std::runtime_error(SDL_GetError());
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(_renderer, surface);
    if (!textTexture)
        throw std::runtime_error(SDL_GetError());
    SDL_Rect textRect = {x, y, w, h};

    _textures.push_back(textTexture);
    SDL_RenderCopy(_renderer, textTexture, NULL, &textRect);
}

void SDL2::display_instruction(rectInstr &rectangle)
{
    SDL_Color color = convert_rgba(rectangle.color_hex);
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {(int)rectangle.x, 
        (int)rectangle.y, (int)rectangle.w, (int)rectangle.h};
    SDL_RenderFillRect(_renderer, &rect);
    if (!rectangle.asset_location->empty()) {
        SDL_Surface *surface = IMG_Load(rectangle.asset_location->c_str());
        createTextureFromSurface(surface, rect.x, rect.y, rect.w, rect.h);
    }
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
    SDL_Color color = convert_rgba(circle.color_hex);

    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    DrawCircle(
        circle.x, 
        circle.y, 
        circle.radius, _renderer);
}

void SDL2::display_instruction(textInstr &text)
{
    SDL_Color color = convert_rgba(text.color_hex);
    TTF_Font *font = TTF_OpenFont(text.asset_location->c_str(), text.fontSize);
    if (!font)
        throw std::runtime_error(SDL_GetError());
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text.text.c_str(), color);
    if (!textSurface)
        throw std::runtime_error(SDL_GetError());
    createTextureFromSurface(textSurface, text.x, text.y, textSurface->w, textSurface->h);
}

void display_instruction(dimensionInstr &dimension)
{
    std::cout << "Dimension" << std::endl;
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

void SDL2::addEvents(SDL_KeyboardEvent &touch)
{
    int key = touch.keysym.sym;;
    Event event = key;

    printf("Key: %d\n", key);
    _events.push(event);
}

void SDL2::addEvents(SDL_MouseButtonEvent &click)
{
    if (click.button) {
        point_t point = {click.x, click.y};
        Event event = point;
        printf("X: %d Y: %d\n", point.x, point.y);
        _events.push(event);
    }
}

std::queue<Event> SDL2::pollEvents()
{
    SDL_Event sdl_event = {0};

    if (SDL_PollEvent(&sdl_event)) {
        if ((sdl_event.type == SDL_KEYUP) ||  (sdl_event.type  == SDL_KEYDOWN))
            addEvents(sdl_event.key);
        if ((sdl_event.type == SDL_MOUSEBUTTONUP) || (sdl_event.type == SDL_MOUSEBUTTONDOWN))
            addEvents(sdl_event.button);
        return _events;
    }
    return {};
}

extern "C" LIB_TYPE getLibType()
{
    return DISPLAY;
}

SDL2::~SDL2()
{
}
