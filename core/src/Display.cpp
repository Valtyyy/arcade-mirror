/*
** EPITECH PROJECT, 2026
** Display
** File description:
** Display declaration
*/

#include "Display.hpp"
#include "IGame.hpp"
#include <functional>
#include <stdexcept>

Display::Display(const std::string &_lib_location) : _lib(_lib_location)
{
    _lib.load();
    if (getLibType() != LIB_TYPE::DISPLAY)
        throw std::runtime_error("Error: " + _lib_location + " not a grapical library\n");
}

Display::~Display()
{
    if (_lib.is_loaded())
        close();
}

void Display::init()
{
    std::function<void()> func = reinterpret_cast<void(*)()>(_lib.sym("init"));

    return func();
}

void Display::close()
{
    std::function<void()> func = reinterpret_cast<void(*)()>(_lib.sym("close"));

    return func();
}

void Display::clear()
{
    std::function<void()> func = reinterpret_cast<void(*)()>(_lib.sym("clear"));

    return func();
}

void Display::render(std::stack<AnyInstruction> instructions)
{
    std::function<void(std::stack<AnyInstruction>)> func = reinterpret_cast<void(*)(std::stack<AnyInstruction>)>(_lib.sym("render"));

    return func(instructions);
}

std::queue<Event> Display::pollEvents()
{
    std::function<std::queue<Event>()> func = reinterpret_cast<std::queue<Event>(*)()>(_lib.sym("pollEvents"));

    return func();
}

LIB_TYPE Display::getLibType()
{
    std::function<LIB_TYPE()> func = reinterpret_cast<LIB_TYPE(*)()>(_lib.sym("getLibType"));

    return func();
}
