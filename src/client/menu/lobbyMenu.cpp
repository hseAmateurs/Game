#include <algorithm>
#include "friendEntry.h"
#include "lobbyMenu.h"
#include "awaitingMenu.h"
#include <iostream>

LobbyMenu::LobbyMenu(const sf::Font& font, MenuManager* menuManager,Client& client,std::vector<FriendEntry>& vec) :
    Menu("Lobby"),
    nextPageButton(sf::Vector2f(700, 500), "Next", font), // Example positions
    prevPageButton(sf::Vector2f(100, 500), "Prev", font),
    backButton(sf::Vector2f(850, 50), "Back", font,15),  // Example position for top-right
    menuManager(menuManager)
{
    friendsList=vec;
    invited.clear();
    errorMessage.setFont(font);
    errorMessage.setString(""); // Start with an empty string
    errorMessage.setCharacterSize(13); // Adjust size as needed 
    errorMessage.setFillColor(sf::Color::Red);
    errorMessage.setPosition(750.f, 900.f);

    backButton.setSize(80.f, 30.f);
    backButton.setButtonColor(sf::Color(150, 0, 0)); // Red
    backButton.setHoverColor(sf::Color(200, 0, 0)); // Brighter red
    
    message=message+client.getLogin()+" ";
}

void LobbyMenu::draw(sf::RenderWindow& window){
    backButton.draw(window);
    window.draw(errorMessage);
    int startIndex=currentPage*friendsPerPage;
    int endIndex=std::min(startIndex+friendsPerPage,static_cast<int>(friendsList.size()));
    // Draw friends on the current page
    const float yPos=50.f;
    const float spacing=30.f;
    for(int i=startIndex;i<endIndex;++i){
        friendsList[i].setPosition(sf::Vector2f(yPos,yPos+(i%10)*30.f));
        friendsList[i].draw(window);
        MenuButton inviteButton(friendsList[i].getPosition() + sf::Vector2f(200.f, 0.f), "Invite", menuManager->getFont(),10,sf::Color::White,sf::Color::Blue,sf::Color::Cyan,75.f,25.f); // Adjust position and size
        inviteButton.draw(window);
    }
    if (startIndex > 0) {
        prevPageButton.draw(window);
    }
    if (endIndex < friendsList.size()) {
        nextPageButton.draw(window);
    }

}

void LobbyMenu::handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    int startIndex=currentPage*friendsPerPage;
    int endIndex=std::min(startIndex+friendsPerPage,static_cast<int>(friendsList.size()));
    for (int i = startIndex; i < endIndex; ++i) {
        const FriendEntry& friendEntry = friendsList[i];
        sf::FloatRect inviteButtonBounds(friendEntry.getPosition() + sf::Vector2f(200.f, 0.f), sf::Vector2f(80.f, 20.f)); // Adjust bounds as needed
        if (inviteButtonBounds.contains(mousePos.x, mousePos.y) && event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            std::string friendUsername = friendEntry.getUsername();
            std::vector<std::string> invited=getInvitedVector();
            if(invited.size()==1)
                leaveFlag=true;
            message=message+friendUsername+" ";
            invited.push_back(friendUsername);
            setInvitedVector(invited);
        }
    }

    if (nextPageButton.isPressed(window) && (currentPage+1)*friendsPerPage<friendsList.size()) {
        ++currentPage;
    } 
    if (prevPageButton.isPressed(window) && currentPage > 0) {
        --currentPage;
    }

    if (backButton.isPressed(window)) {
        MenuManager* menuManager = getMenuManager();
        if(menuManager){
            menuManager->popMenu();
        } 
    }
}

void LobbyMenu::update(const sf::Time& deltaTime,Client& client){
    if(leaveFlag==true){
        std::vector<std::string> invited=getInvitedVector();
        if(invited[0]==invited[1]){
            errorMessage.setString("You can't invite the same person twice.");
            invited.clear();
            setInvitedVector(invited);
            leaveFlag=false;
            message="602 "+client.getLogin()+" ";
        }
        else{
            // Everything's fine
            invited.clear();
            MenuManager* menuManager=getMenuManager();
            client.setMsg(message);
            if(menuManager){
                menuManager->pushMenu(new AwaitingMenu(menuManager->getFont(),menuManager,client));            
            }
        }
    }
}

MenuManager* LobbyMenu::getMenuManager(){
    return menuManager; 
}
