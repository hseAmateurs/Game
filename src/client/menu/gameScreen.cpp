#include "gameScreen.h"

GameScreen::GameScreen(const sf::Font& font, MenuManager* menuManager,Client& client) :
    Menu("Game"),
    testButton(sf::Vector2f(850, 50), "bttn", font,15),  // Example position for top-right
    menuManager(menuManager)
{
    testText.setFont(font);
    testText.setString(""); // Start with an empty string
    testText.setCharacterSize(13); // Adjust size as needed 
    testText.setFillColor(sf::Color::Red);
    testText.setPosition(750.f, 900.f);

    testButton.setSize(80.f, 30.f);
    testButton.setButtonColor(sf::Color(150, 0, 0)); // Red
    testButton.setHoverColor(sf::Color(200, 0, 0)); // Brighter red
}


MenuManager* GameScreen::getMenuManager(){
    return menuManager; 
}

void GameScreen::draw(sf::RenderWindow& window){
    testButton.draw(window);
    window.draw(testText); 
}

void GameScreen::handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client){
    if(testButton.isPressed(window)){
        MenuManager* menuManager=getMenuManager();
        if(menuManager){
            std::string message;
            message="601 "+client.getLogin()+" 1";
            client.sendMessage(message.c_str());
            message=client.getMessage();
            testText.setString(message);
        }
    }
} 

void GameScreen::update(const sf::Time& deltaTime,Client& client){
    MenuManager* menuManager=getMenuManager();
    if(menuManager){
        std::string message;
        message=client.getMessage();
        testText.setString(message);
    }

}