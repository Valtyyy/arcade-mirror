/*
** EPITECH PROJECT, 2026
** IGame
** File description:
** header
*/

#pragma once

#include "gfx.hpp"
#include <queue>

class IGame {
    public:
        virtual void init() = 0;
        virtual void close() = 0;
        virtual void update(std::queue<Event>) = 0;
        virtual std::queue<AnyInstruction> getGfxInstructions() = 0;
};
