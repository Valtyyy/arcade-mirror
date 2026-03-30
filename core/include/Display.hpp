/*
** EPITECH PROJECT, 2026
** Display
** File description:
** Display header
*/

#pragma once

#include "IDisplay.hpp"
#include "DlLoader.hpp"

class Display : public IDisplay {
    public:
        Display(const std::string &lib_location);
        ~Display();

        void init() override;
        void close() override;
        void clear() override;
        void render(std::stack<AnyInstruction>) override;
        std::queue<Event> pollEvents() override;
        LIB_TYPE getLibType() override;

    private:
        DlLoader _lib;
};
