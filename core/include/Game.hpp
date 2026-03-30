/*
** EPITECH PROJECT, 2026
** Game
** File description:
** Game header
*/

#pragma once

#include "IGame.hpp"
#include "DlLoader.hpp"

class Game : public IGame {
    public:
        Game(const std::string &lib_location);
        ~Game();

        void init() override;
        void close() override;
        void update(std::queue<Event>) override;
        std::queue<AnyInstruction> getGfxInstructions() override;
        LIB_TYPE getLibType() override;

    private:
        DlLoader _lib;
};
