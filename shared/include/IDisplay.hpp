/*
** EPITECH PROJECT, 2026
** IDisplay
** File description:
** IDsiplay declaration
*/

#pragma once

#include "gfx.hpp"
#include <queue>
#include <stack>

class IDisplay {
    public:
        virtual void init() = 0;
        virtual void close() = 0;
        virtual void clear() = 0;
        virtual void render(std::stack<AnyInstruction>) = 0;
        virtual std::queue<Event> pollEvents() = 0;
};
