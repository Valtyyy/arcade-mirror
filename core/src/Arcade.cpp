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

Core::Core(const std::string &display_lib, const std::string &game_lib) : _game(game_lib), _display(display_lib)
{

}

void Core::run()
{
    bool running = true;
    const auto interval = std::chrono::microseconds(SECOND / IPS);

    while (running) {
        auto start = std::chrono::steady_clock::now();

        doIteration();
        std::printf("AA\n");

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
    _game.update(_display.pollEvents());
    _display.render(_game.getGfxInstructions());
}
