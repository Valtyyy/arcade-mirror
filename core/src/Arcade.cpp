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

Core::Core(const std::string &display_lib, const std::string &game_lib) : /*_game(game_lib), */ _display(display_lib)
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
        rectInstr rectangle = {{1000, 100, '\0',
            "/home/rayan/delivery/arcade/arcade-mirror/games/Snake/assets/apple.jpg", 252},
            100, 100};
        AnyInstruction rect = rectangle;
        circleInstr circle = {{1500, 600, '\0', "", 120}, 100};
        AnyInstruction circ = circle;
        textInstr text = {
            {{500, 400,'\0', "games/Snake/assets/wild-jungle-font/WildJungleRegular-vnop9.ttf", 16777215},
            500, 500,},"Salut", 200};
        AnyInstruction text_inst = text;
        std::queue<AnyInstruction> instructions = {};
        instructions.push(rect);
        instructions.push(circ);
        instructions.push(text_inst);
        _display.render(instructions);
        std::queue<Event> events = _display.pollEvents();
        //doIteration();
        auto elapsed = std::chrono::steady_clock::now() - start;
        if (elapsed < interval) {
            std::this_thread::sleep_for(interval - elapsed);
            continue;
        }
        std::this_thread::sleep_for(interval);
    }
}

void Core::doIteration()
{
    auto events = _display.pollEvents();

    if (_handle_command(events) < 0)
        return;

    //_game.update(events);
    //_display.render(_game.getGfxInstructions());
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
            _currentDisplay = (_currentDisplay + 1) % _displayList.size();
            _display = Display(_displayList[_currentDisplay]);
            break;
        case ASCII_M:
            _currentGame = (_currentGame + 1) % _gamesList.size();
          //  _game = Game(_gamesList[_currentGame]);
            break;
        case ASCII_O:
          //  _game = Game(_gamesList[_currentGame]);
            break;
        case ASCII_L:
       //     _game = Game(MENU_GAME);
            break;
        case ASCII_I:
            return -1;
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
    return {"to_fill"};
}

std::vector<std::string> Core::getDisplayList()
{
    return {"to_fill"};
}
