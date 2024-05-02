#include <algorithm>
#include "friendEntry.h"
#include "FriendsMenu.h"

FriendsMenu::FriendsMenu(const sf::Font& font, MenuManager* menuManager,Client& client,std::vector<FriendEntry>& vec) :
    Menu("Friends"),
    addFriendField(sf::Vector2f(100, 900), "", font), // Example position
    addFriendButton(sf::Vector2f(450, 900), "Add", font),
    nextPageButton(sf::Vector2f(700, 500), "Next", font), // Example positions
    prevPageButton(sf::Vector2f(100, 500), "Prev", font),
    backButton(sf::Vector2f(850, 50), "Back", font,15),  // Example position for top-right
    menuManager(menuManager)
{
    friendsList=vec;
    errorMessage.setFont(font);
    errorMessage.setString(""); // Start with an empty string
    errorMessage.setCharacterSize(13); // Adjust size as needed 
    errorMessage.setFillColor(sf::Color::Red);
    errorMessage.setPosition(750.f, 900.f);

    backButton.setSize(80.f, 30.f);
    backButton.setButtonColor(sf::Color(150, 0, 0)); // Red
    backButton.setHoverColor(sf::Color(200, 0, 0)); // Brighter red
}

void FriendsMenu::draw(sf::RenderWindow& window){
    addFriendField.draw(window);
    addFriendButton.draw(window);
    backButton.draw(window);
    window.draw(errorMessage);
    int startIndex=currentPage*friendsPerPage;
    int endIndex=std::min(startIndex+friendsPerPage,static_cast<int>(friendsList.size()));
    // Draw friends on the current page
    const float yPos=50.f;
    const float spacing=30.f;
    for(int i=startIndex;i<endIndex;++i){
        // also backbutton
        friendsList[i].setPosition(sf::Vector2f(yPos,yPos+(i%10)*30.f));
        friendsList[i].draw(window);
    }
    if (startIndex > 0) {
        prevPageButton.draw(window);
    }
    if (endIndex < friendsList.size()) {
        nextPageButton.draw(window);
    }

}

void FriendsMenu::handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client) {
    addFriendField.handleInput(event,window);

    if (addFriendButton.isPressed(window)) {
        std::string friendusername = addFriendField.getText();
        std::string message;
        message="402 "+client.getLogin()+" "+friendusername;
        client.sendMessage(message.c_str());
        message=client.getMessage();
        if(message=="0"){
            FriendEntry friendentry(friendusername,menuManager->getFont());
            friendsList.push_back(friendentry);
            errorMessage.setFillColor(sf::Color::Green);
            errorMessage.setString("Successfully added!");
        }
        if(message=="1"){
            errorMessage.setFillColor(sf::Color::Red);
            errorMessage.setString("You are friends with this person already!");
        }
            // are friends.
        if(message=="2"){
            errorMessage.setFillColor(sf::Color::Red);
            errorMessage.setString("Unable to find this login.");
        }
            // no such login exists.
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

void FriendsMenu::update(const sf::Time& deltaTime){
    addFriendField.update(deltaTime);
}

MenuManager* FriendsMenu::getMenuManager(){
    return menuManager; 
}
