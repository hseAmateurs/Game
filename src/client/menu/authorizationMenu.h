#ifndef AUTHORIZATIONMENU_H
#define AUTHORIZATIONMENU_H

#include "menu.h"
#include "menuManager.h"
#include "textField.h"

class AuthorizationMenu : public Menu {
public:
    AuthorizationMenu(const sf::Font& font, MenuManager* menuManager);

    void draw(sf::RenderWindow& window) override;
    void handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client) override;

    void update(const sf::Time& deltaTime);
    MenuManager* getMenuManager();


private:
    Textfield usernameField;
    Textfield passwordField;
    MenuButton enterButton;
    MenuButton backButton;
    MenuManager* menuManager;
    sf::Text loginLabel;
    sf::Text passwordLabel;
    sf::Text errorMessage;
};

#endif