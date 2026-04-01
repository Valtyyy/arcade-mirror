/*
** EPITECH PROJECT, 2026
** Display
** File description:
** Display header
*/

#pragma once

#include "IDisplay.hpp"
#include <SFML/Window/Mouse.hpp>
#include <cstdio>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class SFML : public IDisplay {
public:
    SFML();
    void init() override;
    void close() override;
    void clear() override;
    void render(std::queue<AnyInstruction>) override;
    std::queue<Event> pollEvents() override;
    ~SFML();

private:
    sf::RenderWindow _window;
    std::queue<Event> _events;
    std::vector<sf::Texture> _textures;
    void addEvents(sf::Keyboard::Key touch);
    void addEvents(sf::Event::MouseButtonEvent click);
    void create_texture(const int width, const int height);
    void display_instruction(rectInstr &rectangle);
    void display_instruction(circleInstr &circle);
    void display_instruction(textInstr &text);
};
