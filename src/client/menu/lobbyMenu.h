#ifndef LOBBYMENU_H
#define LOBBYMENU_H

#include "menu.h"
#include "menuButton.h"
#include "textField.h"
#include "menuManager.h"
#include <vector>
#include "friendEntry.h"

class LobbyMenu : public Menu {
public:
    LobbyMenu(const sf::Font& font, MenuManager* menuManager,Client& client,std::vector<FriendEntry>& vec);

    void draw(sf::RenderWindow& window) override;
    void handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client) override;
    void update(const sf::Time& deltaTime,Client& client);
    MenuManager* getMenuManager();
    std::vector<FriendEntry> getFriendVector(){return friendsList;};
    std::vector<std::string> getInvitedVector(){return invited;};
    void setInvitedVector(std::vector<std::string> vec){invited=vec;}; 
    void setFriendVector(std::vector<FriendEntry> vec){friendsList=vec;}; 

private:
    std::vector<FriendEntry> friendsList;
    std::vector<std::string> invited;
    int currentPage = 0;
    int friendsPerPage = 10; 
    MenuButton nextPageButton;
    MenuButton prevPageButton;
    sf::Text errorMessage;
    MenuButton backButton;
    MenuManager* menuManager;
    std::string message="602 ";
    bool leaveFlag=false;
};

#endif