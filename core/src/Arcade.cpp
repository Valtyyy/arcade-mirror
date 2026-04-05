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
#include <queue>
#include <string>
#include <thread>
#include <variant>

Core::Core(const std::string &display_lib, const std::string &game_lib) : _game(game_lib), _display(display_lib)
{
    _displayList = getDisplayList();
    _gamesList = getGamesList();

    _currentDisplay = _findIndex(_displayList, display_lib);
    _currentGame = _findIndex(_gamesList, game_lib);
}

void Core::run()
{
    bool running = true;
    const auto interval = std::chrono::microseconds(SECOND / IPS);

    while (running) {
        auto start = std::chrono::steady_clock::now();

        if (doIteration() < 0)
            return;

        auto elapsed = std::chrono::steady_clock::now() - start;
        if (elapsed < interval) {
            std::this_thread::sleep_for(interval - elapsed);
            continue;
        }
        std::this_thread::sleep_for(interval);
    }
}

int Core::doIteration()
{
    auto events = _display.pollEvents();

    if (_handle_command(events) < 0)
        return -1;

    _game.update(events);
    _display.render(_game.getGfxInstructions());
    return 0;
}

int Core::_handle_command(std::queue<Event> events)
{
    Event curr;

    while (!events.empty()) {
        curr = events.front();
        if (std::holds_alternative<CommonKey>(curr) && _apply_command(std::get<CommonKey>(curr)) < 0)
            return -1;
        events.pop();
    }
    return 0;
}

int Core::_apply_command(CommonKey cmd)
{
    switch (cmd) {
        case CommonKey::P:
            _currentDisplay = (_currentDisplay + 1) % _displayList.size();
            _display = Display(_displayList[_currentDisplay]);
            break;
        case CommonKey::M:
            _currentGame = (_currentGame + 1) % _gamesList.size();
            _game = Game(_gamesList[_currentGame]);
            break;
        case CommonKey::O:
            _game = Game(_gamesList[_currentGame]);
            break;
        case CommonKey::L:
            _game = Game(MENU_GAME);
            break;
        case CommonKey::I:
            return -1;
        default:
            break;
    }
    return 0;
}

size_t Core::_findIndex(const std::vector<std::string> &list, const std::string &value)
{
    for (size_t i = 0; i < list.size(); ++i) {
        if (list[i] == value)
            return i;
    }
    return 0;
}

std::vector<std::string> Core::getGamesList()
{
    return {std::string(LIB_PATH) + "libarcade_snake.so"};
}

std::vector<std::string> Core::getDisplayList()
{
    return {std::string(LIB_PATH) + "libarcade_sfml.so", std::string(LIB_PATH) + "libarcade_sdl2.so"};
}
