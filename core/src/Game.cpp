/*
** EPITECH PROJECT, 2026
** Game
** File description:
** Game declaration
*/

#include "Game.hpp"
#include "IGame.hpp"
#include <functional>
#include <memory>
#include <stdexcept>

Game::Game(const std::string &_lib_location) : _lib(_lib_location)
{
    _lib.load();

    std::function<LIB_TYPE()> getLibType = reinterpret_cast<LIB_TYPE(*)()>(_lib.sym("getLibType"));
    std::function<IGame*()> create = reinterpret_cast<IGame*(*)()>(_lib.sym("create"));

    if (getLibType() != LIB_TYPE::GAME)
        throw std::runtime_error("Error: " + _lib_location + " not a game library\n");

    _self = std::unique_ptr<IGame>(create());
    _self->init();
}

Game &Game::operator=(Game &&other) noexcept
{
    if (this != &other) {
        if (_lib.is_loaded())
            close();
        _lib = std::move(other._lib);
        _self = std::move(other._self);
    }
    return *this;
}

Game::~Game()
{
    if (_lib.is_loaded())
        close();
}

void Game::init()
{
    _self->init();
}

void Game::close()
{
    _self->close();
}

void Game::update(std::queue<Event> events)
{
    _self->update(events);
}

std::queue<AnyInstruction> Game::getGfxInstructions()
{
    return _self->getGfxInstructions();
}
