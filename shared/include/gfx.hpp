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
    size_t length;
    size_t width;
};

struct circleInstr : public GfxInstruction {
    size_t radius;
};

struct textInstr : public GfxInstruction {
    std::string text;
};

using Event = std::variant<int, point_t>;

using AnyInstruction = std::variant<rectInstr, circleInstr, textInstr>;
