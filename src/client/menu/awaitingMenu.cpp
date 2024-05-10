#include "awaitingMenu.h"
#include <iostream>
#include "gameScreen.h"

AwaitingMenu::AwaitingMenu(const sf::Font& font, MenuManager* menuManager,Client& client) :
    Menu("Waiting"),
    menuManager(menuManager)
{
    searchingText.setFont(font);
    searchingText.setString("Waiting for players...");
    searchingText.setCharacterSize(30); // Adjust size as needed
    searchingText.setFillColor(sf::Color::White);
    searchingText.setPosition(400.f, 300.f); // Example position (center of screen)

}

MenuManager* AwaitingMenu::getMenuManager(){
    return menuManager; 
}

void AwaitingMenu::draw(sf::RenderWindow& window){
    window.draw(searchingText); 
}

void AwaitingMenu::handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client){
} 

void AwaitingMenu::update(const sf::Time& deltaTime,Client& client){
    // Update animation
    if(animationClock.getElapsedTime().asSeconds() > 0.5f){
        currentDotCount = (currentDotCount + 1) % 4; 
        std::string dots(currentDotCount,'.');
        searchingText.setString("Waiting for players"+dots);
        animationClock.restart();
    }
    MenuManager* menuManager=getMenuManager();
    if(menuManager){
        std::string message=client.getMsg();
        client.sendMessage(message.c_str());
        message=client.getMessage();
        if(message=="1"){
            searchingText.setString("Everyone joined! Launching game...");
            menuManager->pushMenu(new GameScreen(menuManager->getFont(),menuManager,client));            

        }
    }

}