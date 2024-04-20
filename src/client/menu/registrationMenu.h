#ifndef REGISTRATIONMENU_H
#define REGISTRATIONMENU_H

#include "menu.h"
#include "menuManager.h"
#include "textField.h"

class RegistrationMenu : public Menu {
public:
    RegistrationMenu(const sf::Font& font, MenuManager* menuManager);

    void draw(sf::RenderWindow& window) override;
    void handleInput(const sf::Event& event, sf::RenderWindow& window) override;

    void update(const sf::Time& deltaTime);
    MenuManager* getMenuManager();


private:
    Textfield usernameField;
    Textfield passwordField;
    MenuButton enterButton;
    MenuButton backButton;
    MenuManager* menuManager;
};

#endif