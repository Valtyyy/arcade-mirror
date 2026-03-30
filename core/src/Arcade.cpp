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

int Core::run(const std::string &display_lib)
{
    //Display display(display_lib);
    //Game game(MENU_GAME);
    bool running = true;
    const auto interval = std::chrono::microseconds(SECOND / IPS);

    while (running) {
        auto start = std::chrono::steady_clock::now();

        //doIteration(display, game);
        std::printf("AA\n");

        auto elapsed = std::chrono::steady_clock::now() - start;
        if (elapsed < interval) {
            std::this_thread::sleep_for(interval - elapsed);
            continue;;
        }
        std::this_thread::sleep_for(interval);
    }
    return EXIT_SUCCESS;
}
