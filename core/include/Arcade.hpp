/*
** EPITECH PROJECT, 2026
** Arcade
** File description:
** Arcade header
*/

#pragma once

#include "Display.hpp"
#include "Game.hpp"
#include "gfx.hpp"
#include <map>
#include <queue>
#include <string>
#include <vector>

#define EXIT_FAIL 84
#define EXIT_SUCCESS 0
#define IPS 15
#define SECOND 1000000
#define MENU_GAME LIB_PATH "libarcade_menu.so"

#define ASCII_O 0
#define ASCII_P 1
#define ASCII_L 2
#define ASCII_M 3
#define ASCII_I 4

class Core {
    public:
        Core(const std::string &, const std::string &);
        void run();
        void doIteration();

    private:
        int _handle_command(std::queue<Event>);
        int _apply_command(int);

        std::map<std::string, std::string> _gamesList;
        std::map<std::string, std::string> _displayList;

        static std::map<std::string, std::string> _getGamesList;
        static std::map<std::string, std::string> _getDisplayList;

        Game _game;
        Display _display;
        size_t currentGame;
        size_t currentDisplay;
};
