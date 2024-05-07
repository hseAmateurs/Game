#include "QuickplayMenu.h"
#include <iostream>
#include "gameScreen.h"

QuickplayMenu::QuickplayMenu(const sf::Font& font, MenuManager* menuManager,Client& client) :
    Menu("Quick Play"),
    backButton(sf::Vector2f(50, 50), "Back", font,10), // Example position for top-right
    menuManager(menuManager)
{
    backButton.setSize(80.f, 30.f);
    backButton.setButtonColor(sf::Color(150, 0, 0)); // Red
    backButton.setHoverColor(sf::Color(200, 0, 0)); // Brighter red

    searchingText.setFont(font);
    searchingText.setString("Looking for players...");
    searchingText.setCharacterSize(30); // Adjust size as needed
    searchingText.setFillColor(sf::Color::White);
    searchingText.setPosition(400.f, 300.f); // Example position (center of screen)
}

MenuManager* QuickplayMenu::getMenuManager(){
    return menuManager; 
}

void QuickplayMenu::draw(sf::RenderWindow& window){
    backButton.draw(window);
    window.draw(searchingText); 
}

void QuickplayMenu::handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client){
    if(backButton.isPressed(window)){
        MenuManager* menuManager=getMenuManager();
        if(menuManager){
            std::string message;
            message="502 "+client.getLogin();
            client.sendMessage(message.c_str());
            message=client.getMessage(); // not supposed to fail anyway
            menuManager->popMenu(); // Go back to the previous menu
        }
    }
} 

void QuickplayMenu::update(const sf::Time& deltaTime,Client& client){
    // Update animation
    if(animationClock.getElapsedTime().asSeconds() > 0.5f){
        currentDotCount = (currentDotCount + 1) % 4; 
        std::string dots(currentDotCount,'.');
        searchingText.setString("Looking for players"+dots);
        animationClock.restart();
    }
    MenuManager* menuManager=getMenuManager();
    if(menuManager){
        std::string message;
        message="501 "+client.getLogin();
        client.sendMessage(message.c_str());
        message=client.getMessage();
        if(message=="1"){
            searchingText.setString("Lobby found! Launching game...");
            menuManager->pushMenu(new GameScreen(menuManager->getFont(),menuManager,client));            

        }
    }

}