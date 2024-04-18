#ifndef AUTHORIZATIONMENU_H
#define AUTHORIZATIONMENU_H

#include "Menu.h"
#include "textField.h"

class AuthorizationMenu : public Menu {
public:
    AuthorizationMenu(const sf::Font& font);

    void draw(sf::RenderWindow& window) override;
    void handleInput(const sf::Event& event, sf::RenderWindow& window) override;

    void update(const sf::Time& deltaTime);


private:
    Textfield usernameField;
    Textfield passwordField;
    MenuButton enterButton;
    MenuButton backButton;
};

#endif