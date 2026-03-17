/*
** EPITECH PROJECT, 2026
** GFX
** File description:
** GFX header
*/

#pragma once

#include <cstddef>
#include <functional>
#include <map>
#include <tuple>
#include <vector>
#include <stack>
#include "shape.hpp"
#include <optional>

enum SHAPE_TYPE {
    RECT,
    CIRCLE,
    TEXT,
};

// to delete
template <typename T>
std::stack<std::tuple<SHAPE_TYPE, T>> gfxInstructions;
//

template <typename T>
struct GfxInstruction {
    size_t x;
    size_t y;
    std::optional<std::string> asset_location;
    size_t color_hex;
    SHAPE_TYPE type;
    std::optional<std::function<T()>> callback;
};

template <typename T>
struct rectInstr : public GfxInstruction<T> {
    size_t length;
    size_t width;
};

template <typename T>
struct circleInstr : public GfxInstruction<T> {
    size_t radius;
};

template <typename T>
struct textInstr : public GfxInstruction<T> {
    std::string text;
};

typedef struct gfx_s gfx_instr_t;
