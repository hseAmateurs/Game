#include <SFML/Graphics.hpp>
#include "textField.h"
#include "menuButton.h"
#include <iostream>


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Text Input");
    window.setFramerateLimit(60); // Set a frame rate limit

    // Load the font (replace with your font file path)
    sf::Font font;
    if (!font.loadFromFile("PressStart2P-Regular.ttf")) {
    //if(!font.loadFromFile("C:/HSE/C++/gameproj/Game/src/client/resources/PressStart2P-Regular.ttf"))
        // Handle error
        return 1;
    }

    // Create a TextField object
    Textfield textField(sf::Vector2f(100, 100), "", font, 30, sf::Color::White,sf::Color::Black,200.f,50.f);
    MenuButton menuButton(sf::Vector2f(300,300), "Huy", font, 30, sf::Color::White,sf::Color::Blue,sf::Color::Cyan,150.f,50.f);

    sf::Clock clock; // Clock for tracking time

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                // Check if the text field was clicked
                if (textField.isMouseOver(window))
                    textField.setActive(true); 
                else{
                    textField.setActive(false); 
                }
            } 

            // Pass events to the TextField for handling input
            textField.handleInput(event);
        }

        // Update the TextField with delta time
        sf::Time deltaTime = clock.restart();
        textField.update(deltaTime);

        // Clear the window with dark blue color
        window.clear(sf::Color(0, 0, 50)); 

        // Draw the TextField
        textField.draw(window);

        menuButton.draw(window);

        window.display();
    }

    return 0;
}


// // Function to check password validity
// bool isValidPassword(const sf::String& password) {
//     if (password.getSize() < 6) {
//         return false;
//     }
//     for (char c : password) {
//         if (!isalnum(c) && !ispunct(c)) { // Check for alphanumeric and punctuation
//             return false;
//         }
//     }
//     return true;
// }


// int main() {
//     // Создаем окно
//     sf::RenderWindow window(sf::VideoMode(1920, 1080), "Game Authorization");
//     window.setFramerateLimit(60);

//     // Фон (темно-синий)
//     sf::RectangleShape background(sf::Vector2f(1920, 1080));
//     background.setFillColor(sf::Color(0, 0, 50));  // Dark blue

//     // Текстовые поля (увеличенные)
//     sf::RectangleShape loginField(sf::Vector2f(400, 60)); 
//     loginField.setFillColor(sf::Color::Black);
//     loginField.setPosition(760, 400);

//     sf::RectangleShape passwordField(sf::Vector2f(400, 60));
//     passwordField.setFillColor(sf::Color::Black);
//     passwordField.setPosition(760, 500);

//     // Текст (уменьшенный размер шрифта)
//     sf::Font font;
//     if (!font.loadFromFile("PressStart2P-Regular.ttf")) {
//         return EXIT_FAILURE;
//     }
//     sf::Text loginText("Login", font, 24);
//     loginText.setFillColor(sf::Color::White);
//     loginText.setPosition(770, 410);

//     sf::Text passwordText("Password", font, 24);
//     passwordText.setFillColor(sf::Color::White);
//     passwordText.setPosition(770, 510);

//     // Cursor variables
//     sf::RectangleShape cursor(sf::Vector2f(2, 30)); // Adjust size as needed
//     cursor.setFillColor(sf::Color::White);
//     bool showCursor = true;
//     sf::Clock cursorClock;

//     // Error message
//     sf::Text errorMessage("", font, 20);
//     errorMessage.setFillColor(sf::Color::Red);
//     errorMessage.setPosition(750, 350); // Adjust position as needed

//     // Переменные для ввода текста
//     sf::String loginInput;
//     sf::String passwordInput;

//     // Главный цикл
//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed) {
//                 window.close();
//             } else if (event.type == sf::Event::TextEntered) {
//                 if (event.text.unicode < 128) {
//                     if (loginField.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
//                         if (event.text.unicode == '\b' && !loginInput.isEmpty()) { // Backspace
//                             loginInput.erase(loginInput.getSize() - 1, 1);
//                         } else if (event.text.unicode != '\r') { // Ignore Enter
//                             loginInput += event.text.unicode;
//                         }
//                     } else if (passwordField.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
//                         if (event.text.unicode == '\b' && !passwordInput.isEmpty()) { // Backspace
//                             passwordInput.erase(passwordInput.getSize() - 1, 1);
//                         } else if (event.text.unicode != '\r' && 
//                                    event.text.unicode != ' ' && // No spaces
//                                    event.text.unicode >= 32) {   // Allow special characters and numbers
//                             passwordInput += event.text.unicode;
//                         }
//                     }
//                 }
//             } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
//             if (isValidPassword(passwordInput)) {
//                 std::cout << "Data sent to server" << std::endl;
//                 errorMessage.setString(""); // Clear any previous error message
//             } else {
//                 errorMessage.setString("Invalid password. Must be at least 6 characters with no spaces or cyrillic characters.");
//             }
//         }
//             // Cursor blinking
//         if (cursorClock.getElapsedTime().asSeconds() > 0.5f) {
//             showCursor = !showCursor;
//             cursorClock.restart();
//         }

//         // Position cursor in active field
//         if (loginField.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
//             cursor.setPosition(loginText.findCharacterPos(loginInput.getSize()) + sf::Vector2f(5, 5)); // Adjust offset as needed
//         } else if (passwordField.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
//             cursor.setPosition(passwordText.findCharacterPos(passwordInput.getSize()) + sf::Vector2f(5, 5));
//         }
//         }

//         // Обновляем текст в полях
//         loginText.setString(loginInput);
//         passwordText.setString(passwordInput);

//         window.clear();
//         // Отрисовка
//         if (showCursor)
//             window.draw(cursor);
//         window.draw(errorMessage); // Draw error message
//         window.draw(background);
//         window.draw(loginField);
//         window.draw(passwordField); 
//         window.draw(loginText);
//         window.draw(passwordText);
//         window.display();
//     }

//     return 0;
// }