

#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include "screen.h"

class MenuScreen : public Screen
{

public:
    MenuScreen(sf::RenderWindow &window);

    void refreshScreen(sf::RenderWindow &window) override;
    void handleInput(sf::RenderWindow &window, std::function<void(const std::string &)> switchScreenCallback) override;
    void draw(sf::RenderWindow &window) override;

private:
    sf::Event m_event;
    std::vector<sf::Text> m_menuItems;
};

#endif // MENUSCREEN_H