/*
** EPITECH PROJECT, 2026
** Display
** File description:
** Display header
*/

#pragma once

#include "IDisplay.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_test_font.h>
#include <cstdio>


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
    std::vector<SDL_Texture*> _textures;
    std::queue<Event> _events;
    
    void addEvents(SDL_KeyboardEvent &);
    void addEvents(SDL_MouseButtonEvent &);
    void DrawCircle(int x, int y, float radius, SDL_Renderer *renderer);
    SDL_Color convert_rgba(int hexValue);
    void create_texture(const int width, const int height);
    void createTextureFromSurface(SDL_Surface *surface,
        int x, int y, int w, int h);
    void display_instruction(rectInstr &rectangle);
    void display_instruction(circleInstr &circle);
    void display_instruction(textInstr &text);
};
