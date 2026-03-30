/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Arcade
*/

#include "Arcade.hpp"
#include "Display.hpp"
#include "Game.hpp"
#include <chrono>
#include <cstdio>
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

       // doIteration();

       std::cout << "RUN " << std::endl;
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
