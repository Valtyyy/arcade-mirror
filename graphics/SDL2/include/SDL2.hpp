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


class SDL2 : public IDisplay {
public:
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
    void display_instruction(rectInstr &rectangle);
    void display_instruction(circleInstr &circle);
    void display_instruction(textInstr &text);
};
