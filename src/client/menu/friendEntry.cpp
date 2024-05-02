#include "friendEntry.h"

FriendEntry::FriendEntry(const std::string& username, const sf::Font& font) {
    friendText.setFont(font);
    friendText.setString(username);
    friendText.setCharacterSize(16); // Adjust size as needed 
    friendText.setFillColor(sf::Color::White);
}

void FriendEntry::draw(sf::RenderWindow& window) const {
    window.draw(friendText);
}