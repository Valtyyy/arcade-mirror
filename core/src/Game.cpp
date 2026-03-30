/*
** EPITECH PROJECT, 2026
** Game
** File description:
** Game declaration
*/

#include "Game.hpp"
#include "IGame.hpp"
#include <functional>
#include <stdexcept>

Game::Game(const std::string &_lib_location) : _lib(_lib_location)
{
    _lib.load();
    if (getLibType() != LIB_TYPE::GAME)
        throw std::runtime_error("Error: " + _lib_location + " not a game library\n");
}

Game::~Game()
{
    if (_lib.is_loaded())
        close();
}

void Game::init()
{
    std::function<void()> func = reinterpret_cast<void(*)()>(_lib.sym("init"));

    return func();
}

void Game::close()
{
    std::function<void()> func = reinterpret_cast<void(*)()>(_lib.sym("close"));

    return func();
}

void Game::update(std::queue<Event> events)
{
    std::function<void(std::queue<Event>)> func = reinterpret_cast<void(*)(std::queue<Event>)>(_lib.sym("update"));

    return func(events);
}

std::queue<AnyInstruction> Game::getGfxInstructions()
{
    std::function<std::queue<AnyInstruction>()> func = reinterpret_cast<std::queue<AnyInstruction>(*)()>(_lib.sym("getGfxInstructions"));

    return func();
}

LIB_TYPE Game::getLibType()
{
    std::function<LIB_TYPE()> func = reinterpret_cast<LIB_TYPE(*)()>(_lib.sym("getLibType"));

    return func();
}
