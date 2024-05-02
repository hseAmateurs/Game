#include "menuManager.h"
#include "mainMenu.h"
#include "menuButton.h"
#include "statisticsMenu.h"


StatisticsMenu::StatisticsMenu(const sf::Font& font, MenuManager* menuManager,Client& client) :
    Menu("Statistics"),    
    backButton(sf::Vector2f(850, 50), "Back", font,10), // Example position for top-right
    menuManager(menuManager)
{
    backButton.setSize(80.f, 30.f);
    backButton.setButtonColor(sf::Color(150, 0, 0)); // Red
    backButton.setHoverColor(sf::Color(200, 0, 0)); // Brighter red

    std::string stats="";
    stats="\t\tYour stats:\n\n\n\n\n\nDeaths: "+client.getDeaths()+"\n\n\nKills: "+client.getKills()+"\n\n\nGames played: "+client.getGamecount(); // unholy
    statistics.setFont(font);
    statistics.setString(stats);
    statistics.setCharacterSize(25); // Adjust size as needed 
    statistics.setFillColor(sf::Color::Red);
    statistics.setPosition(600.f, 250.f); // Example position (below the buttons)

}

void StatisticsMenu::draw(sf::RenderWindow& window) {
    backButton.draw(window);
    window.draw(statistics);
}

MenuManager* StatisticsMenu::getMenuManager() {
    return menuManager; 
}

void StatisticsMenu::handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client){
    if (backButton.isPressed(window)) {
        MenuManager* menuManager = getMenuManager();
        if(menuManager){
            menuManager->popMenu();
        } 
    }
}

