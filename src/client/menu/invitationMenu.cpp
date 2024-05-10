#include "invitationMenu.h"
#include <iostream>
#include "gameScreen.h"

InvitationMenu::InvitationMenu(const sf::Font& font, MenuManager* menuManager,Client& client) :
    Menu("Invitation"),
    menuManager(menuManager)
{
    searchingText.setFont(font);
    searchingText.setString("Waiting to be invited...");
    searchingText.setCharacterSize(30); // Adjust size as needed
    searchingText.setFillColor(sf::Color::White);
    searchingText.setPosition(400.f, 300.f); // Example position (center of screen)
}

MenuManager* InvitationMenu::getMenuManager(){
    return menuManager; 
}

void InvitationMenu::draw(sf::RenderWindow& window){
    window.draw(searchingText); 
}

void InvitationMenu::handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client){} 

void InvitationMenu::update(const sf::Time& deltaTime,Client& client){
    // Update animation
    if(animationClock.getElapsedTime().asSeconds() > 0.5f){
        currentDotCount = (currentDotCount + 1) % 4; 
        std::string dots(currentDotCount,'.');
        searchingText.setString("Waiting to be invited"+dots);
        animationClock.restart();
    }
    MenuManager* menuManager=getMenuManager();
    if(menuManager){
        std::string message;
        message="603 "+client.getLogin();
        client.sendMessage(message.c_str());
        message=client.getMessage();
        if(message=="1"){
            searchingText.setString("Joined a lobby! Launching game...");
            menuManager->pushMenu(new GameScreen(menuManager->getFont(),menuManager,client));            

        }
    }

}