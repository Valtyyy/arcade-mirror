/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Arcade header
*/

#pragma once

#include "Display.hpp"
#include "Game.hpp"
#include <string>

#define EXIT_FAIL 84
#define EXIT_SUCCESS 0
#define IPS 15
#define SECOND 1000000
#define MENU_GAME LIB_PATH "libarcade_menu.so"

class Core {
    public:
        static int run(const std::string &display_lib);
        static void doIteration(Display, Game);
};
