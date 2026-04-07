/*
** EPITECH PROJECT, 2026
** Minesweeper
** File description:
** 
*/

#pragma once

#include "IGame.hpp"
#include "Keys.hpp"
#include "gfx.hpp"
#include "GameMatrix.hpp"


namespace MineSweeper
{
    enum VISIBILITY {
        HIDE,
        VISIBLE,
        FLAG,
    };

    struct cell {
        bool isMine;
        VISIBILITY visiblility;
        std::size_t neighboringBombs;
    };

    #define TILESIZE 40
    #define MATRIXLEN 10
    #define MATRIXSIZE 100
    #define MAXBOMB MATRIXSIZE / 2
    #define MINBOMB MATRIXSIZE / 3

    class Game : public IGame 
    {
    public:
        Game();
        ~Game();

        void init() override;
        void close() override;
        void update(std::queue<Event>) override;
        std::queue<AnyInstruction> getGfxInstructions() override;
        void discoverTile(cell &tile);
        void setNeighbour(std::size_t x, std::size_t y);
        void findNextNeighbour(std::size_t x, std::size_t y);

    private:
        GameMatrix<cell> _bombs;

        bool _isAlive = true;
        bool _flagActive = false;
        std::size_t _nbBombs;
    };
}