/*
** EPITECH PROJECT, 2026
** IGame
** File description:
** header
*/

#pragma once

#include "gfx.hpp"
#include <stack>

class IGame {
    public:
        virtual void init() = 0;
        virtual void close() = 0;
        virtual void update() = 0;
        virtual std::stack<gfx_instr_t> getGFX() = 0;
        virtual void applyInput(std::stack<int>) = 0;
};
