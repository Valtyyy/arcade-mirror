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

        static std::vector<std::string> getGamesList();
        static std::vector<std::string> getDisplayList();

    private:
        int _handle_command(std::queue<Event>);
        int _apply_command(int);
        static size_t _findIndex(const std::vector<std::string> &, const std::string &);

        Game _game;
        Display _display;
        size_t _currentGame;
        size_t _currentDisplay;
        std::vector<std::string> _gamesList;
        std::vector<std::string> _displayList;
};
