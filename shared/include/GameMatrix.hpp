/*
** EPITECH PROJECT, 2026
** GameMatrix
** File description:
** 
*/

#pragma once

#include "IGame.hpp"
#include "gfx.hpp"
#include <vector>
#include <exception>
#include <sstream>
#include <iostream>
#include <stack>


template <typename T>
class GameMatrix {
    public:
        GameMatrix(std::size_t columns, std::size_t lines, T defaultValue, std::size_t tileSize):
        _lines(lines),
        _columns(columns),
        _tileSize(tileSize),
        _defaultValue(defaultValue)
        {
            _matrix.resize(_lines, std::vector<T>(_columns));
            for (std::vector<T> &elem : _matrix) {
                elem.resize(_columns, _defaultValue);
            }
        };


        GfxInstruction<void> createTileGFX()
        {
            rectInstr<void> tileGFX;

            tileGFX.type = SHAPE_TYPE::RECT;
            tileGFX.length = _tileSize;
            tileGFX.width = _tileSize;
            return tileGFX;
        }

        std::stack<GfxInstruction<void>> &matrixToGFX(std::size_t color = 0)
        {
            GfxInstruction<void> tileGFX;

            for (std::size_t y; y < _matrix.size(); y++){
                for (std::size_t x; x < _matrix.size(); x++){
                    tileGFX = createTileGFX();
                    tileGFX.color_hex = color;
                    tileGFX.x = x * _tileSize;
                    tileGFX.y = y * _tileSize;
                    instruct.push(tileGFX);
                }
            }
            return instruct;
        };

        std::stack<GfxInstruction<void>> matrixToGFX(std::string asset)
        {
            GfxInstruction<void> tileGFX;

            for (std::size_t y; y < _matrix.size(); y++){
                for (std::size_t x; x < _matrix.size(); x++){
                    tileGFX = createTileGFX();
                    tileGFX.asset_location = asset;
                    tileGFX.x = x * _tileSize;
                    tileGFX.y = y * _tileSize;
                    instruct.push(tileGFX);
                }
            }
            return instruct;
        };

        void resize(std::size_t newColumns, std::size_t newLines)
        {
            _lines = newLines;
            _columns = newColumns;
            _matrix.resize(_lines, std::vector<T>(_columns));
            for (std::vector<T> &elem : _matrix) {
                elem.resize(_columns, _defaultValue);
            }
        };

        T& operator()(std::size_t x, std::size_t y) 
        {
            if (x > (_columns - 1) || y > (_lines - 1)){
                throw SizeError(x, y);
            }
            return _matrix[y][x];
        };

        void printMatrix()
        {
            for (std::vector<T> line : _matrix){
                for (T &elem : line) {
                    std::cout << elem;
                }
                std::cout << std::endl;
            }

        };

        class SizeError : public std::exception
        {
            private:
                std::string msg;
            public:
                SizeError(std::size_t x, std::size_t y)
                {
                    std::stringstream tmp;

                    tmp << "the coordinate (" << x << "," << y << ") doesnt fit the matrix";
                    msg = tmp.str();
                };
                const char* what() const noexcept override{
                    return msg.c_str();
                }
        };
    private:
        std::stack<GfxInstruction<void>> instruct;
        std::vector<std::vector<T>> _matrix;
        std::size_t _lines;
        std::size_t _columns;
        std::size_t _tileSize;
        T _defaultValue;
};
