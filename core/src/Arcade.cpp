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
#include <queue>
#include <thread>
#include <variant>

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
    auto events = _display.pollEvents();

    if (_handle_command(events) < 0)
        return;

    _game.update(events);
    _display.render(_game.getGfxInstructions());
}

int Core::_handle_command(std::queue<Event> events)
{
    Event curr;

    while (!events.empty()) {
        curr = events.front();
        if (std::holds_alternative<int>(curr) && _apply_command(std::get<int>(curr)) < 0)
            return -1;
        events.pop();
    }
    return 0;
}

int Core::_apply_command(int cmd)
{
    switch (cmd) {
        case ASCII_P:
            _display = Display(_);
            break;
        case ASCII_M:
            _game = Game("ll");
            break;
        case ASCII_O:
            _game.close();
            _game.init();
            break;
        case ASCII_L:
            _game = Game(MENU_GAME);
            break;
        case ASCII_I:
            return -1;
    }
}
