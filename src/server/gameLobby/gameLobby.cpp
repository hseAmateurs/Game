#include "gameLobby.h"
#include <algorithm>
#include "../../common.h"
#include <algorithm>
#include <memory>


void GameLobby::addPlayer(const std::string& username, int clientSocket) {
    playerLogins.push_back(username);
    playerSockets.push_back(clientSocket);
    // ... (Potentially store username and other player data) ...
}

void GameLobby::notifyPlayers(const std::string& message) {
    for (int clientSocket : playerSockets) {
        //server.sendMessage(clientSocket, message.c_str());
    }
}

bool GameLobby::hasPlayer(const std::string& username) {
    for (const auto& player : playerLogins) {
        if (player == username) {
            return true; // Player found in this lobby
        }
    }
    return false; // Player not found in this lobby
}

void GameLobby::gameLoop() {
    view.reset(sf::FloatRect(0, 0, settings::screen::WIDTH, settings::screen::HEIGHT));

    /*while (window.isOpen()) {
        sf::Event event{};
        if (event.type == sf::Event::Closed)
            window.close();
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            field.handleRightClick(sf::Mouse::getPosition(window));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            field.handleLeftClick(sf::Mouse::getPosition(window));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            field.handleButton(sf::Keyboard::Q);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            field.handleButton(sf::Keyboard::W);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            field.handleButton(sf::Keyboard::E);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            field.handleButton(sf::Keyboard::R);
    }*/
    sf::Time elapsed = clock.restart();

    field.update(elapsed, sf::Mouse::getPosition(window));

    window.clear(sf::Color(100,100,100));
    //changeView(elapsed, event.mouseWheelScroll.delta, sf::Mouse::getPosition(window));
    window.setView(view);
    field.draw(window);
    window.display();
    //test+=1;
}

//void GameLobby::setNames() {
//    field.setNames(playerLogins);
//}




