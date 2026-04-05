/*
** EPITECH PROJECT, 2026
** Menu
** File description:
** Menu
*/

#include "Menu.hpp"
#include "IGame.hpp"
#include "Keys.hpp"
#include "gfx.hpp"
#include "DisplayVariable.hpp"
#include "MenuUtils.hpp"
#include "Utils.hpp"

#include <queue>
#include <chrono>

#define MENU_SCREEN_H SCREEN_H / 3
#define MENU_SCREEN_W SCREEN_W / 4


extern "C" LIB_TYPE getLibType()
{
    return LIB_TYPE::GAME;
}

extern "C" IGame *create()
{
    return new MenuGame();
}

void MenuGame::init()
{
}

void MenuGame::close()
{

}

void MenuGame::update(std::queue<Event> events)
{
    static auto start = std::chrono::steady_clock::now();
    const auto interval = std::chrono::milliseconds(400);
    CommonKey *key = 0;

    while (!events.empty()) {
        key = std::get_if<CommonKey>(&events.front());
        events.pop();
    }
    auto now = std::chrono::steady_clock::now();
    if (now - start >= interval) {
        start = now;
    }
}

std::queue<AnyInstruction> MenuGame::getGfxInstructions()
{
    std::queue<AnyInstruction> instructions;
    std::queue<AnyInstruction> button = MenuUtils::createButton(MENU_SCREEN_W, MENU_SCREEN_H, "games/Menu/assets/button.jpg");
    rectInstr background = {{0, 0, ' ', "games/Menu/assets/background.jpg"}, SCREEN_H, SCREEN_W};

    instructions.push((dimensionInstr){SCREEN_H, SCREEN_W});
    instructions.push(background);
    instructions = Utils::mergeQueues(instructions, button);

    return instructions;
}
