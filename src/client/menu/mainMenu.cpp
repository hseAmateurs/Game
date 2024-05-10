#include "mainMenu.h"
#include <sstream>
#include "statisticsMenu.h"
#include "friendEntry.h"
#include "friendsMenu.h"
#include "quickplayMenu.h"
#include "createjoinMenu.h"

MainMenu::MainMenu(const sf::Font& font,MenuManager* menuManager,Client& client) :
    Menu("Main Menu"),
    quickPlayButton(sf::Vector2f(710, 200), "Quick Play", font,25), // Example positions 
    joinLobbyButton(sf::Vector2f(710, 400), "Join Lobby", font,25),
    statisticsButton(sf::Vector2f(710, 600), "Statistics", font,25),
    friendsButton(sf::Vector2f(710, 800), "Friends", font,25),
    menuManager(menuManager)
{
    // Center the buttons horizontally
    // quickPlayButton.setOrigin(quickPlayButton.getSize().x / 2.f, 0.f);
    // joinLobbyButton.setOrigin(joinLobbyButton.getSize().x / 2.f, 0.f);
    // statisticsButton.setOrigin(statisticsButton.getSize().x / 2.f, 0.f);
    // friendsButton.setOrigin(friendsButton.getSize().x / 2.f, 0.f);

    login.setFont(font);
    login.setString(client.getLogin()); // Start with an empty string
    login.setCharacterSize(18); // Adjust size as needed 
    login.setFillColor(sf::Color::White);
    login.setPosition(50.f, 50.f);

    quickPlayButton.setSize(500.f, 100.f);
    quickPlayButton.setButtonColor(sf::Color(0, 0, 150));
    quickPlayButton.setHoverColor(sf::Color(0, 0, 200)); 

    joinLobbyButton.setSize(500.f, 100.f);
    joinLobbyButton.setButtonColor(sf::Color(0, 0, 150)); 
    joinLobbyButton.setHoverColor(sf::Color(0, 0, 200)); 

    statisticsButton.setSize(500.f, 100.f);
    statisticsButton.setButtonColor(sf::Color(0, 0, 150)); 
    statisticsButton.setHoverColor(sf::Color(0, 0, 200)); 
    
    friendsButton.setSize(500.f, 100.f);
    friendsButton.setButtonColor(sf::Color(0, 0, 150)); 
    friendsButton.setHoverColor(sf::Color(0, 0, 200)); 

}


void MainMenu::draw(sf::RenderWindow& window){
    quickPlayButton.draw(window);
    joinLobbyButton.draw(window);
    statisticsButton.draw(window);
    friendsButton.draw(window);
    window.draw(login);
}

MenuManager* MainMenu::getMenuManager() {
    return menuManager; 
}

void MainMenu::update(const sf::Time& deltaTime){}

void MainMenu::handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client){
    if(statisticsButton.isPressed(window)){
        MenuManager* menuManager=getMenuManager();
        if(menuManager){
            std::string message;
            message="301 "+client.getLogin();
            client.sendMessage(message.c_str());
            message=client.getMessage();
            if(message=="1"){
                return; // output something to the user? not now though 
            }
            else{
                std::stringstream ss(message);
                std::string deaths,kills,gamecount;
                ss >> deaths >> kills >> gamecount;
                client.setDeaths(deaths);
                client.setKills(kills);
                client.setGamecount(gamecount);
                menuManager->pushMenu(new StatisticsMenu(menuManager->getFont(),menuManager,client));
            }
        }
    }

    if(friendsButton.isPressed(window)){
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
                menuManager->pushMenu(new FriendsMenu(menuManager->getFont(),menuManager,client,vec));
            }
        }
    }

    if(quickPlayButton.isPressed(window)){
        MenuManager* menuManager=getMenuManager();
        if(menuManager){
            std::string message;
            message="501 "+client.getLogin();
            client.sendMessage(message.c_str());
            message=client.getMessage();
            menuManager->pushMenu(new QuickplayMenu(menuManager->getFont(),menuManager,client));            
        }
    }

    if(joinLobbyButton.isPressed(window)){
        MenuManager* menuManager=getMenuManager();
        if(menuManager){
            menuManager->pushMenu(new CreateJoinMenu(menuManager->getFont(),menuManager,client));            
        }
    }
}