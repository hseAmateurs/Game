#include "gameScreen.h"

/*
Этот экран - пустышка.
Он нужен лишь для того, чтобы обмануть мой controller (в стеке menuManager будет лежать меню с нужным именем)
и заставить его переключиться на gameController,
который в свою очередь уже запустит игру.
*/

GameScreen::GameScreen(const sf::Font& font, MenuManager* menuManager,Client& client) :
    Menu("GameScreen"),
    menuManager(menuManager)
{
}


MenuManager* GameScreen::getMenuManager(){
    return menuManager; 
}

void GameScreen::draw(sf::RenderWindow& window){
}

void GameScreen::handleInput(const sf::Event& event, sf::RenderWindow& window,Client& client){
} 

void GameScreen::update(const sf::Time& deltaTime,Client& client){

}