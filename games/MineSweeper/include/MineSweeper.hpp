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
        int neighboringBombs;
    };

    #define TILESIZE 50
    #define MATRIXLEN 13
    #define MATRIXSIZE MATRIXLEN * MATRIXLEN
    #define MAXBOMB 15
    #define MINBOMB 25
    #define TILEASSET "games/MineSweeper/asset/tileMineSweeper.jpg"

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
        point_t findCoords(cell &target);
        void discoverAdjacent(point_t pos);

    private:
        GameMatrix<cell> _bombs;

        textInstr _endGameScreen;
        std::unordered_map<int, std::string> _tileAsset {
            {-1, "games/MineSweeper/asset/bomb.jpg"},
            {0, "games/MineSweeper/asset/TileEmpty.png"},
            {1, "games/MineSweeper/asset/Tile1.png"},
            {2, "games/MineSweeper/asset/Tile2.png"},
            {3, "games/MineSweeper/asset/Tile3.png"},
            {4, "games/MineSweeper/asset/Tile4.png"},
            {5, "games/MineSweeper/asset/Tile5.png"},
            {6, "games/MineSweeper/asset/Tile6.png"},
            {7, "games/MineSweeper/asset/Tile7.png"},
            {8, "games/MineSweeper/asset/Tile8.png"},
        };
        bool _isAlive = true;
        bool _flagActive = false;
        std::size_t _nbBombs;
    };
}