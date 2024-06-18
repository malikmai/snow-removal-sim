#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <sstream>

// Function prototypes
void renderTitle(sf::RenderWindow &window, sf::Font &font, sf::Text &titleText);
void renderStartButton(sf::RenderWindow &window, sf::RectangleShape &button, sf::Text &buttonText);
void renderBackstoryScreen(sf::RenderWindow &window, sf::Font &font, sf::Sprite &backgroundSprite, sf::Text &backstoryText, sf::RectangleShape &backstoryBox, sf::RectangleShape &goToWorkButton, sf::Text &goToWorkButtonText);
void renderNamePrompt(sf::RenderWindow &window, sf::Font &font, sf::Text &namePromptText, sf::RectangleShape &nameBox);

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(736, 414), "Snow Remover 2000");
    window.setFramerateLimit(60);

    // Load font
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/DejaVuSans-Bold.ttf"))
    {
        std::cerr << "Error loading font\n";
        return 1;
    }

    // Load background image
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/images/startscreen.png"))
    {
        std::cerr << "Error loading background image\n";
        return 1;
    }
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);

    // Setup title text
    sf::Text titleText;
    titleText.setFont(font);
    titleText.setString("Snow Remover 2000");
    titleText.setCharacterSize(36);
    titleText.setFillColor(sf::Color::Black);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition(150, 60); // Adjusted for new window size and box

    // Setup start button
    sf::RectangleShape startButton(sf::Vector2f(200, 50));
    startButton.setPosition(268, 300);                // Adjusted for new window size
    startButton.setFillColor(sf::Color(0, 102, 204)); // Winter theme blue
    startButton.setOutlineColor(sf::Color::White);
    startButton.setOutlineThickness(2);

    sf::Text startButtonText;
    startButtonText.setFont(font);
    startButtonText.setString("Start Game");
    startButtonText.setCharacterSize(24);
    startButtonText.setFillColor(sf::Color::White);
    startButtonText.setPosition(288, 310); // Adjusted for new window size

    // Setup input for user name
    sf::String playerInput;
    sf::Text playerText;
    playerText.setFont(font);
    playerText.setCharacterSize(18);
    playerText.setFillColor(sf::Color::Black);
    playerText.setPosition(120, 150);
    playerText.setString("What is your name? "); // Initial prompt text

    // Setup name box
    sf::RectangleShape nameBox(sf::Vector2f(500, 60));
    nameBox.setPosition(118, 140);
    nameBox.setFillColor(sf::Color::White);
    nameBox.setOutlineColor(sf::Color::Black);
    nameBox.setOutlineThickness(2);

    bool gameStarted = false;
    bool showBackstory = false;
    bool nameEntered = false;
    std::string playerName;

    // Setup backstory text
    sf::Text backstoryText;
    backstoryText.setFont(font);
    backstoryText.setCharacterSize(14);
    backstoryText.setFillColor(sf::Color::Black);
    backstoryText.setPosition(70, 50); // Adjust as needed

    // Setup backstory box
    sf::RectangleShape backstoryBox(sf::Vector2f(600, 200));
    backstoryBox.setPosition(68, 40);
    backstoryBox.setFillColor(sf::Color::White);
    backstoryBox.setOutlineColor(sf::Color::Black);
    backstoryBox.setOutlineThickness(2);

    // Setup go to work button
    sf::RectangleShape goToWorkButton(sf::Vector2f(150, 40));
    goToWorkButton.setPosition(293, 320);                // Adjusted for new window size
    goToWorkButton.setFillColor(sf::Color(0, 102, 204)); // Winter theme blue
    goToWorkButton.setOutlineColor(sf::Color::White);
    goToWorkButton.setOutlineThickness(2);

    sf::Text goToWorkButtonText;
    goToWorkButtonText.setFont(font);
    goToWorkButtonText.setString("Go to work");
    goToWorkButtonText.setCharacterSize(18);
    goToWorkButtonText.setFillColor(sf::Color::White);
    goToWorkButtonText.setPosition(308, 328); // Adjust as needed

    // Main loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle mouse click on start button
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (!gameStarted && startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        showBackstory = true;
                    }
                    if (showBackstory && nameEntered && goToWorkButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        gameStarted = true;
                    }
                }
            }

            // Handle text input
            if (showBackstory && !nameEntered && event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b' && playerInput.getSize() > 0)
                {
                    playerInput.erase(playerInput.getSize() - 1, 1);
                }
                else if (event.text.unicode < 128 && playerInput.getSize() < 10)
                {
                    playerInput += event.text.unicode;
                }
                playerText.setString("What is your name? " + playerInput);
            }

            // Handle enter key press for name submission
            if (showBackstory && !nameEntered && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && playerInput.getSize() > 0)
            {
                nameEntered = true;
                playerName = playerInput;
                std::ostringstream backstoryStream;
                backstoryStream << "So your name is " << playerName << " huh? Well " << playerName << ", here's the jazz kid... \n";
                backstoryStream << "\n";
                backstoryStream << "Its been a bad winter and been snowing all year!\n";
                backstoryStream << "We need you to get this place up and running in 30 DAYS!\n";
                backstoryStream << "I'll need you to use your cunning and wit to manage us out of this pickle.\n";
                backstoryStream << "\n";
                backstoryStream << "Goal:\n";
                backstoryStream << "Your goal is to get us a big ol' truck and some new building upgrades but\n";
                backstoryStream << "its gonna run us $100000! Well.. I'm off to Florida with the wife. \n";
                backstoryStream << "See ya in a month!";
                backstoryText.setString(backstoryStream.str());
            }
        }

        // Clear the screen
        window.clear();

        if (!gameStarted)
        {
            if (showBackstory)
            {
                if (!nameEntered)
                {
                    window.draw(backgroundSprite);
                    window.draw(nameBox);
                    window.draw(playerText);
                }
                else
                {
                    renderBackstoryScreen(window, font, backgroundSprite, backstoryText, backstoryBox, goToWorkButton, goToWorkButtonText);
                }
            }
            else
            {
                // Draw the background
                window.draw(backgroundSprite);

                renderTitle(window, font, titleText);
                renderStartButton(window, startButton, startButtonText);
            }
        }
        else
        {
            // Game rendering and logic here (to be implemented)
        }

        // Update the window
        window.display();
    }

    return 0;
}

void renderTitle(sf::RenderWindow &window, sf::Font &font, sf::Text &titleText)
{
    window.draw(titleText);
}

void renderStartButton(sf::RenderWindow &window, sf::RectangleShape &button, sf::Text &buttonText)
{
    window.draw(button);
    window.draw(buttonText);
}

void renderBackstoryScreen(sf::RenderWindow &window, sf::Font &font, sf::Sprite &backgroundSprite, sf::Text &backstoryText, sf::RectangleShape &backstoryBox, sf::RectangleShape &goToWorkButton, sf::Text &goToWorkButtonText)
{
    window.draw(backgroundSprite);
    window.draw(backstoryBox);
    window.draw(backstoryText);
    window.draw(goToWorkButton);
    window.draw(goToWorkButtonText);
}