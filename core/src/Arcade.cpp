/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Arcade
*/

#include "Arcade.hpp"
#include "Display.hpp"
#include "Game.hpp"
#include "gfx.hpp"
#include <chrono>
#include <cstdio>
#include <queue>
#include <thread>
#include <iostream>

Core::Core(const std::string &display_lib, const std::string &game_lib) : _display(display_lib)
{
    std::cout << game_lib << std::endl;
}

void Core::run()
{
    bool running = true;
    const auto interval = std::chrono::microseconds(SECOND / IPS);

    while (running) {
        auto start = std::chrono::steady_clock::now();

        rectInstr rectangle = {1000, 100, "", 252, 100, 100};
        AnyInstruction rect = rectangle;
        circleInstr circle = {1500, 600, "", 120, 100};
        AnyInstruction circ = circle;
        std::queue<AnyInstruction> instructions = {};
        instructions.push(rect);
        instructions.push(circ);
        _display.render(instructions);
       // doIteration();
        auto elapsed = std::chrono::steady_clock::now() - start;
        if (elapsed < interval) {
            std::this_thread::sleep_for(interval - elapsed);
            continue;;
        }
        std::this_thread::sleep_for(interval);
    }
}

void Core::doIteration()
{
    //_game.update(_display.pollEvents());
    //_display.render(_game.getGfxInstructions());
}
