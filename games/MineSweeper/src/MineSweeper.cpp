/*
** EPITECH PROJECT, 2026
** MineSweeper
** File description:
** 
*/

#include "MineSweeper.hpp"

MineSweeper::Game::Game():
    _bombs(GameMatrix<cell>(0,0, {false, HIDE}, TILESIZE))
{
}

void MineSweeper::Game::setNeighbour(std::size_t x, std::size_t y)
{
    _bombs(x, y).isMine = true;
    for (int i = -1; i <= 1; i++) {
        for (int  j = -1; j <= 1; j++) {
            try {
                _bombs(x, y).neighboringBombs += 1;
            } catch (std::exception &e){
                std::cout << e.what() << std::endl;
                continue;
            }
        }
    }
    
}

void MineSweeper::Game::findNextNeighbour(std::size_t x, std::size_t y)
{
    std::size_t newX;
    std::size_t newY;
    for (size_t i = 0; i < MATRIXSIZE; i++) {
        newX = (x + ((i / 10) % MATRIXLEN)) % MATRIXLEN;
        newY = (y + (i % MATRIXLEN)) % MATRIXLEN;
        if (_bombs(newX, newY).isMine == false) {
            setNeighbour(newX, newY);
            return;
        }
    }
}

void MineSweeper::Game::init()
{
    std::size_t x = 0;
    std::size_t y = 0;
    _nbBombs = std::rand() % (MAXBOMB - MINBOMB) + MINBOMB;
    _bombs.resize(MATRIXLEN, MATRIXLEN);

    for (std::size_t i = 0; i < _nbBombs; i++) {
        x = std::rand() % MATRIXLEN;
        y = std::rand() % MATRIXLEN;
        if (!_bombs(x,y).isMine){
            findNextNeighbour(x, y);
            continue;
        }
        setNeighbour(x, y);
    }
}



void MineSweeper::Game::discoverTile(cell &tile)
{
    if (tile.visiblility == VISIBLE)
        return;
    if (_flagActive){
        tile.visiblility = FLAG;
    } else {
        tile.visiblility = VISIBLE;
        if (tile.isMine) {
            _isAlive = false;
        }
    }
}

void MineSweeper::Game::update(std::queue<Event> events)
{
    point_t *click;

    while (!events.empty()) {
        if (_isAlive){
            click = std::get_if<point_t>(&events.front());
            _bombs.onTileClick(*click, [this](MineSweeper::cell &tile) {discoverTile(tile);});
        }
        events.pop();
    }
}

void MineSweeper::Game::close()
{
    
}