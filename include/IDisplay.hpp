/*
** EPITECH PROJECT, 2026
** IDisplay
** File description:
** IDsiplay declaration
*/

#pragma once

#include "gfx.hpp"
#include <stack>

class IDisplay {
    public:
        virtual void init() = 0;
        virtual void close() = 0;
        virtual std::stack<int> getInput() = 0;
        virtual void render(std::stack<gfx_instr_t>) = 0;  
};
