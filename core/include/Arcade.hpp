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
        Core(const std::string &, const std::string &);
        void run();
        void doIteration();

    private:
        //Game _game;
        Display _display;
};
