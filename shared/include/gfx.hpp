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
    std::optional<std::string> asset_location;
    size_t color_hex;
};

struct rectInstr : public GfxInstruction {
    size_t w;
    size_t h;
};

struct circleInstr : public GfxInstruction {
    size_t radius;
};

struct  textInstr : public rectInstr {
    std::string text;
    size_t fontSize;
};

using Event = std::variant<int, point_t>;
using AnyInstruction = std::variant<rectInstr, circleInstr, textInstr>;