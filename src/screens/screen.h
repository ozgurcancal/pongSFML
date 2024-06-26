

#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include <iostream>
#include <any>

class Screen
{
public:
    Screen()
    {
        loadFont("assets/GreatVibes.otf"); // Specify the default font path
    }
    virtual ~Screen() = default;
    virtual void refreshScreen(sf::RenderWindow &window) = 0;
    virtual void handleInput(sf::RenderWindow &window, std::function<void(const std::string &)> switchScreenCallback) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
    // virtual void handleCollision(sf::Sprite &ps1, sf::Sprite &ps2, sf::Sprite &pb, sf::RenderWindow &window);

protected:
    sf::Font m_font;
    void loadFont(const std::string &fontPath)
    {
        if (!m_font.loadFromFile(fontPath))
        {
            std::cerr << "Error loading font" << std::endl;
        }
    }
    float m_speed = 1.0f;
};

#endif // SCREEN_H