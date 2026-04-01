#include "IDisplay.hpp"
#include "SFML.hpp"
#include "gfx.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <ostream>

extern "C" IDisplay *create()
{
    return new SFML();
}

SFML::SFML() : _window(sf::VideoMode(1920, 1080), 
        "SFML",
        sf::Style::Default) {}

void SFML::init()
{
    _window.setFramerateLimit(60);
    _window.clear(sf::Color::Blue);
}

void SFML::close()
{
    _window.close();
}

void SFML::clear()
{
}

void SFML::display_instruction(rectInstr &rectangle)
{
    sf::RectangleShape rect(sf::Vector2f(rectangle.w, rectangle.h));
    rect.setPosition(sf::Vector2f(rectangle.x, rectangle.y));

    if (!rectangle.asset_location->empty()) {
        _textures.emplace_back();
        _textures.back().loadFromFile(rectangle.asset_location->c_str());
        rect.setTexture(&_textures.back());
        rect.setTextureRect(sf::IntRect(0, 0,
            _textures.back().getSize().x,
            _textures.back().getSize().y));
    }
    else
        rect.setFillColor(sf::Color(rectangle.color_hex));
    _window.draw(rect);
}

void SFML::display_instruction(circleInstr &circle)
{
    sf::CircleShape circ(circle.radius);
    circ.setFillColor(sf::Color(circle.color_hex));
    circ.setPosition(sf::Vector2f(circle.x, circle.y));

    if (!circle.asset_location->empty()) {
        _textures.emplace_back();
        _textures.back().loadFromFile(circle.asset_location->c_str());
        circ.setTexture(&_textures.back());
        circ.setTextureRect(sf::IntRect(0, 0,
            _textures.back().getSize().x,
            _textures.back().getSize().y));
    }
    _window.draw(circ);
}

void SFML::display_instruction(textInstr &text)
{
    sf::Font font;

    font.loadFromFile(text.asset_location->c_str());
    sf::Text Text(text.text, font, text.fontSize);
    Text.setFillColor(sf::Color(text.color_hex));
    Text.setPosition(sf::Vector2f(text.x, text.y));
    _window.draw(Text);
}

void SFML::display_instruction(dimensionInstr &text)
{
    std::cout << "DIMENSTION" << std::endl;
}

void SFML::render(std::queue<AnyInstruction> instructions)
{
    _window.clear(sf::Color::Transparent);
    while (!instructions.empty()) {
        std::visit(
            [this](auto &arg) { display_instruction(arg); },
        instructions.front());
        instructions.pop();
    }
    _window.display();
    _textures.clear();
}

void SFML::addEvents(sf::Keyboard::Key touch)
{
    int key = static_cast<char>(touch - sf::Keyboard::A + 'a');;
    Event event = key;

    printf("Key: %d\n", key);
    _events.push(event);
}

void SFML::addEvents(sf::Event::MouseButtonEvent click)
{
    point_t point = {click.x, click.y};
    Event event = point;

    printf("X: %d Y: %d\n", point.x, point.y);
    _events.push(event);
}

std::queue<Event> SFML::pollEvents()
{
    sf::Event event;

    if  (_window.pollEvent(event)) {
        if ((event.type == sf::Event::KeyPressed) || (event.type == sf::Event::KeyReleased))
            addEvents(sf::Keyboard::localize(event.key.scancode));
        sf::Mouse::getPosition();
        if ((event.type == sf::Event::MouseButtonPressed) || event.type == sf::Event::MouseButtonReleased)
            addEvents(event.mouseButton);
        return _events;
    }
    return {};
}

extern "C" LIB_TYPE getLibType()
{
    return DISPLAY;
}

SFML::~SFML()
{

}
