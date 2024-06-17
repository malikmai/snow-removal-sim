#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

// Function prototypes
void renderTitle(sf::RenderWindow &window, sf::Font &font, sf::Text &titleText);
void renderStartButton(sf::RenderWindow &window, sf::RectangleShape &button, sf::Text &buttonText);

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

    bool gameStarted = false;

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
                    if (startButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
                    {
                        gameStarted = true;
                    }
                }
            }
        }

        // Clear the screen
        window.clear();

        if (!gameStarted)
        {
            // Draw the background
            window.draw(backgroundSprite);

            renderTitle(window, font, titleText);
            renderStartButton(window, startButton, startButtonText);
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
