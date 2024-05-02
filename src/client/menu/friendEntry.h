#ifndef FRIENDENTRY_H
#define FRIENDENTRY_H

#include "menu.h"


class FriendEntry {
public:
    FriendEntry(const std::string& username, const sf::Font& font);

    void draw(sf::RenderWindow& window) const;

    void setPosition(const sf::Vector2f& position) { friendText.setPosition(position); }
    sf::Vector2f getSize() const { return friendText.getLocalBounds().getSize(); }

private:
    sf::Text friendText;
};

#endif 