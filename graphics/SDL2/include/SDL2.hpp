/*
** EPITECH PROJECT, 2026
** Display
** File description:
** Display header
*/

#pragma once

#include "IDisplay.hpp"
#include <queue>
#include <SDL2/SDL.h>
#include <vector>


class SDL2 : public IDisplay {
public:
    struct rgba_t {
        int r;
        int g;
        int b;
        int a;
    };
    SDL2();
    void init() override;
    void close() override;
    void clear() override;
    void render(std::queue<AnyInstruction>) override;
    std::queue<Event> pollEvents() override;
    ~SDL2();

private:
    SDL_Window *_window;
    SDL_Renderer* _renderer;
    std::vector<SDL_Texture*> _textures;
    void DrawCircle(int x, int y, float radius, SDL_Renderer *renderer);
    rgba_t convert_rgba(int hexValue);
    void create_texture(const int width, const int height);
    void display_instruction(rectInstr &rectangle);
    void display_instruction(circleInstr &circle);
    void display_instruction(textInstr &text);
};
