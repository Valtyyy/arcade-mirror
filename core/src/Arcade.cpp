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
#include <cstddef>
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
        rectInstr rectangle = {{1000, 100,
            "/home/rayan/delivery/arcade/arcade-mirror/games/Snake/assets/apple.jpg", 252},
            100, 100};
        AnyInstruction rect = rectangle;
        circleInstr circle = {{1500, 600, "", 120}, 100};
        AnyInstruction circ = circle;
        textInstr text = {
            {{500, 400, "games/Snake/assets/wild-jungle-font/WildJungleRegular-vnop9.ttf", 16777215},
            500, 500,},"Salut", 200};
        AnyInstruction text_inst = text;
        std::queue<AnyInstruction> instructions = {};
        instructions.push(rect);
        instructions.push(circ);
        instructions.push(text_inst);
        _display.render(instructions);
        std::queue<Event> events = _display.pollEvents();
        doIteration();
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
