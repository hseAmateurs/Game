#include "controller.h"

int main(){
    Controller controller;
    controller.run();
}



// #include <SFML/Graphics.hpp>
// #include "textField.h"
// #include "menuButton.h"
// #include "startMenu.h"
// #include "menuManager.h"
// #include "authorizationMenu.h"
// #include <iostream>


// int main() {
//     sf::RenderWindow window(sf::VideoMode(800, 600), "Text Input");
//     window.setFramerateLimit(60); // Set a frame rate limit
//     sf::Clock clock;
//     // Load the font (replace with your font file path)
//     sf::Font font;
//     if (!font.loadFromFile("PressStart2P-Regular.ttf")) {
//         return 1;
//     }
//     MenuManager menuManager;
//     menuManager.setFont(font);
//     StartMenu startMenu(font, &menuManager);
//     menuManager.pushMenu(&startMenu);
//     sf::Time deltaTime=clock.restart();
//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 window.close();
//             }
//             // Handle input for the authorization menu
//             menuManager.handleInput(event, window);
//         }
//         sf::Time deltaTime=clock.restart();
//         menuManager.update(deltaTime);

//         window.clear(sf::Color(50, 50, 50)); // Example background color

//         // Draw the authorization menu
//         menuManager.draw(window);

//         window.display();
//     }

//     return 0;
// }