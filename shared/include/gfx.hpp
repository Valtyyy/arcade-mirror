/*
** EPITECH PROJECT, 2026
** GFX
** File description:
** GFX header
*/

#pragma once

#include <cstddef>
#include "shape.hpp"
#include <optional>
#include <variant>

typedef struct gfx_s gfx_instr_t;
typedef struct point_s {
    int x;
    int y;
} point_t;

struct GfxInstruction {
    size_t x;
    size_t y;
    char txt;
    std::optional<std::string> asset_location;
    size_t color_hex;
};

struct rectInstr : public GfxInstruction {
<<<<<<< HEAD
    size_t w;
    size_t h;
=======
    size_t h;
    size_t w;
>>>>>>> feat/core
};

struct circleInstr : public GfxInstruction {
    size_t radius;
};

struct  textInstr : public rectInstr {
    std::string text;
    size_t fontSize;
<<<<<<< HEAD
};

using Event = std::variant<int, point_t>;
using AnyInstruction = std::variant<rectInstr, circleInstr, textInstr>;
=======
};

struct dimensionInstr {
    size_t h;
    size_t w;
};

using Event = std::variant<int, point_t>;

using AnyInstruction = std::variant<rectInstr, circleInstr, textInstr, dimensionInstr>;
>>>>>>> feat/core
