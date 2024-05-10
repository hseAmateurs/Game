#include "createjoinMenu.h"
#include "lobbyMenu.h"
#include <sstream>
#include "friendEntry.h"
#include "menuManager.h"
#include "invitationMenu.h"

CreateJoinMenu::CreateJoinMenu(const sf::Font& font, MenuManager* menuManager,Client& client) :
    Menu("Choice Menu"),
    createButton(sf::Vector2f(710, 400), "Create Lobby", font),
    joinButton(sf::Vector2f(710, 600), "Join Lobby", font),
    backButton(sf::Vector2f(1400, 50), "Back", font,15),
    menuManager(menuManager)
{
    createButton.setSize(500.f, 100.f);
    joinButton.setSize(500.f, 100.f);

    backButton.setSize(80.f, 30.f);
    backButton.setButtonColor(sf::Color(150, 0, 0)); // Red
    backButton.setHoverColor(sf::Color(200, 0, 0)); // Brighter red
}

void CreateJoinMenu::draw(sf::RenderWindow& window) {
    createButton.draw(window);
    joinButton.draw(window);
    backButton.draw(window);
}

MenuManager* CreateJoinMenu::getMenuManager(){
    return menuManager; 
}

void CreateJoinMenu::handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client) {
    if (createButton.isPressed(window)) {
        MenuManager* menuManager=getMenuManager();
        if(menuManager){
            std::string message;
            message="401 "+client.getLogin();
            client.sendMessage(message.c_str());    
            message=client.getMessage();
            if(message=="1"){
                return;
            }
            else{
                std::stringstream ss(message);
                std::vector<FriendEntry> vec;
                std::string username;
                while(std::getline(ss,username,' ')){
                    if(username!="0"){
                        FriendEntry friendentry(username,menuManager->getFont());
                        vec.push_back(friendentry);
                    }
                }   
                menuManager->pushMenu(new LobbyMenu(menuManager->getFont(),menuManager,client,vec));
            }
        }
    } 

    if (joinButton.isPressed(window)) {
        MenuManager* menuManager = getMenuManager();
        if (menuManager) {
            menuManager->pushMenu(new InvitationMenu(menuManager->getFont(),menuManager,client));
        }
    }
    
    if(backButton.isPressed(window)){
        MenuManager* menuManager=getMenuManager();
        if(menuManager){
            menuManager->popMenu();
        } 
    }
}

