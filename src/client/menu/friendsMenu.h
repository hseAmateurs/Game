#ifndef FRIENDSMENU_H
#define FRIENDSMENU_H

#include "menu.h"
#include "menuButton.h"
#include "textField.h"
#include "menuManager.h"
#include "friendEntry.h"

class FriendsMenu : public Menu {
public:
    FriendsMenu(const sf::Font& font, MenuManager* menuManager,Client& client,std::vector<FriendEntry>& vec);

    void draw(sf::RenderWindow& window) override;
    void handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client) override;
    void update(const sf::Time& deltaTime);
    MenuManager* getMenuManager();
    std::vector<FriendEntry> getFriendVector(){return friendsList;};
    void setFriendVector(std::vector<FriendEntry> vec){friendsList=vec;}; // both ugly and slow 

private:
    std::vector<FriendEntry> friendsList;
    Textfield addFriendField;
    MenuButton addFriendButton;
    int currentPage = 0;
    int friendsPerPage = 10; 
    MenuButton nextPageButton;
    MenuButton prevPageButton;
    sf::Text errorMessage;
    MenuButton backButton;
    MenuManager* menuManager;
};

#endif